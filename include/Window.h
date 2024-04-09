/**
 * @file Window.h
 * @author ayano
 * @date 03/04/24
 * @brief
 */

#ifndef TANOSHIIEDITOR_WINDOW_H
#define TANOSHIIEDITOR_WINDOW_H
#include "Border.hpp"
#include "Buffer.h"
#include <ncurses.h>
#include <panel.h>
#include <string>

/**
 * @brief Base class of all windows, defined some utility functions, all window should explicitly or implicitly inherit this.
 *
 */
class BaseWindow {
public:
    BaseWindow(const Border& borders, const std::string& name, std::size_t width, std::size_t height, PANEL* associated_panel, std::size_t init_x, std::size_t init_y, std::size_t max_width, std::size_t max_height);
    virtual ~BaseWindow();

    void updateBorder(const Border& borders);
    void updateDimension(std::size_t width, std::size_t height);
    void moveTo(std::size_t x, std::size_t y);

    /**
     * @brief Get the width
     *
     * @return std::size_t width
     */
    std::size_t getWidth() const;
    /**
     * @brief Get the Height
     *
     * @return std::size_t height
     */
    std::size_t getHeight() const;
    /**
     * @brief Get the max width of the window
     *
     * @return std::size_t max width
     */
    std::size_t getMaxWidth() const;
    /**
     * @brief Get the max height of the window
     *
     * @return std::size_t max height
     */
    std::size_t getMaxHeight() const;
    /**
     * @brief get x coordinate of the upperleft corner
     *
     * @return std::size_t x coordinate of the upperleft corner
     */
    std::size_t getX() const;
    /**
     * @brief get y coordinate of the upperleft corner
     *
     * @return std::size_t y coordinate of the upperleft corner
     */
    std::size_t getY() const;
    /**
     * @brief Get the Border object of the window
     *
     * @return Border border object for the window
     */
    Border getBorder() const;
    /**
     * @brief Get the Name of the window
     *
     * @return std::string name
     */
    std::string getName() const;
    /**
     * @brief refresh the window
     *
     */
    virtual void refreshWindow();

    /**
     * @brief handles all the inputs
     *
     * @param ch the return value of getch() in ncurses
     */
    virtual void inputHandler(chtype ch) = 0;

protected:
    PANEL* associated_panel;
    WINDOW* window_ptr;
    /**
     * @brief Get the associated Panel object
     *
     * @return PANEL* associated panel ptr
     */
    PANEL* getAssociatedPanel() const;
    /**
     * @brief Get the window ptr
     *
     * @return WINDOW* raw window ptr
     */
    WINDOW* getWindowPtr() const;
    /**
     * @brief validate window, now is only checking dimension
     *
     * @return true if the window is valid
     * @return false otherwise
     */
    virtual bool validifyWindow();
    /**
     * @brief destory the window
     *
     */
    virtual void killWindow();
    /**
     * @brief erase the window, including content and header
     *
     */
    virtual void eraseWindow();
    /**
     * @brief redraw the whole window
     *
     */
    virtual void redrawWindow();
    /**
     * @brief display the give border object
     *
     */
    virtual void makeBorder();
    /**
     * @brief update label for the window
     *
     */
    virtual void makeWindowLabel();

private:
    std::size_t window_width, window_height, x, y;
    std::size_t max_width, max_height;
    Border window_border;
    std::string name;
};

class TextEditWindow : public BaseWindow {
public:
    TextEditWindow(const Border& borders, const std::string& name, std::size_t width, std::size_t height, PANEL* associated_panel, std::size_t init_x, std::size_t init_y, std::size_t max_width, std::size_t max_height);
    void inputHandler(chtype ch) override;

protected:
    /**
     * @brief Convert the wrapped column to unwrapped column
     *
     * @return std::size_t unwrapped column
     */
    std::size_t unwrappedCol() const;

    /**
     * @brief Convert the wrapped row to unwrapped row
     *
     * @return std::size_t nwrapped row
     */
    std::size_t unwrappedLine() const;

private:
    /**
     * @brief update the display content of the text editing window
     *
     */
    void updateDisplay();

    /**
     * @brief erase only the text portion of the window
     *
     */
    void eraseTextContent();
    /**
     * @param cursor_col which column the cursor is on, for wrapped line
     * @param cursor_line which line the cursor is on, for wrapped line
     * @param top_line which line is the line at the top
     */
    std::size_t cursor_col, cursor_line, top_line;
    Buffer buffer;

    void scrollDown();

    void scrollUp();
};

#endif // TANOSHIIEDITOR_WINDOW_H
