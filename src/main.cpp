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

#include "math/Coords.hpp"
#include "types/CosmicObject.hpp"
#include "utils/ansi_escape_code.hpp"
#include "utils/input.hpp"
#include <atomic>
#include <format>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <vector>

int main() {
  std::system("clear");

  const int object_count = 500;

  int view_radius = 35;

  int zoom = view_radius * 2;

  int input = 0;

  double x_rotation = 0.0;
  double y_rotation = 0.0;
  double z_rotation = 0.0;

  double rotation_distance = 0.1;

  std::vector<CosmicObject> objects =
      std::vector<CosmicObject>(object_count, CosmicObject({0, 0, 0}));

  for (int i = 0; i < object_count; i++) {
    objects[i] = CosmicObject(random_spherical_coords());
  }

  while (true) {
    std::vector<std::vector<CosmicObject>> view =
        std::vector<std::vector<CosmicObject>>(
            2 * view_radius + 1,
            std::vector<CosmicObject>(2 * view_radius + 1,
                                      CosmicObject({0, 0, 0})));

    for (CosmicObject i : objects) {
      CartesianCoordinates xyz =
          spherical_to_cartesian_coords(i.spherical_coords);

      double X = xyz.x * (zoom / (zoom - xyz.z));
      double Y = xyz.y * (zoom / (zoom - xyz.z));

      if (X >= -(view_radius) && X <= view_radius && Y >= -(view_radius) &&
          Y <= view_radius) {
        view[Y + view_radius][X + view_radius] = i;
      }
    }

    std::cout << "\033[0;0f";

    for (int row = 0; row < 2 * view_radius + 1; row++) {
      for (int col = 0; col < 2 * view_radius + 1; col++) {
        if ((row == view_radius || col == view_radius) &&
            !(row == view_radius && col == view_radius)) {
          std::cout << ansi_escape_codes::color_bg_n(233)
                    << view[row][col].get_color()
                    << view[row][col].get_symbol();
        } else if (row == view_radius && col == view_radius) {
          std::cout << ansi_escape_codes::color_bg_n(232)
                    << ansi_escape_codes::slow_blink_opcode()
                    << view[row][col].get_color() << view[row][col].get_symbol()
                    << ansi_escape_codes::blink_off_opcode();
        } else {
          std::cout << ansi_escape_codes::color_bg_n(232)
                    << view[row][col].get_color()
                    << view[row][col].get_symbol();
        }
      }
      std::cout << '\n';
    }

    std::cout << std::endl;

    input = getch_echo(false);

    switch (input) {
    case 119:
    case 65: // up
    {
      x_rotation += rotation_distance;
      for (int i = 0; i < object_count; i++) {
        rotate(objects[i].spherical_coords, rotation_distance * (M_PI / 180),
               0.00, 0.0);
      }
      break;
    }
    case 115:
    case 66: // down
    {
      x_rotation -= rotation_distance;
      for (int i = 0; i < object_count; i++) {
        rotate(objects[i].spherical_coords, -rotation_distance * (M_PI / 180),
               0.0, 0.0);
      }
      break;
    }
    case 100:
    case 67: // right
    {
      y_rotation += rotation_distance;
      for (int i = 0; i < object_count; i++) {
        rotate(objects[i].spherical_coords, 0.0,
               rotation_distance * (M_PI / 180), 0.0);
      }
      break;
    }
    case 97:
    case 68: // left
    {
      y_rotation -= rotation_distance;
      for (int i = 0; i < object_count; i++) {
        rotate(objects[i].spherical_coords, 0.0,
               -rotation_distance * (M_PI / 180), 0.0);
      }
      break;
    }
    case 113: // q
    {
      z_rotation -= rotation_distance;
      for (int i = 0; i < object_count; i++) {
        rotate(objects[i].spherical_coords, 0.0, 0.0,
               -rotation_distance * (M_PI / 180));
      }
      break;
    }
    case 101: // e
    {
      z_rotation += rotation_distance;
      for (int i = 0; i < object_count; i++) {
        rotate(objects[i].spherical_coords, 0.0, 0.0,
               rotation_distance * (M_PI / 180));
      }
      break;
    }
    case 122: // z
    {
      zoom -= 1;
      if (zoom < 1)
        zoom = 1;
      break;
    }
    case 120: // x
    {
      zoom++;
      break;
    }
    case 99: // c
    {
      zoom = view_radius * 2;
      break;
    }
    case 90: // shift + z
    {
      view_radius--;
      if (view_radius < 16)
        view_radius = 16;

      std::cout << "\033[0;0f";
      for (int row = 0; row < 2 * view_radius + 1; row++) {
        for (int col = 0; col < 2 * view_radius + 1; col++) {
          std::cout << ansi_escape_codes::default_background_color << "  ";
        }
        std::cout << '\n';
      }

      std::cout << std::endl;

      std::system("clear");
      break;
    }
    case 88: // shift + x
    {
      view_radius++;

      std::cout << "\033[0;0f";
      for (int row = 0; row < 2 * view_radius + 1; row++) {
        for (int col = 0; col < 2 * view_radius + 1; col++) {
          std::cout << ansi_escape_codes::default_background_color << "  ";
        }
        std::cout << '\n';
      }

      std::cout << std::endl;

      std::system("clear");
    }
    case 61: // +
    {
      rotation_distance += 0.1;
      break;
    }
    case 45: // -
    {
      rotation_distance -= 0.1;
      if (rotation_distance <= 0)
        rotation_distance = 0.1;
      break;
    }
    case 48: // 0
    {
      rotation_distance = 0.1;
      break;
    }
    case 32: // space
    {
      CosmicObject *target = &view[view_radius][view_radius];
      if ((*target).Seed != 0) {
        std::cout << "\033[0;0f" << ansi_escape_codes::white_color() << "Info"
                  << "\nSeed: " << (*target).Seed
                  << "\nClass: " << (*target).get_class()
                  << "\nColor: " << (*target).get_color() << "#";
      }
      getch_echo(false);
      break;
    }
    case 10: // enter
    {
      CosmicObject *target = &view[view_radius][view_radius];
      
      break;
    }
    }

    if (std::abs(x_rotation) >= 360) {
      x_rotation = 0;
    } else if (std::abs(x_rotation) < 0) {
      x_rotation = M_PI;
    }

    if (std::abs(y_rotation) >= 360) {
      y_rotation = 0;
    } else if (std::abs(y_rotation) < 0) {
      y_rotation = M_PI;
    }

    if (std::abs(z_rotation) >= 360) {
      z_rotation = 0;
    } else if (std::abs(z_rotation) < 0) {
      z_rotation = M_PI;
    }

    std::cout << ansi_escape_codes::reset
              << std::format(
                     " X: {}    Y: {}   Z: {}   Zoom: {}    Rotation "
                     "Distance: {}  Seed: {}                               ",
                     x_rotation, y_rotation, z_rotation, zoom,
                     rotation_distance, view[view_radius][view_radius].Seed);
  }
}
