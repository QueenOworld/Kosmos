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

    long Seed; // i don't understand how to make a member const when it deletes
               // the copy assignment operator, making it impossible to assign
               // to game::cosmic_objects.

    const char *get_symbol() const;

    const ansi_escape_codes::color_n get_color() const;

    const char get_class() const;

    const double get_apparent_magnitude() const;

    const double get_absolute_magnitude() const;

    // there is no point in recalculating all of these when its value will never
    // be different, but like i said above i have no idea how to make them const
    // members without anything breaking. all i want to convey is that it'll
    // always be the same value once assigned.
};

using viewport_t = std::vector<std::vector<CosmicObject>>;

#endif
