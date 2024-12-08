#pragma once

#include "types/CosmicObject.hpp"
#include <iostream>
#include <sstream>
#include <sys/ioctl.h>
#include <vector>

class Game {
    int object_count;
private:
    std::vector<CosmicObject> cosmic_objects;

    static inline struct winsize wsize;

    int view_radius;

    int zoom;

    double x_rotation;
    double y_rotation;
    double z_rotation;

    double rotation_distance;

    static void redraw(int signum);

    static Game *me;

  public:
    Game(int object_count);
    void draw();
    void step();
};