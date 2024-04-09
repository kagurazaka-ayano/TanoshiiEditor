/**
 * @file Buffer.h
 * @author ayano
 * @date 03/04/24
 * @brief Buffer for text editor
 */

#ifndef TANOSHIIEDITOR_BUFFER_H
#define TANOSHIIEDITOR_BUFFER_H

#include <string>
#include <vector>
#include <ncurses.h>

class Buffer {
public:
    Buffer();
    /**
     * @brief insert a line to the buffer
     *
     * @param line line content
     * @param pos position you want to insert
     */
    void insertLine(const std::string& line, std::size_t pos);
    /**
     * @brief add a character at certain position
     *
     * @param line which line
     * @param col which column
     */
    void addChAt(std::size_t line, std::size_t col, chtype ch);
    
    /**
     * @brief append character to the end of the line
     * 
     * @param line line
     * @param ch character
     */
    void appendCh(std::size_t line, chtype ch);
    /**
     * @brief append a line at the back of the buffer
     *
     * @param line line content
     */
    void appendLine(const std::string& line);
    /**
     * @brief remove a line
     *
     * @param pos line position in the buffer
     */
    void removeLine(int pos);
    /**
     * @brief Get the Buffer Size
     *
     * @return std::size_t buffer size
     */
    std::size_t getBufferSize() const;
    /**
     * @brief Get the line count after wrapped
     *
     * @return std::size_t wrapped Line count
     * @warning This function will NOT update the wrapped line
     */
    std::size_t getWrappedLineCount() const;
    /**
     * @brief get the wrapped line at position idx
     *
     * @param idx index
     * @return std::tuple<std::size_t, std::string> reference to wrapped line at position idx
     * @warning This function will NOT update the wrapped line
     */
    std::tuple<std::size_t, std::string>& getWrappedLineTuple(std::size_t idx);
    /**
     * @brief get the wrapped line at position idx
     *
     * @param idx index
     * @return std::tuple<std::size_t, std::string> reference to wrapped line at position idx
     * @warning This function will NOT update the wrapped line
     */
    std::tuple<std::size_t, std::string> getWrappedLineTuple(std::size_t idx) const;
    /**
     * @brief get the unwrapped line at position idx
     *
     * @param idx index
     * @return std::string& unwrapped line at position idx
     */
    std::string& operator[](std::size_t idx);
    /**
     * @brief get the unwrapped line at position idx
     *
     * @param idx index
     * @return std::string& unwrapped line at position idx
     */
    std::string operator[](std::size_t idx) const;
    /**
     * @brief toString
     *
     * @return std::string the wrapped string
     */
    operator std::string() const;
    /**
     * @brief generate wrapped line buffer
     *
     * @param window_width max width to be wrapped
     */
    void wrapLines(std::size_t window_width);

private:
    std::vector<std::string> lines;
    std::vector<std::tuple<std::size_t, std::string>> wrapped_lines;
    bool buffer_modified = false;
};

#endif // TANOSHIIEDITOR_BUFFER_H