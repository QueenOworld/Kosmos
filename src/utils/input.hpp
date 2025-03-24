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

#ifndef INPUT_H
#define INPUT_H

int getch(bool);
int kbhit();

enum input_codes {
    UP = 65,
    DOWN = 66,
    RIGHT = 67,
    LEFT = 68,
    KEY_W = 119,
    KEY_S = 115,
    KEY_D = 100,
    KEY_A = 97,
    KEY_Q = 113,
    KEY_E = 101,
    KEY_Z = 122,
    KEY_X = 120,
    KEY_C = 99,
    KEY_SHIFT_Z = 90,
    KEY_SHIFT_X = 88,
    KEY_PLUS = 61,
    KEY_MINUS = 45,
    KEY_ZERO = 48,
    KEY_SPACE = 32,
    KEY_ENTER = 10,
};

#endif
