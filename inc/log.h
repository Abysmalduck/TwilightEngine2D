#pragma once

#include <string>
#include <map>

#include <iostream>

#define logs(text) LogManager::getInstance().log(text, INFO)
#define logsi(text, imp) LogManager::getInstance().log(text, imp)

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

    void log(std::string text, Importance imp)
    {
        std::cout << "[" << imp_to_str.at(imp) << "] "  << text << std::endl;
    }
};