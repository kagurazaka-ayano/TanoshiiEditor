/**
 * @file Window.cpp
 * @author ayano
 * @date 03/04/24
 * @brief Implementation of window classes
 */

#include "Window.h"
#include "Border.hpp"
#include <cstddef>
#include <fmt/core.h>
#include <ncurses.h>
#include <stdexcept>

std::size_t BaseWindow::getWidth() const
{
    return window_width;
}

std::size_t BaseWindow::getHeight() const
{
    return window_height;
}

std::size_t BaseWindow::getMaxWidth() const
{
    return max_width;
}

std::size_t BaseWindow::getMaxHeight() const
{
    return max_height;
}
std::size_t BaseWindow::getX() const
{
    return x;
}
std::size_t BaseWindow::getY() const
{
    return y;
}

PANEL* BaseWindow::getAssociatedPanel() const
{
    return associated_panel;
}

WINDOW* BaseWindow::getWindowPtr() const
{
    return window_ptr;
}

Border BaseWindow::getBorder() const
{
    return window_border;
}

std::string BaseWindow::getName() const
{
    return name;
}

void BaseWindow::refreshWindow()
{
    makeBorder();
    wrefresh(window_ptr);
}

bool BaseWindow::validifyWindow()
{
    return (window_height < max_height && window_width < max_width);
}

void BaseWindow::eraseWindow()
{
    wborder(window_ptr, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    for (int i = 0; i < window_width; ++i) {
        for (int j = 0; j < window_height; ++j) {
            mvwaddch(window_ptr, j, i, ' ');
        }
    }
    wrefresh(window_ptr);
}

void BaseWindow::killWindow()
{
    if (window_ptr != nullptr) {
        eraseWindow();
        delwin(window_ptr);
        window_ptr = nullptr;
    }
}

void BaseWindow::redrawWindow()
{
    eraseWindow();
    makeBorder();
    makeWindowLabel();
    wrefresh(window_ptr);
}

void BaseWindow::makeBorder()
{
    wborder(window_ptr, window_border.ls, window_border.rs, window_border.ts, window_border.bs, window_border.tl, window_border.tr, window_border.bl, window_border.br);
    wrefresh(window_ptr);
}

void BaseWindow::makeWindowLabel()
{
    mvwprintw(window_ptr, window_height - 1, 1, name.data());
    wrefresh(window_ptr);
}

BaseWindow::BaseWindow(const Border& borders, const std::string& name, std::size_t width, std::size_t height, PANEL* associated_panel, std::size_t init_x, std::size_t init_y, std::size_t max_width, std::size_t max_height)
    : window_height(height)
    , window_width(width)
    , x(init_x)
    , y(init_y)
    , window_border(borders)
    , associated_panel(associated_panel)
    , max_height(max_height)
    , max_width(max_width)
    , name(name)
{
    if (!validifyWindow())
        throw std::runtime_error(fmt::format(
            "ERROR: Window {} doesn't match dimension requirement, expected max dimension: ({}, {}), found ({}, {})",
            name, max_width, max_height, window_width, window_height));
    window_ptr = newwin(height, width, x, y);
    makeBorder();
    makeWindowLabel();
    wrefresh(window_ptr);
}

BaseWindow::~BaseWindow()
{
    killWindow();
}


void BaseWindow::updateBorder(const Border& borders)
{
    window_border = borders;
    makeBorder();
    wrefresh(window_ptr);
}

void BaseWindow::updateDimension(std::size_t width, std::size_t height)
{
    window_width = width;
    window_height = height;
    if (!validifyWindow())
        throw std::runtime_error(fmt::format(
            "ERROR: Window {} doesn't match dimension requirement, expected max dimension: ({}, {}), found ({}, {})",
            name, max_width, max_height, window_width, window_height));
    wresize(window_ptr, window_height, window_width);
    redrawWindow(); 
}

void BaseWindow::moveTo(std::size_t x, std::size_t y)
{
    this->x = x;
    this->y = y;
    eraseWindow();
    mvwin(window_ptr, x, y);
    makeBorder();
    makeWindowLabel();
    wrefresh(window_ptr);
}
