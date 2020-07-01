#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "obstacle.h"
#include <memory>

class Game {
 public:
  // Feat: add GameMode variable to the Game Constructor
  Game(std::size_t grid_width, std::size_t grid_height, GameMode &mode);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;
  // Feat: add private member _obstacle using smart pointer
  std::unique_ptr<Obstacle> _obstacle;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  // Feat: add private member _mode 
  GameMode _mode;
  // Feat: add level private member to be updated based on score
  int level{0};
  // Feat: add levelScore private member to be used in level calculation (e.g. level increase after every 3 points)
  const int levelScore{3};

  void PlaceFood();
  void Update();
};

#endif
