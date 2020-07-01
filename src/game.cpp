#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, GameMode &mode)
    : _mode(mode),                                    // Feat: Initialize the _mode private member
      snake(grid_width, grid_height),
      _obstacle(std::unique_ptr<Obstacle> ( new Obstacle(grid_width,grid_height))),  // Feat: Initialize the smart pointer _obstacle window width and height
      engine(dev()),
      random_w(0, static_cast<int>(grid_width-1)),    // Fix: initially grid_width used not (grid_width-1) lead to out of boundary food point 
      random_h(0, static_cast<int>(grid_height-1)){   // Fix: initially grid_height used not (grid_height-1) lead to out of boundary food point
  if(_mode == GameMode::Difficult)
    snake.speed = 0.2;  // Feat: Set initial speed to 0.2 in Difficult mode vs 0.1 in Normal mode
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  int fps = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, *_obstacle);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;
    
    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      // Feat: update fps variable only here to get the frame count per second
      fps = frame_count;
      frame_count = 0;
      title_timestamp = frame_end;
    }
    // Feat: set the level based on the score and the levelScore constant
    if((score % levelScore) == 0) { level = score / levelScore; }
    // Feat: update title with the score, fps, level and game mode values
    renderer.UpdateWindowTitle(score, fps, level, _mode);
    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    // Feat: check also that the location of food is not occupied by any obstacle
    if (!snake.SnakeCell(x, y) && !_obstacle->ObstacleCell(x,y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Feat: check if the snake run into an obstacle
  if(_obstacle->ObstacleCell(new_x,new_y)){
    snake.alive = false;
    return;
  }
  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    
    // Feat: check if the game mode is difficult and the max obstacle count is not reached to add obstacle every level
    if((_mode == GameMode::Difficult) && _obstacle->GetObstacleCount()!=Obstacle::MAX_OBSTACLE_COUNT && score%levelScore==0)
    {
        _obstacle->CreateObstacle();
    }

    // Feat: after every 15 points reset/remove the obstacles
    if(score % 15 == 0) 
      _obstacle->RemoveObstacle();

    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
