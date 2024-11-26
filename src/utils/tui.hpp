#pragma once

#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

namespace tui {
inline struct winsize wsize;

void resize_window(int signum);
void draw_border(char border_char);
void draw_border(wchar_t border_char);
void draw_border(std::string border_string);
void draw_border(char tl_corner, char top, char tr_corner, char right,
                 char br_corner, char bottom, char bl_corner, char left);
void draw_border(wchar_t tl_corner, wchar_t top, wchar_t tr_corner,
                 wchar_t right, wchar_t br_corner, wchar_t bottom,
                 wchar_t bl_corner, wchar_t left);
void draw_border(std::string tl_corner, std::string top, std::string tr_corner,
                 std::string right, std::string br_corner, std::string bottom,
                 std::string bl_corner, std::string left);
}; // namespace tui
