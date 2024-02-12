#ifndef COSMIC_OBJECT_H
#define COSMIC_OBJECT_H

#include "../math/Coords.hpp"
#include "../utils/ansi_escape_code.hpp"

struct CosmicObject
{
    CosmicObject(SphericalCoordinates);

    SphericalCoordinates spherical_coords;

    long Seed;

    const char* get_symbol();

    ansi_escape_codes::color_n get_color();
};

#endif