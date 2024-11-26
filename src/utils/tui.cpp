#include "tui.hpp"
#include <iostream>
#include <string>

inline std::string repeat(uint32_t num, const std::string &input) {
    std::string ret;
    ret.reserve(input.size() * num);
    for (int8_t index = 31; index >= 0; index--)
        if (num >> index) {
            ret += ret;
            if ((num >> index) % 2) {
                ret += input;
            }
        }
    return ret;
}

void tui::resize_window(int signum) {
    tui::draw_border("╭", "─", "╮", "│", "╯", "─", "╰", "│");
}

void tui::draw_border(char border_char) {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);

    std::cout << "\033[0;0f";

    for (int row = 0; row < wsize.ws_row; row++) {
        if (row == 0) {
            std::cout << std::string(wsize.ws_col, border_char) << '\n';
        } else if (row == wsize.ws_row - 1) {
            std::cout << std::string(wsize.ws_col, border_char);
        } else {
            std::cout << border_char << std::string(wsize.ws_col - 2, ' ')
                      << border_char << '\n';
        }
    }
}

void tui::draw_border(wchar_t border_char) {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);

    std::wcout << "\033[0;0f";

    for (int row = 0; row < wsize.ws_row; row++) {
        if (row == 0) {
            std::wcout << std::wstring(wsize.ws_col, border_char) << '\n';
        } else if (row == wsize.ws_row - 1) {
            std::wcout << std::wstring(wsize.ws_col, border_char);
        } else {
            std::wcout << border_char << std::wstring(wsize.ws_col - 2, ' ')
                       << border_char << '\n';
        }
    }
}

void tui::draw_border(std::string border_string) {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);

    std::cout << "\033[0;0f";

    for (int row = 0; row < wsize.ws_row; row++) {
        if (row == 0) {
            std::cout << repeat(wsize.ws_col, border_string) << '\n';
        } else if (row == wsize.ws_row - 1) {
            std::cout << repeat(wsize.ws_col, border_string);
        } else {
            std::cout << border_string << std::string(wsize.ws_col - 2, ' ')
                      << border_string << '\n';
        }
    }
}

void tui::draw_border(char tl_corner, char top, char tr_corner, char right,
                      char br_corner, char bottom, char bl_corner, char left) {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);

    std::cout << "\033[0;0f";

    for (int row = 0; row < wsize.ws_row; row++) {
        if (row == 0) {
            std::cout << tl_corner << std::string(wsize.ws_col - 2, top)
                      << tr_corner << '\n';
        } else if (row == wsize.ws_row - 1) {
            std::cout << bl_corner << std::string(wsize.ws_col - 2, bottom)
                      << br_corner;
        } else {
            std::cout << left << std::string(wsize.ws_col - 2, ' ') << right
                      << '\n';
        }
    }
}

void tui::draw_border(std::string tl_corner, std::string top,
                      std::string tr_corner, std::string right,
                      std::string br_corner, std::string bottom,
                      std::string bl_corner, std::string left) {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);

    std::string buffer = "\033[0;0f";

    for (int row = 0; row < wsize.ws_row; row++) {
        if (row == 0) {
            buffer +=
                tl_corner + repeat(wsize.ws_col - 2, top) + tr_corner + '\n';
        } else if (row == wsize.ws_row - 1) {
            buffer += bl_corner + repeat(wsize.ws_col - 2, bottom) + br_corner;
        } else {
            buffer += left + std::string(wsize.ws_col - 2, ' ') + right + '\n';
        }
    }

    std::cout << buffer << std::flush;
}

void tui::draw_border(wchar_t tl_corner, wchar_t top, wchar_t tr_corner,
                      wchar_t right, wchar_t br_corner, wchar_t bottom,
                      wchar_t bl_corner, wchar_t left) {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);

    std::wcout << "\033[0;0f";

    for (int row = 0; row < wsize.ws_row; row++) {
        if (row == 0) {
            std::wcout << tl_corner << std::wstring(wsize.ws_col - 2, top)
                       << tr_corner << '\n';
        } else if (row == wsize.ws_row - 1) {
            std::wcout << bl_corner << std::wstring(wsize.ws_col - 2, bottom)
                       << br_corner;
        } else {
            std::wcout << left << std::wstring(wsize.ws_col - 2, ' ') << right
                       << '\n';
        }
    }
}
