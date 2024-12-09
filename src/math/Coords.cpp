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

#include "Coords.hpp"
#include <random>

CartesianCoordinates
spherical_to_cartesian_coords(SphericalCoordinates spherical_coords) {
    double x = spherical_coords.radius * std::sin(spherical_coords.angle) *
               std::cos(spherical_coords.azimuth);

    double y = spherical_coords.radius * std::sin(spherical_coords.angle) *
               std::sin(spherical_coords.azimuth);

    double z = spherical_coords.radius * std::cos(spherical_coords.angle);

    return CartesianCoordinates{x, y, z};
}

SphericalCoordinates
cartesian_to_spherical_coordinates(CartesianCoordinates cartesian_coords) {
    double radius = std::sqrt(std::pow(cartesian_coords.x, 2) +
                              std::pow(cartesian_coords.y, 2) +
                              std::pow(cartesian_coords.z, 2));
    double angle = std::atan(std::sqrt(std::pow(cartesian_coords.x, 2) +
                                       std::pow(cartesian_coords.y, 2)) /
                             cartesian_coords.z);
    double azimuth = std::atan2(cartesian_coords.y, cartesian_coords.x);

    return SphericalCoordinates(radius, angle, azimuth);
}

void rotate(SphericalCoordinates &spherical_coords, double angle_x,
            double angle_y, double angle_z) {
    CartesianCoordinates cartesian_coords =
        spherical_to_cartesian_coords(spherical_coords);

    double x_rotated_z = cartesian_coords.x * std::cos(angle_z) -
                         cartesian_coords.y * std::sin(angle_z);
    double y_rotated_z = cartesian_coords.x * std::sin(angle_z) +
                         cartesian_coords.y * std::cos(angle_z);
    double z_rotated_z = cartesian_coords.z;

    double x_rotated_y =
        z_rotated_z * std::sin(angle_y) + x_rotated_z * std::cos(angle_y);
    double y_rotated_y = y_rotated_z;
    double z_rotated_y =
        z_rotated_z * std::cos(angle_y) - x_rotated_z * std::sin(angle_y);

    double x_rotated_x = x_rotated_y;
    double y_rotated_x =
        y_rotated_y * std::cos(angle_x) - z_rotated_y * std::sin(angle_x);
    double z_rotated_x =
        y_rotated_y * std::sin(angle_x) + z_rotated_y * std::cos(angle_x);

    spherical_coords = cartesian_to_spherical_coordinates(
        CartesianCoordinates(x_rotated_x, y_rotated_x, z_rotated_x));
}

void rotate(CartesianCoordinates &cartesian_coords, double angle_x,
            double angle_y, double angle_z) {
    double x_rotated_z = cartesian_coords.x * std::cos(angle_z) -
                         cartesian_coords.y * std::sin(angle_z);
    double y_rotated_z = cartesian_coords.x * std::sin(angle_z) +
                         cartesian_coords.y * std::cos(angle_z);
    double z_rotated_z = cartesian_coords.z;

    double x_rotated_y =
        z_rotated_z * std::sin(angle_y) + x_rotated_z * std::cos(angle_y);
    double y_rotated_y = y_rotated_z;
    double z_rotated_y =
        z_rotated_z * std::cos(angle_y) - x_rotated_z * std::sin(angle_y);

    double x_rotated_x = x_rotated_y;
    double y_rotated_x =
        y_rotated_y * std::cos(angle_x) - z_rotated_y * std::sin(angle_x);
    double z_rotated_x =
        y_rotated_y * std::sin(angle_x) + z_rotated_y * std::cos(angle_x);

    cartesian_coords =
        CartesianCoordinates(x_rotated_x, y_rotated_x, z_rotated_x);
}

SphericalCoordinates random_spherical_coords() {
    std::random_device generator{};
    std::uniform_real_distribution radius_dist(4.0, 13.0E9);
    std::uniform_real_distribution angle_azimuth_dist(-360.0, 360.0);

    double radius = radius_dist(generator);

    double angle = angle_azimuth_dist(generator);

    double azimuth = angle_azimuth_dist(generator);

    return SphericalCoordinates(radius, angle, azimuth);
}
