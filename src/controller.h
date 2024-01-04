#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "difficultyLevel.h"

// Forward declaration
class Game;

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake, Game &game, DifficultyLevel level);

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif