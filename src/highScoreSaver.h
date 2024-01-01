#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

static const std::string highscoreFilePath = "../data/highscores.txt";

class HighScoreSaver
{
public:
    static bool NewHighscoreReached(size_t score)
    {
        std::fstream highscoreFile;
        size_t highscore = 0;

        highscoreFile.open(highscoreFilePath, std::fstream::in);

        // Get last score from highscore file which is the highest score
        if (highscoreFile.is_open())
        {
            std::string line;
            std::string name;
            while (std::getline(highscoreFile, line))
            {
                std::istringstream linestream(line);
                linestream >> name >> highscore;
            }

            highscoreFile.close();
        }

        return score > highscore;
    }

    static void Save(std::string playerName, size_t highscore)
    {
        std::fstream highscoreFile;
        highscoreFile.open(highscoreFilePath, std::fstream::app);

        if (!highscoreFile.is_open())
        {
            std::cout << "Error: Saving highscore in file " << highscoreFilePath << " was not possible\n";
            return;
        }

        // Save current time as time struct
        auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::tm* localTime = std::localtime(&currentTime);

        // Define format
        const char* format = "%d.%m.%Y, %H:%M";

        char timestamp[20];

        // Get timestamp with correct format
        strftime(timestamp, sizeof(timestamp), format, localTime);

        highscoreFile << std::setw(15) << std::left << playerName + ": " << std::setw(5) << std::left << highscore << " (" << timestamp << ")\n";

        highscoreFile.close();
        std::cout << "Highscore saved in file " << highscoreFilePath << "\n";
    }
};