/**
 * @file Logger.cpp
 * @author ayano
 * @date 09/04/24
 * @brief Logger class implementation
 */

#include "Logger.h"
#include <chrono>
#include "fmt/core.h"
#include <ctime>
#include <filesystem>

Logger::Logger()
{
    std::string name = fmt::format("logs/{}.log", std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())));
    std::filesystem::create_directory("logs");
    log_file.open(name);
}

std::shared_ptr<Logger> Logger::Instance()
{
    static std::shared_ptr<Logger> instance = std::make_shared<Logger>();
    return instance;
}

void Logger::log(const std::string& message)
{
    log_file << fmt::format("[{}] {}\n", std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()), message);
}

std::ofstream& Logger::getLogFile()
{
    return log_file;
}

std::ostream& Logger::operator<<(const std::string& message)
{
    log(message);
    return log_file;
}

