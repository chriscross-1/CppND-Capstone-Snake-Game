#pragma once

#include "SDL.h"
#include "enum.h"

BETTER_ENUM(FoodType, u_int8_t, Normal, Super, Poor)

struct Food {
  SDL_Point coordinates = SDL_Point();
  FoodType type = +FoodType::Normal;
};