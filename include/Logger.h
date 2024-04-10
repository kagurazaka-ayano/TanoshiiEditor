/**
 * @file Logger.h
 * @author ayano
 * @date 09/04/24
 * @brief Logger clas
 */

#ifndef TANOSHIIEDITOR_LOGGER_H
#define TANOSHIIEDITOR_LOGGER_H

#include <string>
#include <fstream>

class Logger {
public:
    static std::shared_ptr<Logger> Instance();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    void log(const std::string& message);
    std::ofstream& getLogFile();

    std::ostream &operator<<(const std::string& message);
private:
    Logger();
    std::ofstream log_file;
};

#endif // TANOSHIIEDITOR_LOGGER_H