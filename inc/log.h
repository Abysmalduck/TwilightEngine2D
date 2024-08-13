#pragma once

#include <string>
#include <map>

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cstdio>

#define logs(text) LogManager::getInstance().log(text, INFO)
#define logsi(text, imp) LogManager::getInstance().log(text, imp)

const std::string log_file_path = "tweng.log";

enum Importance
{
    INFO,
    WARN,
    ERR
};

const std::map<Importance, std::string> imp_to_str = 
{
    {INFO, "INFO"},
    {WARN, "WARNING"},
    {ERR, "ERROR"}
};


class LogManager
{
private:
    LogManager() {};
    LogManager(LogManager&) {};
    void operator=(LogManager&) {}
public:
    static LogManager& getInstance()
    {
        static LogManager instance;
        return instance;
    }

    void init()
    {
        if (std::filesystem::exists(log_file_path))
        {
            bool result = std::filesystem::remove(log_file_path);
            if(result != true)
            {
                logsi("Impossible to delete log file.", WARN);
            }
        }
    }

    void log(std::string text, Importance imp)
    {
        std::stringstream log_stream;

        log_stream << "[" << imp_to_str.at(imp) << "] "  << text << std::endl;

        std::cout << log_stream.str();
        std::ofstream file_stream;
        file_stream.open(log_file_path, std::ios_base::app);
        file_stream << log_stream.str();
        file_stream.close();
    }
};