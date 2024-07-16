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

#ifndef COORDINATES_H
#define COORDINATES_H

struct SphericalCoordinates
{
    double radius, angle, azimuth;
};

struct CartesianCoordinates
{
    double x, y, z;
};

struct RectangularCoordinates
{
    double x, y;
};

CartesianCoordinates spherical_to_cartesian_coords(SphericalCoordinates);
SphericalCoordinates cartesian_to_spherical_coordinates(CartesianCoordinates);
SphericalCoordinates random_spherical_coords();

void rotate(SphericalCoordinates&, double, double, double);

void rotate(CartesianCoordinates&, double, double, double);

#endif