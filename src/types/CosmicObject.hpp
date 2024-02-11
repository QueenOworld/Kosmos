#ifndef COSMIC_OBJECT_H
#define COSMIC_OBJECT_H

#include "../math/Coords.hpp"
#include <bit>

struct CosmicObject
{
    CosmicObject(SphericalCoordinates spherical_coordinates)
    {
        spherical_coords = spherical_coordinates;

        Seed = std::bit_cast<long>(spherical_coordinates.radius) + (std::bit_cast<long>(spherical_coordinates.angle) << 21) + (std::bit_cast<long>(spherical_coordinates.azimuth) << 42);
    }

    SphericalCoordinates spherical_coords;

    long Seed;
};

#endif