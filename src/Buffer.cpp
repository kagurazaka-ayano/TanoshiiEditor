/**
 * @file Buffer.cpp
 * @author ayano
 * @date 04/04/24
 * @brief Implementation of Buffer class
 */

#include "Buffer.h"
#include <sstream>
#include <iostream>
#include <string>
#include <ncurses.h>
#include <tuple>
#include <vector>

Buffer::Buffer()
{
    lines.push_back("");
    wrapped_lines.push_back(std::make_tuple(0, ""));
}

void Buffer::insertLine(const std::string& line, std::size_t pos)
{
    lines.insert(lines.begin() + pos, line);
    buffer_modified = true;
}

void Buffer::addChAt(std::size_t line, std::size_t col, chtype ch) {
    lines[line].insert(lines[line].begin() + col, ch);
    buffer_modified = true;
}

void Buffer::appendCh(std::size_t line, chtype ch) {
    lines[line].push_back(ch);
    buffer_modified = true;
}

void Buffer::appendLine(const std::string& line)
{
    lines.push_back(line);
    buffer_modified = true;
}

void Buffer::removeLine(int pos)
{
    lines.erase(lines.begin() + pos);
    buffer_modified = true;
}

std::size_t Buffer::getBufferSize() const
{
    return lines.size();
}

std::string& Buffer::operator[](std::size_t idx)
{
    return lines[idx];
}

std::string Buffer::operator[](std::size_t idx) const
{
    return lines.at(idx);
}

Buffer::operator std::string() const {
    std::stringstream ss;
    for (auto i : wrapped_lines) {
        ss << std::get<1>(i) << std::endl;
    }
    return ss.str();
}

std::size_t Buffer::getWrappedLineCount() const {
    return wrapped_lines.size();
}

void Buffer::wrapLines(std::size_t window_width) {
    if(!buffer_modified) return;
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
    buffer_modified = false;
}

std::tuple<std::size_t, std::string>& Buffer::getWrappedLineTuple(std::size_t idx)
{
    return wrapped_lines[idx];
}

std::tuple<std::size_t, std::string> Buffer::getWrappedLineTuple(std::size_t idx) const
{
    return wrapped_lines.at(idx);
}

std::vector<std::string> Buffer::split(const std::string &str, const std::string &delim) {
    std::vector<std::string> tokens;
    std::size_t start = 0;
    std::size_t end = str.find(delim);
    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delim.length();
        end = str.find(delim, start);
    }
    tokens.push_back(str.substr(start, end));
    return tokens;
}
