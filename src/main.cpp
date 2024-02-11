#include <iostream>
#include "types/CosmicObject.hpp"
#include "math/Coords.hpp"
#include <vector>
#include "utils/input.hpp"
#include "utils/ansi_escape_code.hpp"
#include <math.h>
#include <format>

int main()
{
    // while (true)
    // {
    //     std::cout << getch_echo(false) << "\n";
    // }

    int view_radius = 35;

    int input = 0;

    double x_rotation = 0.0;
    double y_rotation = 0.0;
    double z_rotation = 0.0;

    std::vector<CosmicObject> objects = std::vector<CosmicObject>(100, CosmicObject({0, 0, 0}));

    for (int i = 0; i < 100; i++)
    {
        objects[i] = CosmicObject(random_spherical_coords());
    }

    while (true)
    {
        std::vector<std::vector<char>> view = std::vector<std::vector<char>>(2 * view_radius + 1, std::vector<char>(2 * view_radius + 1, ' '));

        for (CosmicObject i : objects)
        {
            CartesianCoordinates xyz = spherical_to_cartesian_coords(i.spherical_coords);

            double X = xyz.x / (xyz.z);
            double Y = xyz.y / (xyz.z);

            if (X >= -(view_radius) && X <= view_radius && Y >= -(view_radius) && Y <= view_radius && xyz.z > 1.0)
            {
                if (i.spherical_coords.radius < 30000.0)
                {
                    view[Y + view_radius][X + view_radius] = '3';
                }
                else if (i.spherical_coords.radius < 60000.0)
                {
                    view[Y + view_radius][X + view_radius] = '2';
                }
                else
                {
                    view[Y + view_radius][X + view_radius] = '1';
                }
            }
        }

        std::cout << "\033[0;0f";

        for (int row = 0; row < 2 * view_radius + 1; row++)
        {
            for (int col = 0; col < 2 * view_radius + 1; col++)
            {
                if (view[row][col] == '3')
                {
                    std::cout << ansi_escape_codes::color_bg_n(232) << ansi_escape_codes::color_n(255) << '*' << ' ';
                }
                else if (view[row][col] == '2') {
                    std::cout << ansi_escape_codes::color_bg_n(232) << ansi_escape_codes::color_rgb(100, 100, 100) << '.' << ' ';
                }
                else if (view[row][col] == '1') {
                    std::cout << ansi_escape_codes::color_bg_n(232) << ansi_escape_codes::color_n(235) << '.' << ' ';
                }
                else
                {
                    std::cout << ansi_escape_codes::color_bg_n(232) << ansi_escape_codes::color_n(255) << ' ' << ' ';
                }
            }
            std::cout << '\n';
        }

        std::cout << std::endl;

        input = getch_echo(false);

        switch (input)
        {
            case 119:
            case 65: // up
            {
                x_rotation += 0.01;
                for (int i = 0; i < 100; i++)
                {
                    rotate(objects[i].spherical_coords, 0.02, 0.0, 0.0);
                }
                //std::cout << "\u2191";
            }
            case 115:
            case 66: // down
            {
                x_rotation -= 0.01;
                for (int i = 0; i < 100; i++)
                {
                    rotate(objects[i].spherical_coords, -0.01, 0.0, 0.0);
                }
                //std::cout << "\u2193";
            }
            case 100:
            case 67: // right
            {
                y_rotation += 0.01;
                for (int i = 0; i < 100; i++)
                {
                    rotate(objects[i].spherical_coords, 0.0, 0.02, 0.0);
                }
                //std::cout << "\u2192";
            }
            case 97:
            case 68: // left
            {
                y_rotation -= 0.01;
                for (int i = 0; i < 100; i++)
                {
                    rotate(objects[i].spherical_coords, 0.0, -0.01, 0.0);
                }
                //std::cout << "\u2190";
            }
            case 113: // q
            {
                z_rotation -= 0.01;
                for (int i = 0; i < 100; i++)
                {
                    rotate(objects[i].spherical_coords, 0.0, 0.0, -0.02);
                }
                //std::cout << "\u21BA";
            }
            case 101: // e
            {
                z_rotation += 0.01;
                for (int i = 0; i < 100; i++)
                {
                    rotate(objects[i].spherical_coords, 0.0, 0.0, 0.01);
                }
                //std::cout << "\u21BB";
            }
        }

        if (x_rotation >= 360.0) {
            x_rotation = 0;
        }
        else if (x_rotation < 0) {
            x_rotation = 359.99;
        }

        if (y_rotation >= 360.0) {
            y_rotation = 0;
        }
        else if (y_rotation < 0) {
            y_rotation = 359.01;
        }

        if (z_rotation >= 360.0) {
            z_rotation = 0;
        }
        else if (z_rotation < 0) {
            z_rotation = 359.01;
        }

        //std::cout << ansi_escape_codes::reset << std::format(" X: {}    Y: {}   Z: {}                               ", x_rotation, y_rotation, z_rotation);
    }
}