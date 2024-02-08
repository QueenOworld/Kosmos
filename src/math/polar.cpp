#include "polar.h"
#include <vector>
#include <random>

std::vector<int> spherical_to_cartesian_coords(std::vector<double> spherical_coords) {
    std::vector<int> cartesian_coords = std::vector<int>(3, 0);

    float radius = spherical_coords[0];
    float angle = spherical_coords[1];
    float azimuth = spherical_coords[2];

    // x
    cartesian_coords[0] = static_cast<int>(radius * std::sin(angle) * std::cos(azimuth));
    // y
    cartesian_coords[1] = static_cast<int>(radius * std::sin(angle) * std::sin(azimuth));
    // z
    cartesian_coords[2] = static_cast<int>(radius * std::cos(angle));

    return cartesian_coords;
}

std::vector<double> random_spherical_coords() {
    std::random_device generator{};
    std::uniform_real_distribution radius_dist(10.0, 255.0);
    std::uniform_real_distribution angle_azimuth_dist(-360.0, 360.0);

    std::vector<double> spherical_coords = std::vector<double>(3, 0.0);

    float radius = radius_dist(generator);
    float angle = angle_azimuth_dist(generator);
    float azimuth = angle_azimuth_dist(generator);

    spherical_coords[0] = radius;
    spherical_coords[1] = angle;
    spherical_coords[2] = azimuth;

    return spherical_coords;
}