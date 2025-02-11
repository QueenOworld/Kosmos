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
#include <random>
#include <sys/types.h>

CosmicObject::CosmicObject(SphericalCoordinates spherical_coordinates)
    : spherical_coords(spherical_coordinates),
      Seed(std::bit_cast<long>(spherical_coordinates.radius) +
           (std::bit_cast<long>(spherical_coordinates.angle) << 21) +
           (std::bit_cast<long>(spherical_coordinates.azimuth) << 42)),
      Color(get_color(*this)) {
    Symbol = get_symbol(*this);

    Class = get_class(*this);

    ApparentMagnitude = get_apparent_magnitude(*this);

    AbsoluteMagnitude = get_absolute_magnitude(*this);
}

const char *CosmicObject::get_symbol(CosmicObject object) {
    if (object.Seed == 0)
        return "  ";

    const char *symbols[44] = {
        ". ", "* ", "🟄 ", "🟅 ", "🟆 ", "🟉 ", "🟋 ", "🟎 ", "🟐 ", "🟒 ", "🟓 ",
        "🞄 ", "🞗 ", "✦ ", "⋆ ", "● ", "⯌ ", "‧ ", "․ ", "∙ ", "⋆ ", "⦁ ",
        " .", " *", " 🟄", " 🟅", " 🟆", " 🟉", " 🟋", " 🟎", " 🟐", " 🟒", " 🟓",
        " 🞄", " 🞗", " ✦", " ⋆", " ●", " ⯌", " ‧", " ․", " ∙", " ⋆", " ⦁"};

    return symbols[std::abs(object.Seed) % 44];
}

ansi_escape_codes::color_rgb CosmicObject::get_color(CosmicObject object) {
    double x;
    double y;

    std::srand(object.Seed);

    ulong T = 1000 + rand() % 24001;

    if (T <= 15000) {
        double u = (0.860117757 + 1.54118254 * 0.0001 * T +
                    1.28641212 * 0.0000001 * std::pow(T, 2)) /
                   (1 + 8.42420235 * 0.0001 * T +
                    7.08145163 * 0.0000001 * std::pow(T, 2));

        double v = (0.317398726 + 4.22806245 * 0.00001 * T +
                    4.20481681 * 0.00000001 * std::pow(T, 2)) /
                   (1 - 2.89741816 * 0.00001 * T +
                    1.61456053 * 0.0000001 * std::pow(T, 2));

        x = (3 * u) / (2 * u - 8 * v + 4);

        y = (2 * v) / (2 * u - 8 * v + 4);
    } else {
        x = -3.0258469 * (1000000000 / std::pow(T, 3)) +
            2.1070379 * (1000000 / std::pow(T, 2)) + 0.2226347 * (1000.0 / T) +
            0.240390;
        y = 3.0817580 * std::pow(x, 3) - 5.87338670 * std::pow(x, 2) +
            3.75112997 * x - 0.37001483;
    }

    double r = x * 1.656492 - y * 0.354851 - (1.0 - x - y) * 0.255038;
    double g = -x * 0.707196 + y * 1.655397 + (1.0 - x - y) * 0.036152;
    double b = x * 0.051713 - y * 0.121364 + (1.0 - x - y) * 1.011530;

    r = r <= 0.0031308 ? 12.92 * r
                       : (1.0 + 0.055) * std::pow(r, (1.0 / 2.4)) - 0.055;

    g = g <= 0.0031308 ? 12.92 * g
                       : (1.0 + 0.055) * std::pow(g, (1.0 / 2.4)) - 0.055;

    b = b <= 0.0031308 ? 12.92 * b
                       : (1.0 + 0.055) * std::pow(b, (1.0 / 2.4)) - 0.055;

    r = std::max(r, 0.0);
    g = std::max(g, 0.0);
    b = std::max(b, 0.0);

    double max = std::max(std::max(r, g), b);

    if (max > 1) {
        r = r / max;
        g = g / max;
        b = b / max;
    }

    r = std::floor(r * 255);
    g = std::floor(g * 255);
    b = std::floor(b * 255);

    return ansi_escape_codes::color_rgb((unsigned char)r, (unsigned char)g,
                                        (unsigned char)b);
}

char CosmicObject::get_class(CosmicObject object) {
    const char *classes = "MKGFABO";
    return classes[std::abs(object.Seed - 20) % 7];
}

double CosmicObject::get_apparent_magnitude(CosmicObject object) {
    std::uniform_real_distribution<double> random_magnitude(-2.0, 35.0);
    std::mt19937_64 random_generator{
        std::bit_cast<uint64_t>(object.Seed - 1312)};
    return random_magnitude(random_generator);
}

double CosmicObject::get_absolute_magnitude(CosmicObject object) {
    return get_apparent_magnitude(object) -
           5 * std::log10((object.spherical_coords.radius / ONE_LIGHTYEAR) - 1);
}
