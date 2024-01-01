#include "configAccessor.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

/******************* public functions *******************/

ConfigAccessor::ConfigAccessor(const std::string& path)
    : m_path(path)
    , m_framesPerSecond(30)
    , m_screenWidth(640)
    , m_screenHeight(640)
    , m_gridWidth(32)
    , m_gridHeight(32)
    , m_speed(0.1)
{
    ReadInSettings();
}

std::size_t ConfigAccessor::GetFramesPerSecond() const
{
    return m_framesPerSecond;
}

std::size_t ConfigAccessor::GetScreenWidth() const
{
    return m_screenWidth;
}

std::size_t ConfigAccessor::GetScreenHeight() const
{
    return m_screenHeight;
}

std::size_t ConfigAccessor::GetGridWidth() const
{
    return m_gridWidth;
}

std::size_t ConfigAccessor::GetGridHeight() const
{
    return m_gridHeight;
}

float ConfigAccessor::GetSpeed() const
{
    return m_speed;
}

/******************* private functions *******************/

void ConfigAccessor::ReadInSettings()
{
    std::ifstream stream(m_path);
    std::string line;
    std::string key;
    std::string value;

    if (!stream.is_open())
    {
        std::cout << "Error: ConfigAccessor was not able to read data from config. Default values will be used.\n";
        return;
    }

    std::cout << "Using config data from file" << m_path << "\n";
    while (std::getline(stream, line))
    {
        std::replace(line.begin(), line.end(), '=', ' ');
        std::istringstream linestream(line);
        while (linestream >> key >> value)
        {
            SaveValue(key, value);
            std::cout << key << ": " << value << "\n";
        }
    }
}

void ConfigAccessor::SaveValue(const std::string& key, const std::string& value)
{
    if (key.compare("FramesPerSecond") == 0)
        m_framesPerSecond = std::stol(value);
    else if (key.compare("ScreenWidth") == 0)
        m_screenWidth = std::stol(value);
    else if (key.compare("ScreenHeight") == 0)
        m_screenHeight = std::stol(value);
    else if (key.compare("GridWidth") == 0)
        m_gridWidth = std::stol(value);
    else if (key.compare("GridHeight") == 0)
        m_gridHeight = std::stol(value);
    else if (key.compare("Speed") == 0)
        m_speed = std::stof(value);
    else
        std::cout << "Error: " << key << " not relevant for settings, please check config file.\n";
}