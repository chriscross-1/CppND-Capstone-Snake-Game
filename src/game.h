#ifndef GAME_H
#define GAME_H

#include <random>
#include <thread>
#include <future>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "food.h"
#include "difficultyLevel.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, float speed);
  void Run(std::shared_ptr<Controller> controller, std::shared_ptr<Renderer> renderer,
           std::size_t target_frame_duration, DifficultyLevel level);
  int GetScore() const;
  int GetSize() const;
  void ResetScore();

 private:
  std::shared_ptr<Snake> snake;
  Food food;
  std::thread inputThread;
  std::future<void> slowDownFuture;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::uniform_int_distribution<int> random_superFood;
  std::uniform_int_distribution<int> random_poorFood;

  int score{0};

  void PlaceFood();
  void Update();
};

#endif