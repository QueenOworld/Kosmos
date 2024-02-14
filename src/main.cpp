#include <iostream>
#include "types/CosmicObject.hpp"
#include "math/Coords.hpp"
#include <vector>
#include "utils/input.hpp"
#include "utils/ansi_escape_code.hpp"
#include <math.h>
#include <string>
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

    double rotation_distance = 0.01;

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
                if ((row == view_radius || col == view_radius) && !(row == view_radius && col == view_radius))
                {
                    std::cout << ansi_escape_codes::color_bg_n(233) << view[row][col].get_color() << view[row][col].get_symbol();
                }
                else if (row == view_radius && col == view_radius)
                {
                    std::cout << ansi_escape_codes::color_bg_n(232) << ansi_escape_codes::slow_blink_opcode() << view[row][col].get_color() << view[row][col].get_symbol() << ansi_escape_codes::blink_off_opcode();
                }
                else
                {
                    std::cout << ansi_escape_codes::color_bg_n(232) << view[row][col].get_color() << view[row][col].get_symbol();
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
                x_rotation += rotation_distance;
                for (int i = 0; i < object_count; i++)
                {
                    rotate(objects[i].spherical_coords, rotation_distance, 0.00, 0.00);
                }
                break;
            }
            case 115:
            case 66: // down
            {
                x_rotation -= rotation_distance;
                for (int i = 0; i < object_count; i++)
                {
                    rotate(objects[i].spherical_coords, -rotation_distance, 0.0, 0.00);
                }
                break;
            }
            case 100:
            case 67: // right
            {
                y_rotation += rotation_distance;
                for (int i = 0; i < object_count; i++)
                {
                    rotate(objects[i].spherical_coords, 0.0, rotation_distance, 0.00);
                }
                break;
            }
            case 97:
            case 68: // left
            {
                y_rotation -= rotation_distance;
                for (int i = 0; i < object_count; i++)
                {
                    rotate(objects[i].spherical_coords, 0.0, -rotation_distance, 0.0);
                }
                break;
            }
            case 113: // q
            {
                z_rotation -= rotation_distance;
                for (int i = 0; i < object_count; i++)
                {
                    rotate(objects[i].spherical_coords, 0.0, 0.0, -rotation_distance);
                }
                break;
            }
            case 101: // e
            {
                z_rotation += rotation_distance;
                for (int i = 0; i < object_count; i++)
                {
                    rotate(objects[i].spherical_coords, 0.0, 0.0, rotation_distance);
                }
                break;
            }
            case 122: // z
            {
                zoom -= 1;
                if (zoom < 1)
                    zoom = 1;
                break;
            }
            case 120: // x
            {
                zoom++;
                break;
            }
            case 99: // c
            {
                zoom = view_radius * 2;
                break;
            }
            case 90: // shift + z
            {
                view_radius--;
                if (view_radius < 16) view_radius = 16;
                break;
            }
            case 88: // shift + x
            {
                view_radius++;
                break;
            }
            case 61: // +
            {
                rotation_distance += 0.001;
                break;
            }
            case 45: // -
            {
                rotation_distance -= 0.001;
                if (rotation_distance <= 0) rotation_distance = 0.001;
                break;
            }
            case 48: // 0
            {
                rotation_distance = 0.01;
                break;
            }
            case 32: // space
            {
                break;
            }
            case 10: // enter
            {
                break;
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

        std::cout << ansi_escape_codes::reset << std::format(" X: {}    Y: {}   Z: {}   Zoom: {}    Rotation Distance: {}                               ", x_rotation, y_rotation, z_rotation, zoom, rotation_distance);
    }
}