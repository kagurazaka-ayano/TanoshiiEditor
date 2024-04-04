/**
 * @file Application.cpp
 * @author ayano
 * @date 03/04/24
 * @brief Implementation of Application class
 */

#include "Application.h"
#include <functional>
#include <ncurses.h>


void Application::run()
{
    init();
    while(!app_should_terminate) {
        loop();
    }
    cleanUp();
}

void Application::connect(Signal observer)
{
    observers.push_back(observer);
}

void Application::notify()
{
    for(auto& i : observers) {
        i();
    }
}

void Application::init()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    width = COLS / 3;
    height = LINES / 3;
    init_x = 0;
    init_y = 0;
    w = std::make_shared<TextEditWindow>(DEFAULT_BORDER, "test", width, height, nullptr, init_x, init_y, COLS, LINES);
    refresh();
}

void Application::loop()
{
    auto ch = getch();
    w->inputHandler(ch);
    refresh();
    notify();
}

void Application::cleanUp()
{
    endwin();
}
