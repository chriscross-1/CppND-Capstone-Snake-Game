#include "game.h"
#include "SDL.h"
#include <iostream>

Game::Game(std::size_t grid_width, std::size_t grid_height, float speed)
    : snake(std::make_shared<Snake>(grid_width, grid_height, speed)),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      random_superFood(0, 5),
      random_poorFood(0,10) {
  PlaceFood();
}

void Game::Run(std::shared_ptr<Controller> controller, std::shared_ptr<Renderer> renderer,
               std::size_t target_frame_duration, DifficultyLevel level) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  // Input, Update, Render - the main game loop.
  // Input as own thread to avoid bug where snake can move into itself after quick direction change
  inputThread = std::thread(&Controller::HandleInput, controller, std::ref(running), snake, std::ref(*this), std::move(level));

  while (running) {
    frame_start = SDL_GetTicks();

    // controller.HandleInput(running, snake);
    Update();
    renderer->Render(snake, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer->UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is smaller than the
    // target ms_per_frame), delay the loop to achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

  if (inputThread.joinable())
    inputThread.join();
  if (slowDownFuture.valid())
    slowDownFuture.get();
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing food.
    if (!snake->SnakeCell(x, y)) {
      food.coordinates.x = x;
      food.coordinates.y = y;

      if (random_poorFood(engine) == 10)
        food.type = +FoodType::Poor;
      else if (random_superFood(engine) == 5)
        food.type = +FoodType::Super;
      else
        food.type = +FoodType::Normal;

      return;
    }
  }
}

void Game::Update() {
  if (!snake->alive || snake->paused) return;

  snake->Update();

  int new_x = static_cast<int>(snake->head_x);
  int new_y = static_cast<int>(snake->head_y);

  // Check if there's food over here
  if (food.coordinates.x == new_x && food.coordinates.y == new_y) {
    int bodyGrow = 0;
    float speed = 0.02;

    if (food.type == +FoodType::Normal)
    {
      score++;
      bodyGrow = 1;
      speed = 0.01;
    } else if (food.type == +FoodType::Super)
    {
      score += 5;
      bodyGrow = 5;
      speed = 0.05;
    } else if (food.type == +FoodType::Poor)
    {
      // Slow down snake for 5 seconds
      if (!slowDownFuture.valid())
      {
        slowDownFuture = std::async(std::launch::async, &Snake::SlowDown, snake);
      }

      else if (slowDownFuture.valid())
      {
        // Slow down again for 5 seconds if time has already seconds passed
        if (slowDownFuture.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
        {
          slowDownFuture.get();
          slowDownFuture = std::async(std::launch::async, &Snake::SlowDown, snake);
        } else
        {
          // Add 5 additional seconds otherwise
          snake->IncreaseSlowDownDuration();
        }
      }
    }

    PlaceFood();

    // Grow snake and increase speed.
    snake->GrowBody(bodyGrow);
    snake->IncreaseSpeed(speed);
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake->size; }

void Game::ResetScore()
{
  score = 0;
}
