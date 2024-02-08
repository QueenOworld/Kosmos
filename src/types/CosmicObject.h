#ifndef COSMIC_OBJECT_H
#define COSMIC_OBJECT_H

#include "Coords.h"

struct CosmicObject
{
    CosmicObject(SphericalCoordinates spherical_coordinates)
    {
        spherical_coords = spherical_coordinates;

        Seed = spherical_coordinates.radius + (static_cast<long>(spherical_coordinates.angle) << 20) + (static_cast<long>(spherical_coordinates.azimuth) << 30);
    }

    SphericalCoordinates spherical_coords;

    long Seed;
};

#endif