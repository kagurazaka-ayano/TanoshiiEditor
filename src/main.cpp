#include <iostream>
#include <memory>
#include <string>
#include <ncurses.h>
#include "Border.h"
#include "Window.h"

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    std::size_t width = 16, height = 9;
    std::size_t init_x = LINES / 2;
    std::size_t init_y = COLS / 2;
    
    refresh();
    std::shared_ptr<BaseWindow> w = std::make_shared<BaseWindow>(DEFAULT_BORDER, "test", width, height, nullptr, init_x, init_y, COLS, LINES);
    char ch = ' ';
    do{
        ch = getch();
        switch(ch) {
            case 'w':
                w->moveTo(w->getX() - 1, w->getY());
                break;
            case 's':
                w->moveTo(w->getX() + 1, w->getY());
                break;
            case 'a':
                w->moveTo(w->getX(), w->getY() - 1);
                break;
            case 'd':
                w->moveTo(w->getX(), w->getY() + 1);
                break;
        }
        refresh();
    } while(ch != 'q');
    endwin();
    return 0;
}