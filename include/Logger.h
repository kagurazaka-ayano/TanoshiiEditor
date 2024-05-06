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
    virtual ~Logger();
    static std::shared_ptr<Logger> Instance();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    void info(const std::string& message);
    void error(const std::string& message);
    void warn(const std::string& message);
    std::ofstream& getLogFile();
    std::ostream &operator<<(const std::string& message);
private:
    Logger();
    void log(const std::string& message);
    std::ofstream log_file;
    std::mutex lock;
};

#endif // TANOSHIIEDITOR_LOGGER_H