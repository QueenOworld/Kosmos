#ifndef POLAR_H
#define POLAR_H

#include "../types/Coords.h"

CartesianCoordinates spherical_to_cartesian_coords(SphericalCoordinates);
SphericalCoordinates random_spherical_coords();

#endif