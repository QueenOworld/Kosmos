#include <iostream>
#include "types/CosmicObject.h"
#include "math/polar.h"
#include "types/Coords.h"

int main()
{
    for (int i = 0; i < 100; i++) {
        SphericalCoordinates coords = random_spherical_coords();
        CosmicObject a = CosmicObject(coords);

        std::cout << coords.radius << " "  << coords.angle << " " << coords.azimuth << "    " << a.Seed << std::endl;
    }
}