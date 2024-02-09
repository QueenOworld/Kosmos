#include "polar.h"
#include <random>
#include "../types/Coords.h"

CartesianCoordinates spherical_to_cartesian_coords(SphericalCoordinates spherical_coords)
{
    double x = spherical_coords.radius * std::sin(spherical_coords.angle) * std::cos(spherical_coords.azimuth);
    
    double y = spherical_coords.radius * std::sin(spherical_coords.angle) * std::sin(spherical_coords.azimuth);

    double z = spherical_coords.radius * std::cos(spherical_coords.angle);

    return CartesianCoordinates{x, y, z};
}

SphericalCoordinates random_spherical_coords()
{
    std::random_device generator{};
    std::uniform_real_distribution radius_dist(50.0, 2000.0);
    std::uniform_real_distribution angle_azimuth_dist(-360.0, 360.0);

    double radius = radius_dist(generator);

    double angle = angle_azimuth_dist(generator);
    
    double azimuth = angle_azimuth_dist(generator);

    return SphericalCoordinates{radius, angle, azimuth};
}