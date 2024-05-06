/**
 * @file TextEditWindow.cpp
 * @author ayano
 * @date 08/04/24
 * @brief Implementation of class TextEditWindow
 */

#include "Logger.h"
#include "Window.h"
#include <fmt/core.h>
#include <ncurses.h>
#include <string>

TextEditWindow::TextEditWindow(const Border& borders, const std::string& name, std::size_t width, std::size_t height, PANEL* associated_panel, std::size_t init_x, std::size_t init_y, std::size_t max_width, std::size_t max_height)
    : BaseWindow(borders, name, width, height, associated_panel, init_x, init_y, max_width, max_height)
{
    wrefresh(getWindowPtr());
}

void TextEditWindow::inputHandler(chtype ch)
{
    auto logger = Logger::Instance();
    switch (ch) {
    case KEY_LEFT:
        if (cursor_col != 0) {
            cursor_col--;
        } else if (cursor_line != 0) {
            cursor_line--;
            cursor_col = buffer[cursor_line].empty() ? 0 : buffer[cursor_line].size();
        }
        break;
    case KEY_RIGHT:
        if (cursor_col + 1 < buffer[cursor_line].size()) {
            cursor_col++;
        }
        else {
            cursor_line++;
            cursor_col = 0;
        }
        break;
    case KEY_UP:
        if (cursor_col - getWidth() < cursor_line) {
            cursor_col -= getWidth();
        }
        else {
            if (cursor_line == 0) {
                cursor_col = 0;
            }
            cursor_line--;
            cursor_col = buffer[cursor_line].size() - 1;
        }
        break;
    case KEY_DOWN:
        if (cursor_line + getWidth() < buffer.getBufferSize()) {
            cursor_col += getWidth();
        }
        else {
            cursor_line++;
            cursor_col = buffer[cursor_line].size() - 1;
        }
        break;
#ifdef __APPLE__
    // enter, since ncurses's definition won't work on mac
    case 10:
#else
    case KEY_ENTER:
#endif
        buffer.appendLine("");
        buffer.wrapLines(getWidth() - 2);
        cursor_line++;
        cursor_col = 0;
        break;
#ifdef __APPLE__
    // backspace, since ncurses's definition won't work on mac
    case 127:
#else
    case KEY_BACKSPACE:
#endif
        if (buffer[cursor_line].size() == 0) {
            if (cursor_col == 0) {
                buffer.wrapLines(getWidth() - 2);
                break;
            }
            cursor_col--;
            buffer.removeLine(cursor_line);
        } else {
            buffer[cursor_line].erase(cursor_col - 1, 1);
        }
        buffer.wrapLines(getWidth() - 2);
        break;
    default:
        if (cursor_col == getWidth() - 1) {
            cursor_line++;
            cursor_col = 1;
        }
        buffer.addChAt(cursor_line, cursor_col, ch);
        buffer.wrapLines(getWidth() - 2);
        cursor_col++;
        break;
    }
    logger->info(fmt::format("cursor_line: {}, cursor_col: {}, wrapped_line: {}, wrapped_col: {}, character inputed: {}", cursor_line, cursor_col, wrappedLine(), wrappedCol(), ch));
    updateDisplay();
}

void TextEditWindow::updateDisplay()
{

    eraseTextContent();
    makeBorder();
    mvaddstr(getY() + 1, getX() + 1, std::string(buffer).c_str());
}

void TextEditWindow::scrollUp()
{
    buffer.wrapLines(getWidth() - 2);
    if (top_line != 0)
        top_line--;
}

void TextEditWindow::scrollDown()
{
    buffer.wrapLines(getWidth() - 2);
    if (top_line != buffer.getWrappedLineCount())
        top_line++;
}

void TextEditWindow::eraseTextContent()
{
    for (int i = 1; i < getWidth() - 1; ++i) {
        for (int j = 1; j < getHeight(); ++j) {
            mvwaddch(window_ptr, j, i, ' ');
        }
    }
}

std::size_t TextEditWindow::wrappedLine() const
{
    std::size_t ans = 0;
    for (int i = 0; i <= cursor_line; i++) {
        if (i == cursor_line) {
            ans += cursor_col / (getWidth() - 2) + 1;
            return ans;
        }
        ans += buffer[i].size() / (getWidth() - 2) + 1;
    }
    return ans;
}

std::size_t TextEditWindow::wrappedCol() const
{
    return cursor_col % (getWidth() - 2) + 1;
}
