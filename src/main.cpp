#include <iostream>
#include "types/CosmicObject.h"
#include "math/polar.h"
#include "types/Coords.h"
#include <vector>

int main()
{

    std::vector<CosmicObject> objects = std::vector<CosmicObject>(100, CosmicObject({0, 0, 0}));

    for (int i = 0; i < 100; i++)
    {
        objects[i] = CosmicObject(random_spherical_coords());
    }

    while (true)
    {
        std::vector<std::vector<char>> view = std::vector<std::vector<char>>(15, std::vector<char>(15, ' '));

        for (CosmicObject i : objects)
        {
            CartesianCoordinates xyz = spherical_to_cartesian_coords(i.spherical_coords);

            int X = xyz.x * (15 / xyz.z);
            int Y = xyz.y * (15 / xyz.z);
            int Z = xyz.z * (15 / xyz.z);

            if (X >= -7 && X <= 7 && Y >= -7 && Y <= 7 && Z > 1)
            {
                if (i.spherical_coords.radius < 500)
                {
                    view[Y + 7][X + 7] = 'O';
                }
                else if (i.spherical_coords.radius < 1500)
                {
                    view[Y + 7][X + 7] = 'o';
                }
                else
                {
                    view[Y + 7][X + 7] = '.';
                }
            }
        }

        for (int row = 0; row < 15; row++)
        {
            for (int col = 0; col < 15; col++)
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