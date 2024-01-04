# CPPND: Capstone Snake Game Example

This is the Capstone project of the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

## New features
* 3 different difficulty levels (Beginner, Advanced, Expert), where the configuration data is read out of a configuration file (e.g. data/configBeginner.cfg)
* If no argument is given, the default level is Beginner
* Use ./SnakeGame -a or ./SnakeGame --advanced for level Advanced and ./SnakeGame -e or ./SnakeGame --expert for level Expert
* The user will be asked for the name before starting the game
* New highscores will be saved to the file data/highscores.txt (only if the score is higher than the last highscore) with name, score and date
* It is possible to end the game (Escape) and restart the game (Enter) when the game is over. After a restart the score will not be saved
* Beside the normal food, there are two addiditonal food types (Super and Poor). With the green super food, the snake will grow 5 fields and increase the speed by factor 5 compared to the normal food. With the red poor food the snake will slow down for 5 seconds.
* The bug is fixed where the snake can move into itself after a quick direction change
* In Expert mode it is possible to manually increase the speed (by pressing the Enter key), grow the snake's body (by pressing the + key) and to pause the snake (by pressing the Space key)

## Rubric points
* Loops, Functions, I/O: game.cpp, configAccessor.cpp, HighscoreHandler.cpp
* Object Oriented Programming: configAccessor.cpp, food.h
* Memory Management: main.cpp, game.cpp, controller.cpp, snake.cpp
* Concurrency: game.h, game.cpp, snake.h, snake.cpp

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
