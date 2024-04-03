/**
 * @file Border.h
 * @author ayano
 * @date 03/04/24
 * @brief Border utility to avoid multiple window creation, along with some predefined borders
 */

#ifndef TANOSHIIEDITOR_BORDER_H
#define TANOSHIIEDITOR_BORDER_H

#include <ncurses.h>

struct Border {
    chtype ls, rs, ts, bs, tl, tr, bl, br;
};

constexpr Border DEFAULT_BORDER = Border{'|', '|', '-', '-', '+', '+', '+', '+'};
constexpr Border EMPTY_BORDER = Border{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

#endif // TANOSHIIEDITOR_BORDER_H