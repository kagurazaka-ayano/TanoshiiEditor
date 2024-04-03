/**
 * @file Window.h
 * @author ayano
 * @date 03/04/24
 * @brief
 */

#ifndef TANOSHIIEDITOR_WINDOW_H
#define TANOSHIIEDITOR_WINDOW_H
#include <ncurses.h>
#include <panel.h>
#include <string>
#include "Border.h"

class BaseWindow {
public:
    BaseWindow(const Border& borders, const std::string& name, std::size_t width, std::size_t height, PANEL* associated_panel, std::size_t init_x, std::size_t init_y, std::size_t max_width, std::size_t max_height);
    virtual ~BaseWindow();

    void updateBorder(const Border& borders);
    void updateDimension(std::size_t width, std::size_t height);
    void moveTo(std::size_t x, std::size_t y);

    std::size_t getWidth() const;
    std::size_t getHeight() const;
    std::size_t getMaxWidth() const;
    std::size_t getMaxHeight() const;
    std::size_t getX() const;
    std::size_t getY() const;
    PANEL* getAssociatedPanel() const;
    Border getBorder() const;
    void refreshWindow() const;

private:
    PANEL* associated_panel;
    WINDOW* window_ptr;
    std::size_t window_width, window_height, x, y;
    std::size_t max_width, max_height;
    Border window_border;
    std::string name;

    virtual bool validifyWindow();
    virtual void killWindow();
    virtual void eraseWindow(bool remove_content = true);
    virtual void redrawWindow();

    virtual void makeBorder();
    virtual void makeWindowLabel();
};
#endif // TANOSHIIEDITOR_WINDOW_H
