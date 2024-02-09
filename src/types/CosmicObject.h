#ifndef COSMIC_OBJECT_H
#define COSMIC_OBJECT_H

#include "Coords.h"
#include <bit>

struct CosmicObject
{
    CosmicObject(SphericalCoordinates spherical_coordinates)
    {
        spherical_coords = spherical_coordinates;

        Seed = std::bit_cast<long>(spherical_coordinates.radius) + (std::bit_cast<long>(spherical_coordinates.angle) << 20) + (std::bit_cast<long>(spherical_coordinates.azimuth) << 30);
    }

    SphericalCoordinates spherical_coords;

    long Seed;
};

#endif