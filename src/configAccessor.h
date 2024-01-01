#pragma once

#include <iostream>

class ConfigAccessor
{
public:
    ConfigAccessor(const std::string& path);
    std::size_t GetFramesPerSecond() const;
    std::size_t GetScreenWidth() const;
    std::size_t GetScreenHeight() const;
    std::size_t GetGridWidth() const;
    std::size_t GetGridHeight() const;
    float GetSpeed() const;

private:
    void ReadInSettings();
    void SaveValue(const std::string& key, const std::string& value);

    const std::string m_path;
    std::size_t m_framesPerSecond;
    std::size_t m_screenWidth;
    std::size_t m_screenHeight;
    std::size_t m_gridWidth;
    std::size_t m_gridHeight;
    float m_speed;
};