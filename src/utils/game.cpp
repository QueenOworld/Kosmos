#include "utils/game.hpp"
#include "math/Coords.hpp"
#include "types/CosmicObject.hpp"
#include "utils/input.hpp"
#include "utils/tui.hpp"
#include <cmath>
#include <csignal>
#include <iomanip>
#include <iostream>

#ifdef __unix__
#include <sys/ioctl.h>
#endif

#ifdef _WIN32
#include <Windows.h>
#endif

Game *Game::me = nullptr;

Game::Game(const int object_count) : object_count(object_count) {
    me = this;

#ifdef __unix__
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);
#endif

#ifdef _WIN32
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
#endif

    cosmic_objects =
        std::vector<CosmicObject>(object_count, CosmicObject({0, 0, 0}));

    for (int i = 0; i < object_count; i++) {
        cosmic_objects[i] = CosmicObject(random_spherical_coords());
    }

#ifdef __unix__
    view_radius =
        std::floor(std::min(wsize.ws_row, (unsigned short)(wsize.ws_col / 2)) /
                   2) -
        1;
#endif

#ifdef _WIN32
    view_radius =
        std::floor(std::min(csbi.srWindow.Bottom - csbi.srWindow.Top + 1,
                            (unsigned short)((csbi.srWindow.Right -
                                              csbi.srWindow.Left + 1) /
                                             2)) /
                   2) -
        1;

#endif

    zoom = view_radius * 2;

    x_rotation = 0.0;
    y_rotation = 0.0;
    z_rotation = 0.0;

    rotation_distance = 0.1;

    signal(SIGWINCH, redraw);
}

void Game::step() {
    viewport_t view = viewport_t(
        2 * view_radius + 1, std::vector<CosmicObject>(
                                 2 * view_radius + 1, CosmicObject({0, 0, 0})));

    for (CosmicObject cosmic_object : cosmic_objects) {
        CartesianCoordinates xyz =
            spherical_to_cartesian_coords(cosmic_object.spherical_coords);

        double x = xyz.x * (zoom / (zoom - xyz.z));
        double y = xyz.y * (zoom / (zoom - xyz.z));

        if (x >= -(view_radius) && x <= view_radius && y >= -(view_radius) &&
            y <= view_radius) {
            view[y + view_radius][x + view_radius] = cosmic_object;
        }
    }

    int input = getch(false);

    switch (input) {
    case KEY_W:
    case UP: {
        x_rotation += rotation_distance;
        for (int i = 0; i < object_count; i++) {
            rotate(cosmic_objects[i].spherical_coords,
                   rotation_distance * (M_PI / 180), 0.00, 0.0);
        }
        break;
    }
    case KEY_S:
    case DOWN: {
        x_rotation -= rotation_distance;
        for (int i = 0; i < object_count; i++) {
            rotate(cosmic_objects[i].spherical_coords,
                   -rotation_distance * (M_PI / 180), 0.0, 0.0);
        }
        break;
    }
    case KEY_D:
    case RIGHT: {
        y_rotation += rotation_distance;
        for (int i = 0; i < object_count; i++) {
            rotate(cosmic_objects[i].spherical_coords, 0.0,
                   rotation_distance * (M_PI / 180), 0.0);
        }
        break;
    }
    case KEY_A:
    case LEFT: {
        y_rotation -= rotation_distance;
        for (int i = 0; i < object_count; i++) {
            rotate(cosmic_objects[i].spherical_coords, 0.0,
                   -rotation_distance * (M_PI / 180), 0.0);
        }
        break;
    }
    case KEY_Q: {
        z_rotation -= rotation_distance;
        for (int i = 0; i < object_count; i++) {
            rotate(cosmic_objects[i].spherical_coords, 0.0, 0.0,
                   -rotation_distance * (M_PI / 180));
        }
        break;
    }
    case KEY_E: {
        z_rotation += rotation_distance;
        for (int i = 0; i < object_count; i++) {
            rotate(cosmic_objects[i].spherical_coords, 0.0, 0.0,
                   rotation_distance * (M_PI / 180));
        }
        break;
    }
    case KEY_Z: {
        zoom -= 1;
        if (zoom < 1)
            zoom = 1;
        break;
    }
    case KEY_X: {
        zoom++;
        break;
    }
    case KEY_C: {
        zoom = view_radius * 2;
        break;
    }
    case KEY_PLUS: {
        rotation_distance += 0.1;
        break;
    }
    case KEY_MINUS: {
        rotation_distance -= 0.1;
        if (rotation_distance <= 0)
            rotation_distance = 0.1;
        break;
    }
    case KEY_ZERO: {
        rotation_distance = 0.1;
        break;
    }
    case KEY_SPACE: {
        CosmicObject *target = &view[view_radius][view_radius];
        if ((*target).Seed != 0) {
            std::cout << "\033[0;0f" << ansi_escape_codes::white_color()
                      << "Info" << "\nSeed: " << (*target).Seed
                      << "\nDistance: " << (*target).spherical_coords.radius
                      << "ly"
                      << "\nAbsolute Magnitude: " << (*target).AbsoluteMagnitude
                      << "\nApparent Magnitude: " << (*target).ApparentMagnitude
                      << "\nClass: " << (*target).Class
                      << "\nColor: " << (*target).Color << "#";
        }
        getch(false);
        break;
    }
    case KEY_ENTER: {
        CosmicObject *target = &view[view_radius][view_radius];
        std::cout << (*target).spherical_coords.radius << " "
                  << (*target).spherical_coords.angle << " "
                  << (*target).spherical_coords.azimuth;
        break;
    }
    }

    if (std::abs(x_rotation) >= 360) {
        x_rotation = 0;
    } else if (std::abs(x_rotation) < 0) {
        x_rotation = M_PI;
    }

    if (std::abs(y_rotation) >= 360) {
        y_rotation = 0;
    } else if (std::abs(y_rotation) < 0) {
        y_rotation = M_PI;
    }

    if (std::abs(z_rotation) >= 360) {
        z_rotation = 0;
    } else if (std::abs(z_rotation) < 0) {
        z_rotation = M_PI;
    }
}

void Game::draw() {
    std::vector<std::vector<CosmicObject>> view =
        std::vector<std::vector<CosmicObject>>(
            2 * view_radius + 1,
            std::vector<CosmicObject>(2 * view_radius + 1,
                                      CosmicObject({0, 0, 0})));

    for (CosmicObject cosmic_object : cosmic_objects) {
        CartesianCoordinates xyz =
            spherical_to_cartesian_coords(cosmic_object.spherical_coords);

        double x = xyz.x * (zoom / (zoom - xyz.z));
        double y = xyz.y * (zoom / (zoom - xyz.z));

        if (x >= -(view_radius) && x <= view_radius && y >= -(view_radius) &&
            y <= view_radius) {
            view[y + view_radius][x + view_radius] = cosmic_object;
        }
    }

    std::stringstream framebuffer;
    framebuffer << SCREEN_OVERWRITE;

    for (int row = 0; row < 2 * view_radius + 1; row++) {
        for (int col = 0; col < 2 * view_radius + 1; col++) {
            if (row == view_radius && col == view_radius) {
                framebuffer << ansi_escape_codes::color_bg_n(232)
                            << ansi_escape_codes::slow_blink_opcode()
                            << view[row][col].Color << view[row][col].Symbol
                            << ansi_escape_codes::blink_off_opcode();
            } else if (row == view_radius || col == view_radius) {
                framebuffer << ansi_escape_codes::color_bg_n(233)
                            << view[row][col].Color << view[row][col].Symbol;
            } else {
                framebuffer << ansi_escape_codes::color_bg_n(232)
                            << view[row][col].Color << view[row][col].Symbol;
            }
        }
        framebuffer << '\n';
    }

    framebuffer << "" << ansi_escape_codes::reset << std::fixed
                << std::setprecision(2) << " X: " << x_rotation
                << " Y: " << y_rotation << " Z: " << z_rotation
                << " Zoom: " << zoom
                << " Rotation Distance: " << rotation_distance
                << " Seed: " << view[view_radius][view_radius].Seed
                << "                    ";

    std::cout << framebuffer.str() << std::flush;
}

void Game::redraw(int signum) {
#ifdef __unix__
    signal(SIGWINCH, SIG_IGN);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);
    system("clear");
    me->view_radius =
        std::floor(std::min(wsize.ws_row, (unsigned short)(wsize.ws_col / 2)) /
                   2) -
        1;
    me->draw();
    signal(SIGWINCH, redraw);
#endif
#ifdef _WIN32
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    system("clr");
    me->view_radius =
        std::floor(std::min(csbi.srWindow.Bottom - csbi.srWindow.Top + 1,
                            (unsigned short)((csbi.srWindow.Right -
                                              csbi.srWindow.Left + 1) /
                                             2)) /
                   2) -
        1;
    me->draw();
#endif
}
