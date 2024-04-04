/**
 * @file StringManipulator.h
 * @author ayano
 * @date 04/04/24
 * @brief A utility class to manipulate string
 */

#ifndef TANOSHIIEDITOR_STRINGMANIPULATOR_H
#define TANOSHIIEDITOR_STRINGMANIPULATOR_H
#include <string>
class StringManipulator {
public:
    static std::string lineWrap(const std::string& str, int max_width);
private:
    StringManipulator() = default;
};
#endif // TANOSHIIEDITOR_STRINGMANIPULATOR_H