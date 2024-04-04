/**
 * @file Buffer.cpp
 * @author ayano
 * @date 04/04/24
 * @brief Implementation of Buffer class
 */

#include "Buffer.h"
#include <sstream>

Buffer::Buffer()
{
    lines.push_back("");
}

void Buffer::insertLine(const std::string& line, int pos)
{
    lines.insert(lines.begin() + pos, line);
}

void Buffer::appendLine(const std::string& line)
{
    lines.push_back(line);
}

void Buffer::removeLine(int pos)
{
    lines.erase(lines.begin() + pos);
}

std::size_t Buffer::getBufferSize() const
{
    return lines.size();
}

std::string& Buffer::operator[](std::size_t idx)
{
    return lines[idx];
}

Buffer::operator std::string() const {
    std::stringstream ss;
    for (auto i : lines) {
        ss << i;
    }
    return ss.str();
}

