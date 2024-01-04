#include "snake.h"
#include <cmath>
#include <iostream>
#include <thread>

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
    std::unique_lock<std::mutex> ulock(directionMutex);
    directionChanged = true;
    directionChangedCondition.notify_one();
  }
}

void Snake::UpdateHead() {
  std::lock_guard<std::mutex> guard(speedMutex);
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    size++;
    growing--;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody(int size) { growing = size; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

void Snake::IncreaseSpeed(float v)
{
  std::lock_guard<std::mutex> guard(speedMutex);
  if (v > 0)
    speed += v;
}

void Snake::SlowDown()
{
  std::unique_lock<std::mutex> ulock(speedMutex);
  auto oldSpeed = speed;
  speed = 0.1;

  // Slow down for 5 seconds
  slowDownDuration = slowDownCycle;
  ulock.unlock();

  auto slowDownStart = std::chrono::system_clock::now();
  auto expiredTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - slowDownStart).count();
  while (alive && expiredTime < slowDownDuration)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    expiredTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - slowDownStart).count();
  }

  ulock.lock();
  speed = oldSpeed + (speed - 0.1);
  ulock.unlock();
}

void Snake::IncreaseSlowDownDuration()
{
  // Add 5 seconds to slow down duration
  std::lock_guard<std::mutex> guard(speedMutex);
  slowDownDuration += slowDownCycle;
}