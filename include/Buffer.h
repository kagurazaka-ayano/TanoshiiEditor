/**
 * @file Buffer.h
 * @author ayano
 * @date 03/04/24
 * @brief Buffer for text editor
 */

#ifndef TANOSHIIEDITOR_BUFFER_H
#define TANOSHIIEDITOR_BUFFER_H

#include <vector>
#include <string>

class Buffer {
public:
    Buffer();

    void insertLine(const std::string& line, int pos);
    void appendLine(const std::string& line);
    void removeLine(int pos);
private:
    std::vector<std::string> lines;

};

#endif // TANOSHIIEDITOR_BUFFER_H