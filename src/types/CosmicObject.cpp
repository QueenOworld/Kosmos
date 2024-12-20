/*
Kosmos is a 3D TUI game about space.
Copyright (C) 2024 - queenoworld

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "CosmicObject.hpp"
#include "math/Coords.hpp"
#include "utils/ansi_escape_code.hpp"
#include <bit>
#include <cmath>
#include <cstdlib>
#include <math.h>
#include <random>

CosmicObject::CosmicObject(SphericalCoordinates spherical_coordinates) {
    spherical_coords = spherical_coordinates;

    Seed = std::bit_cast<long>(spherical_coordinates.radius) +
           (std::bit_cast<long>(spherical_coordinates.angle) << 21) +
           (std::bit_cast<long>(spherical_coordinates.azimuth) << 42);
}

const char *CosmicObject::get_symbol() const {
    if (Seed == 0)
        return "  ";
    const char *symbols[28] = {". ", "* ", "✧ ", "✦ ", "⋆ ", "✴ ", "✵ ",
                               "✶ ", "✷ ", "✸ ", "✹ ", "❂ ", "᠅ ", "◌ ",
                               " .", " *", " ✧", " ✦", " ⋆", " ✴", " ✵",
                               " ✶", " ✷", " ✸", " ✹", " ❂", " ᠅", " ◌"};
    return symbols[std::abs(Seed) % 28];
}

const ansi_escape_codes::color_n CosmicObject::get_color() const {
    const int colors[31] = {232, 222, 223, 117, 228, 229, 195, 229,
                            230, 231, 235, 236, 237, 238, 239, 240,
                            241, 242, 243, 244, 245, 246, 247, 248,
                            249, 250, 251, 252, 253, 254, 255};
    std::srand(Seed);

    return ansi_escape_codes::color_n(colors[rand() % 31]);
}

const char CosmicObject::get_class() const {
    const char *classes = "MKGFABO";
    return classes[std::abs(Seed - 20) % 7];
}

const double CosmicObject::get_apparent_magnitude() const {
    std::uniform_real_distribution<double> random_magnitude(-2.0, 35.0);
    std::mt19937_64 random_generator{std::bit_cast<uint64_t>(Seed - 1312)};
    return random_magnitude(random_generator);
}

const double CosmicObject::get_absolute_magnitude() const {
    return get_apparent_magnitude() -
           5 * std::log10((spherical_coords.radius / ONE_LIGHTYEAR) - 1);
}
