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
#include "utils/game.hpp"
#include "utils/input.hpp"
#include "utils/tui.hpp"
#include <iostream>

int main() {
    Game game(500);

    while (true) {
        game.draw();
        game.step();
    }
}
