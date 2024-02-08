#include <iostream>
#include "./types/CosmicObject.h"
#include "./math/polar.h"
#include <vector>

int main()
{
    std::vector<std::vector<std::vector<CosmicObject>>> Universe(511, std::vector<std::vector<CosmicObject>>(511, std::vector<CosmicObject>(512, CosmicObject(0, 0, 0))));

    for (int i = 0; i < 100; i++) {
        std::vector<int> coords = spherical_to_cartesian_coords(random_spherical_coords());
        std::cout << coords[0] << " " << coords[1] << " " << coords[2] << std::endl;
    }
}