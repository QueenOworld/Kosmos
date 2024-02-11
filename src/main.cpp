#include <iostream>
#include "types/CosmicObject.hpp"
#include "math/Coords.hpp"
#include <vector>
#include "utils/input.hpp"
#include "utils/ansi_escape_code.hpp"

int main()
{
    // while (true)
    // {
    //     std::cout << getch_echo(false) << "\n";
    // }

    int view_radius = 15;

    int input = 0;

    std::vector<CosmicObject> objects = std::vector<CosmicObject>(5000, CosmicObject({0, 0, 0}));

    for (int i = 0; i < 5000; i++)
    {
        objects[i] = CosmicObject(random_spherical_coords());
    }

    while (true)
    {
        std::vector<std::vector<char>> view = std::vector<std::vector<char>>(2 * view_radius + 1, std::vector<char>(2 * view_radius + 1, ' '));

        for (CosmicObject i : objects)
        {
            CartesianCoordinates xyz = spherical_to_cartesian_coords(i.spherical_coords);

            int X = xyz.x / (i.spherical_coords.radius - xyz.z);
            int Y = xyz.y / (i.spherical_coords.radius - xyz.z);

            if (X >= -(view_radius) && X <= view_radius && Y >= -(view_radius) && Y <= view_radius && xyz.z > 1)
            {
                if (i.spherical_coords.radius < 30000)
                {
                    view[Y + view_radius][X + view_radius] = '3';
                }
                else if (i.spherical_coords.radius < 60000)
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

        switch (input)
        {
            case 119:
            case 72:
            case 65: // up
            {
                for (int i = 0; i < 100; i++)
                {
                    rotate(objects[i].spherical_coords, 0.02, 0.0, 0.0);
                }
            }
            case 115:
            case 80:
            case 66: // down
            {
                for (int i = 0; i < 100; i++)
                {
                    rotate(objects[i].spherical_coords, -0.01, 0.0, 0.0);
                }
            }
            case 100:
            case 77:
            case 67: // right
            {
                for (int i = 0; i < 100; i++)
                {
                    rotate(objects[i].spherical_coords, 0.0, 0.02, 0.0);
                }
            }
            case 97:
            case 75:
            case 68: // left
            {
                for (int i = 0; i < 100; i++)
                {
                    rotate(objects[i].spherical_coords, 0.0, -0.01, 0.0);
                }
            }
            case 113: // q
            {
                for (int i = 0; i < 100; i++)
                {
                    rotate(objects[i].spherical_coords, 0.0, 0.0, -0.02);
                }
            }
            case 101: // e
            {
                for (int i = 0; i < 100; i++)
                {
                    rotate(objects[i].spherical_coords, 0.0, 0.0, +0.01);
                }
            }
            default:
            {
                std::cout << input;
            }
        }

        input = getch_echo(false);
    }
}