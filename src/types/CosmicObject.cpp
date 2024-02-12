#include "CosmicObject.hpp"
#include <math.h>
#include <string>
#include <bit>
#include "../utils/ansi_escape_code.hpp"

CosmicObject::CosmicObject(SphericalCoordinates spherical_coordinates)
{
    spherical_coords = spherical_coordinates;

    Seed = std::bit_cast<long>(spherical_coordinates.radius) + (std::bit_cast<long>(spherical_coordinates.angle) << 21) + (std::bit_cast<long>(spherical_coordinates.azimuth) << 42);
}

const char *CosmicObject::get_symbol()
{
    const char *symbols[14] = {".", "*", "✧", "✦", "⋆", "✴", "✵", "✶", "✷", "✸", "✹", "❂", "᠅", "◌"};
    return symbols[std::abs(Seed) % 14];
}

ansi_escape_codes::color_n CosmicObject::get_color()
{
    const int colors[29] = {11, 117, 193, 194, 195, 229, 230, 231, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255};
    std::srand(Seed);

    return ansi_escape_codes::color_n(colors[rand() % 29]);
}