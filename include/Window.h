#include <ncurses.h>
#include <iostream>
#include <panel.h>

class BaseWindow {
public:
    BaseWindow(char* borders, std::size_t width, std::size_t height);
    virtual ~BaseWindow();
    int getWidth();
    int getHeight();

    WINDOW* getWindowPtr() const;
    PANEL* getAssociatedPanel() const;
    char* getBorderList() const;
private:
    WINDOW* window_ptr;
    PANEL* associated_panel;
    std::size_t width;
    std::size_t height;
    char border[8];
};
