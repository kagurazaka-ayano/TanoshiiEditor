#include <ncurses.h>
#include <iostream>
#include "Buffer.h"
#include "Application.h"

int main() {
    Buffer buffer;
    buffer.appendLine("Aliquip do voluptate minim nisi cillum aliquip eiusmod aliqua sit aute sunt. Ex laboris exercitation eu mollit nostrud culpa id aliquip excepteur labore eu et ex. Voluptate ea nisi nisi dolore ipsum occaecat enim incididunt labore occaecat.");
    buffer.wrapLines(30);
    for(int i = 0; i < 30; i++) {
        std::cout << "-";
    }
    std::cout << std::endl << std::string(buffer);
    return 0;
}