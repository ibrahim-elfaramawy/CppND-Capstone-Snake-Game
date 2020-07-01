#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "obstacle.h"

// Feat: add Game mode enum for readability
enum GameMode {
  Normal=0,
  Difficult
};

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

 // Feat: pass obstacle variable by reference to the function
  void Render(Snake const snake, SDL_Point const &food, Obstacle const &obstacle);
  void UpdateWindowTitle(int score, int fps, int level, GameMode mode);

  // Feat: Render the Game Intro Window to ask the user to choose Normal/Difficult Game mode
  // For Normal Mode (press n) and For Difficult Mode (press d)
  static GameMode RenderGameIntro(const std::size_t screen_width, const std::size_t screen_height, const char* imageFileName);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Surface *sdl_surface;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
