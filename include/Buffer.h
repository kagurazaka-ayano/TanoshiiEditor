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
    std::size_t getBufferSize() const;
    std::string& operator[](std::size_t idx);
    operator std::string() const;
private:
    std::vector<std::string> lines;

};



#endif // TANOSHIIEDITOR_BUFFER_H