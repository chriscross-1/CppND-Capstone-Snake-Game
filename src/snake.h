#ifndef SNAKE_H
#define SNAKE_H

#include <condition_variable>
#include <mutex>
#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, float speed)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2),
        speed(speed),
        initialSpeed(speed) {}

  void Update();

  void GrowBody(int size);
  bool SnakeCell(int x, int y);
  void IncreaseSpeed(float v);
  void SlowDown();
  void IncreaseSlowDownDuration();
  void Restart();

  Direction direction = Direction::kUp;

  bool directionChanged;
  std::mutex directionMutex;
  std::condition_variable directionChangedCondition;

  std::mutex speedMutex;

  float speed{0.1f};
  const float initialSpeed{0.1f};
  int size{1};
  bool alive{true};
  bool paused{false};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  int growing{0};
  int grid_width;
  int grid_height;
  int slowDownDuration;
  const int slowDownCycle{5};
};

#endif