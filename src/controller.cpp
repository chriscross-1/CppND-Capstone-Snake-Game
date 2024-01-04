#include "controller.h"
#include "snake.h"
#include "SDL.h"
#include <iostream>
#include <thread>

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.alive && !snake.paused && (snake.direction != opposite || snake.size == 1))
  {
    std::unique_lock<std::mutex> ulock(snake.directionMutex);
    snake.directionChanged = false;
    snake.direction = input;

    snake.directionChangedCondition.wait(ulock, [&snake] { return snake.directionChanged; });
  }

  return;
}

void Controller::HandleInput(bool &running, Snake &snake) {
  while (running)
  {
    SDL_Event e;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        snake.alive = false;
        running = false;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_UP:
            ChangeDirection(snake, Snake::Direction::kUp,
                            Snake::Direction::kDown);
            break;

          case SDLK_DOWN:
            ChangeDirection(snake, Snake::Direction::kDown,
                            Snake::Direction::kUp);
            break;

          case SDLK_LEFT:
            ChangeDirection(snake, Snake::Direction::kLeft,
                            Snake::Direction::kRight);
            break;

          case SDLK_RIGHT:
            ChangeDirection(snake, Snake::Direction::kRight,
                            Snake::Direction::kLeft);
            break;
          case SDLK_RETURN:
            if (running && !snake.paused)
              snake.IncreaseSpeed(0.02);
            else;
              // TODO: Continue Game
            break;
          case SDLK_SPACE:
            snake.paused = snake.paused? false : true;
            break;
          case SDLK_PLUS:
            if (!snake.paused)
              snake.GrowBody(1);
            break;
          case SDLK_ESCAPE:
            snake.alive = false;
            break;
        }
      }
    }
  }
}