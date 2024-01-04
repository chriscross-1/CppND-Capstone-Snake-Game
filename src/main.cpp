#include <iostream>
#include "configAccessor.h"
#include "controller.h"
#include "difficultyLevel.h"
#include "game.h"
#include "renderer.h"
#include "highScoreHandler.h"

int main(int argc, char** argv) {
  // Get difficulty level
  DifficultyLevel level = DifficultyLevel::Beginner;
  if (argc > 1)
  {
    const std::string arg = argv[1];
    if (arg == "-a" || arg == "--advanced")
      level = DifficultyLevel::Advanced;
    else if (arg == "-e" || arg == "--expert")
      level = DifficultyLevel::Expert;
  }

  // Create config accessor
  const std::string configPath = "../data/config" + std::string(level._to_string()) + ".cfg";
  ConfigAccessor config(configPath);

  // Get parameters from config
  const std::size_t kFramesPerSecond = config.GetFramesPerSecond();
  const std::size_t kMsPerFrame = 1000 / kFramesPerSecond;
  const std::size_t kScreenWidth = config.GetScreenWidth();
  const std::size_t kScreenHeight = config.GetScreenHeight();
  const std::size_t kGridWidth = config.GetGridWidth();
  const std::size_t kGridHeight = config.GetGridHeight();
  const float kSpeed = config.GetSpeed();

  std::string name;
  std::cout << "\nPlease enter your name: ";
  std::cin >> name;

  auto renderer = std::make_shared<Renderer>(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight, name);
  auto controller = std::make_shared<Controller>();
  Game game(kGridWidth, kGridHeight, kSpeed);
  game.Run(controller, renderer, kMsPerFrame, std::move(level));
  std::cout << "Game has terminated successfully!\n";

  auto score = game.GetScore();
  std::cout << "Name:  " << name << "\n";
  std::cout << "Score: " << score << "\n";
  std::cout << "Size:  " << game.GetSize() << "\n";
  
  // Save score when new highscore was reached
  if (HighScoreHandler::NewHighscoreReached(score))
  {
    std::cout << "New highscore reached!\n";
    HighScoreHandler::SaveHighscore(name, score);
  } else
  {
    std::cout << "No new highscore reached (current highscore: " << HighScoreHandler::GetCurrentHighscore() << ")\n";
  }
  return 0;
}