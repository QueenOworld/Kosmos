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

#ifndef COSMIC_OBJECT_H
#define COSMIC_OBJECT_H

#include "math/Coords.hpp"
#include "utils/ansi_escape_code.hpp"
#include <vector>

#define ONE_LIGHTYEAR 3.261563777 // the amount of lightyears in one parsec

struct CosmicObject {
    CosmicObject(SphericalCoordinates);

    SphericalCoordinates spherical_coords;

    long Seed;

    ansi_escape_codes::color_rgb Color;

    const char *Symbol;

    char Class;

    double ApparentMagnitude;

    double AbsoluteMagnitude;

  private:
    static const char *get_symbol(CosmicObject object);

    static ansi_escape_codes::color_rgb get_color(CosmicObject object);

    static char get_class(CosmicObject object);

    static double get_apparent_magnitude(CosmicObject object);

    static double get_absolute_magnitude(CosmicObject object);
};

using viewport_t = std::vector<std::vector<CosmicObject>>;

#endif
