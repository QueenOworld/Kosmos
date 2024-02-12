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

    const int object_count = 500;

    int view_radius = 35;

    int zoom = view_radius * 2;

    int input = 0;

    double x_rotation = 0.0;
    double y_rotation = 0.0;
    double z_rotation = 0.0;

    std::vector<CosmicObject> objects = std::vector<CosmicObject>(object_count, CosmicObject({0, 0, 0}));

    for (int i = 0; i < object_count; i++)
    {
        objects[i] = CosmicObject(random_spherical_coords());
    }

    while (true)
    {
        std::vector<std::vector<CosmicObject>> view = std::vector<std::vector<CosmicObject>>(2 * view_radius + 1, std::vector<CosmicObject>(2 * view_radius + 1, CosmicObject({0, 0, 0})));

        for (CosmicObject i : objects)
        {
            CartesianCoordinates xyz = spherical_to_cartesian_coords(i.spherical_coords);

            double X = xyz.x * (zoom / (zoom - xyz.z));
            double Y = xyz.y * (zoom / (zoom - xyz.z));

            if (X >= -(view_radius) && X <= view_radius && Y >= -(view_radius) && Y <= view_radius && xyz.z > 1.0)
            {
                view[Y + view_radius][X + view_radius] = i;
            }
        }

        std::cout << "\033[0;0f";

        for (int row = 0; row < 2 * view_radius + 1; row++)
        {
            for (int col = 0; col < 2 * view_radius + 1; col++)
            {
                if (view[row][col].Seed == 0)
                {
                    std::cout << ansi_escape_codes::color_bg_n(232) << ansi_escape_codes::color_n(255) << ' ' << ' ';
                }
                else
                {
                    std::cout << ansi_escape_codes::color_bg_n(232) << view[row][col].get_color() << view[row][col].get_symbol() << ' ';
                }
            }
            std::cout << '\n';
        }

        std::cout << std::endl;

        switch (input)
        {
            case 119:
            case 65: // up
            {
                x_rotation += 0.02;
                for (int i = 0; i < object_count; i++)
                {
                    rotate(objects[i].spherical_coords, 0.02, 0.00, 0.00);
                }
                // std::cout << "\u2191";
            }
            case 115:
            case 66: // down
            {
                x_rotation -= 0.01;
                y_rotation -= 0.01;
                for (int i = 0; i < object_count; i++)
                {
                    rotate(objects[i].spherical_coords, -0.01, -0.01, 0.00);
                }
                // std::cout << "\u2193";
            }
            case 100:
            case 67: // right
            {
                y_rotation += 0.02;
                for (int i = 0; i < object_count; i++)
                {
                    rotate(objects[i].spherical_coords, 0.0, 0.02, 0.00);
                }
                // std::cout << "\u2192";
            }
            case 97:
            case 68: // left
            {
                zoom++;
                y_rotation -= 0.01;
                for (int i = 0; i < object_count; i++)
                {
                    rotate(objects[i].spherical_coords, 0.0, -0.01, 0.01);
                }
                // std::cout << "\u2190";
            }
            case 113: // q
            {
                zoom--;
                z_rotation -= 0.02;
                for (int i = 0; i < object_count; i++)
                {
                    rotate(objects[i].spherical_coords, 0.0, 0.0, -0.02);
                }
                // std::cout << "\u21BA";
            }
            case 101: // e
            {
                zoom++;
                z_rotation += 0.01;
                for (int i = 0; i < object_count; i++)
                {
                    rotate(objects[i].spherical_coords, 0.0, 0.0, 0.01);
                }
                // std::cout << "\u21BB";
            }
            case 122: // z
            {
                zoom -= 2;
                if (zoom < 1)
                    zoom = 1;
            }
            case 120: // x
            {
                zoom++;
            }
        }

        if (x_rotation >= 360.0)
        {
            x_rotation = 0;
        }
        else if (x_rotation < 0)
        {
            x_rotation = 359.99;
        }

        if (y_rotation >= 360.0)
        {
            y_rotation = 0;
        }
        else if (y_rotation < 0)
        {
            y_rotation = 359.99;
        }

        if (z_rotation >= 360.0)
        {
            z_rotation = 0;
        }
        else if (z_rotation < 0)
        {
            z_rotation = 359.99;
        }

        std::cout << ansi_escape_codes::reset << std::format(" X: {}    Y: {}   Z: {}   Zoom: {}                               ", x_rotation, y_rotation, z_rotation, zoom);

        input = getch_echo(false);
    }
}