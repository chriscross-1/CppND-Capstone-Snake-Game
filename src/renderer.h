#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include "SDL.h"
#include "snake.h"
#include "food.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height,
           const std::string player_name);
  ~Renderer();

  void Render(Snake const &snake, Food const &food);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  const std::string player_name;
};

#endif