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

CartesianCoordinates spherical_to_cartesian_coords(SphericalCoordinates);
SphericalCoordinates cartesian_to_spherical_coordinates(CartesianCoordinates);
SphericalCoordinates random_spherical_coords();

void rotate(SphericalCoordinates&, double, double, double);

void rotate(CartesianCoordinates&, double, double, double);

#endif