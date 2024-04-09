/**
 * @file Buffer.cpp
 * @author ayano
 * @date 04/04/24
 * @brief Implementation of Buffer class
 */

#include "Buffer.h"
#include <sstream>
#include <iostream>

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
    for (auto i : wrapped_lines) {
        ss << std::get<1>(i) << std::endl;
    }
    return ss.str();
}

void Buffer::wrapLines(std::size_t window_width) {
    wrapped_lines.clear();
    int idx = 0;
    for (const auto& line : lines) {
        std::size_t start = 0;
        std::size_t count = 0;
        while (start < line.length()) {
            std::size_t end = line.find(' ', start + 1);
            if (end == std::string::npos) {
                end = line.length();
            }
            std::size_t word_len = end - start;
            if (word_len > window_width) {
                // If the word is too long to fit on a line, split it
                end = start + window_width;
                word_len = window_width;
            }
            if (count + word_len > window_width) {
                // If adding the word to the current line would make it too long, start a new line
                wrapped_lines.push_back(std::make_tuple(idx, line.substr(start, word_len)));
                count = word_len;
            } else {
                // Otherwise, add the word to the current line
                if (!wrapped_lines.empty()) {
                    std::get<1>((wrapped_lines).back()) += line.substr(start, word_len);
                } else {
                    wrapped_lines.push_back(std::make_tuple(idx, line.substr(start, word_len)));
                }
                count += word_len;
            }
            start = end;
        }
        idx++;
    }
}
