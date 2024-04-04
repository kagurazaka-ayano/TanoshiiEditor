/**
 * @file Application.h
 * @author ayano
 * @date 03/04/24
 * @brief An application, controlling the main loop
 */

#ifndef TANOSHIIEDITOR_APPLICATION_H
#define TANOSHIIEDITOR_APPLICATION_H
#include "Window.h"
#include <functional>
#include <memory>
#include <vector>
#include <ncurses.h>

class Application {
public:
    using Signal = std::function<void()>;
    void run();
    void connect(Signal observer);
    void notify();
private:
    void init();
    void loop();
    void cleanUp();

    bool app_should_terminate = false;
    std::size_t width;
    std::size_t height;
    std::size_t init_x;
    std::size_t init_y;
    std::shared_ptr<TextEditWindow> w;
    std::vector<Signal> observers;
};
#endif // TANOSHIIEDITOR_APPLICATION_H