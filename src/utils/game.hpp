#pragma once

#include "types/CosmicObject.hpp"
#include <sys/ioctl.h>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#endif

class Game {
    const int object_count;

  private:
    std::vector<CosmicObject> cosmic_objects;

#ifdef __unix__
    static inline struct winsize wsize;
#endif

#ifdef _WIN32
    static inline CONSOLE_SCREEN_BUFFER_INFO csbi;
#endif

    int view_radius;

    int zoom;

    double x_rotation;
    double y_rotation;
    double z_rotation;

    double rotation_distance;

    static void redraw(int signum);

    static Game *me;

  public:
    Game(const int object_count);
    void draw();
    void step();
};
