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

void BaseWindow::refreshWindow() const
{
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


TextEditWindow::TextEditWindow(const Border& borders, const std::string& name, std::size_t width, std::size_t height, PANEL* associated_panel, std::size_t init_x, std::size_t init_y, std::size_t max_width, std::size_t max_height):
    BaseWindow(borders, name, width, height, associated_panel, init_x, init_y, max_width, max_height)
{
    wrefresh(getWindowPtr());
}

void TextEditWindow::inputHandler(chtype ch)
{
    switch (ch) {
    case KEY_LEFT:
        if (cursor_col != 0) {
            cursor_col--;
        } else if (cursor_line != 0) {
            cursor_line--;
            cursor_col = buffer[cursor_line].size() == 0 ? 0 : buffer[cursor_line].size();
        }
        addstr(fmt::format("cursor pos: {}, {} line size: {}\n", cursor_col, cursor_line, buffer[cursor_line].size()).data());
        break;
    case KEY_RIGHT:
        if (cursor_col + 1 < buffer[cursor_line].size()) {
            cursor_col++;
        } else if (cursor_line + 1 < buffer.getBufferSize()) {
            cursor_line++;
            cursor_col = 0;
        }
        addstr(fmt::format("cursor pos: {}, {} line size: {}\n", cursor_col, cursor_line, buffer[cursor_line].size()).data());
        break;
    case KEY_UP:
        if (cursor_line != 0) {
            cursor_line--;
        }
        addstr(fmt::format("cursor pos: {}, {} line size: {}\n", cursor_col, cursor_line, buffer[cursor_line].size()).data());
        break;
    case KEY_DOWN:
        if (cursor_line + 1 < buffer.getBufferSize()) {
            cursor_line++;
        }
        addstr(fmt::format("cursor pos: {}, {} line size: {}\n", cursor_col, cursor_line, buffer[cursor_line].size()).data());
        break;
    case KEY_ENTER:
        buffer[cursor_line].append("\n");
        buffer.appendLine("");
        addstr("enter");
        break;
    case KEY_BACKSPACE:
        buffer[cursor_line].erase(cursor_col);
        break;
    default:
        buffer[cursor_line].insert(buffer[cursor_line].begin() + cursor_col, 1, ch);
        cursor_col++;
        break;
    }
    updateDisplay();
}


void TextEditWindow::updateDisplay()
{
    eraseWindow();
    makeWindowLabel();
    makeBorder();
    mvaddstr(getY() + 1, getX() + 1, std::string(buffer).c_str());
}

void TextEditWindow::scrollUp() {
    if (top_line != 0) top_line--;
}

void TextEditWindow::scrollDown() {
    if (top_line != buffer.getBufferSize()) top_line++;
}


