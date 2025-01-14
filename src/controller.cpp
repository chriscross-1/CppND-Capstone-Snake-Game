#include "controller.h"
#include "game.h"
#include "snake.h"
#include "SDL.h"
#include <iostream>
#include <thread>

void Controller::ChangeDirection(std::shared_ptr<Snake> snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake->alive && !snake->paused && (snake->direction != opposite || snake->size == 1))
  {
    std::unique_lock<std::mutex> ulock(snake->directionMutex);
    snake->directionChanged = false;
    snake->direction = input;

    snake->directionChangedCondition.wait(ulock, [&snake] { return snake->directionChanged; });
  }

  return;
}

void Controller::HandleInput(bool &running, std::shared_ptr<Snake> snake, Game &game, DifficultyLevel level) {
  while (running)
  {
    SDL_Event e;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        snake->alive = false;
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
            if (level == +DifficultyLevel::Expert && snake->alive && !snake->paused)
              snake->IncreaseSpeed(0.01);
            else if (!snake->alive)
            {
              game.ResetScore();
              snake->Restart();
            }
            break;
          case SDLK_SPACE:
            if (level == +DifficultyLevel::Expert)
              snake->paused = snake->paused? false : true;
            break;
          case SDLK_PLUS:
            if (level == +DifficultyLevel::Expert && !snake->paused)
              snake->GrowBody(1);
            break;
          case SDLK_ESCAPE:
            if (snake->alive)
              snake->Die();
            break;
        }
      }
    }
  }
}