#include <iostream>
#include "types/CosmicObject.h"
#include "math/polar.h"
#include "types/Coords.h"
#include <vector>

int main()
{
    int view_radius = 10;

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

            int X = xyz.x * (1 / xyz.z);
            int Y = xyz.y * (1 / xyz.z);
            int Z = xyz.z * (1 / xyz.z);

            if (X >= -(view_radius) && X <= view_radius && Y >= -(view_radius) && Y <= view_radius && xyz.z > 1)
            {
                if (i.spherical_coords.radius < 3000)
                {
                    view[Y + view_radius][X + view_radius] = 'O';
                }
                else if (i.spherical_coords.radius < 6000)
                {
                    view[Y + view_radius][X + view_radius] = 'o';
                }
                else
                {
                    view[Y + view_radius][X + view_radius] = '.';
                }
            }
        }

        for (int row = 0; row < 2 * view_radius + 1; row++)
        {
            for (int col = 0; col < 2 * view_radius + 1; col++)
            {
                std::cout << view[row][col] << ' ';
            }
            std::cout << '\n';
        }

        std::cin.ignore();

        for (int i = 0; i < 100; i++)
        {
            objects[i].spherical_coords.angle += 0.01;
        }
    }
}