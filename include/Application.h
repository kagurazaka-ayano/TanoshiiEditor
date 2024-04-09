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
#include <ncurses.h>
#include <vector>

class Application {
public:
    using Signal = std::function<void()>;
    /**
     * @brief entry point for the application
     *
     */
    void run();
    /**
     * @brief register a callback signal
     *
     * @param observer the signal function pending register
     */
    void connect(Signal observer);
    /**
     * @brief execute all the signal functions, called in the end of the main loop
     *
     */
    void notify();

private:
    /**
     * @brief Initialization phase of the application, run only once prior to all things
     *
     */
    void init();
    /**
     * @brief Main loop of the application, will quit when app_should_terminate is true
     * 
     */
    void loop();
    /**
     * @brief Cleaning up phase of the application, run only once after everything finished
     * 
     */
    void cleanUp();

    /* define member variables here */
    bool app_should_terminate = false;
    std::size_t width;
    std::size_t height;
    std::size_t init_x;
    std::size_t init_y;
    std::shared_ptr<TextEditWindow> w;
    std::vector<Signal> observers;
};
#endif // TANOSHIIEDITOR_APPLICATION_H