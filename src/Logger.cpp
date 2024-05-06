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
#include <iomanip>
#include <memory>
#include <mutex>

Logger::Logger()
{
    std::string name = fmt::format("logs/{}.log", std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())));
    std::filesystem::create_directory("logs");
    log_file.open(name, std::ios::out | std::ios::app);
}

std::shared_ptr<Logger> Logger::Instance()
{
    static std::shared_ptr<Logger> instance = std::shared_ptr<Logger>(new Logger());
    return instance;
}

Logger::~Logger()
{
    log_file.close();
}

void Logger::log(const std::string& message)
{
    std::lock_guard<std::mutex> guard(lock);
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto tm = std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(tm, "%F %T");
    log_file << fmt::format("[{}] {}\n", ss.str(), message);
    log_file.flush();
}

void Logger::info(const std::string& message)
{
    log(fmt::format("[INFO] {}", message));
}

void Logger::error(const std::string& message)
{
    log(fmt::format("[ERROR] {}", message));
}

void Logger::warn(const std::string& message)
{
    log(fmt::format("[WARN] {}", message));
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

