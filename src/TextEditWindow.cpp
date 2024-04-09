/**
 * @file TextEditWindow.cpp
 * @author ayano
 * @date 08/04/24
 * @brief Implementation of class TextEditWindow
 */

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
        } else if (cursor_line + 1 < buffer.getBufferSize()) {
            cursor_line++;
            cursor_col = 0;
        }
        break;
    case KEY_UP:
        if (cursor_line != 0) {
            cursor_line--;
        }
        break;
    case KEY_DOWN:
        if (unwrappedLine() + 1 < buffer.getBufferSize()) {
            cursor_line++;
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
        if(buffer[unwrappedLine()].size() == 0) {
            if (cursor_col == 0) {
                buffer.wrapLines(getWidth() - 2);
                break;
            }
            cursor_col--;
            buffer.removeLine(unwrappedLine());
        }
        else {
            buffer[unwrappedLine()].erase(unwrappedCol());
        }
        buffer.wrapLines(getWidth() - 2);
        break;
    default:
        if (cursor_col == getWidth() - 1) {
            cursor_line++;
            cursor_col = 1;
        }
        buffer.addChAt(unwrappedLine(), unwrappedCol(), ch);
        buffer.wrapLines(getWidth() - 2);
        cursor_col++;
        break;
    }
    mvaddstr(getHeight() + 1, getWidth() + 1, fmt::format("unwrappedLine: {}, unwrappedCol: {}, wrappedLine: {}, wrappedCol: {}, pressedKey: {}", unwrappedLine(), unwrappedCol(), cursor_line, cursor_col, ch).c_str()); 
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

std::size_t TextEditWindow::unwrappedLine() const
{
    return std::get<0>(buffer.getWrappedLineTuple(cursor_line));
}

std::size_t TextEditWindow::unwrappedCol() const {
    std::size_t ans = cursor_col;
    auto current_unwrapped_line = unwrappedLine();
    // avoid unsigned integer overflow
    if (cursor_line == 0) return ans;
    for(int i = cursor_line - 1; i >= 0; --i) {
        
        auto length = std::get<0>(buffer.getWrappedLineTuple(i));
        if (length == current_unwrapped_line) {
            ans += length;
        }
        else {
            return ans;
        }
        if (i == 0) return ans;
    }
    return ans;
}
