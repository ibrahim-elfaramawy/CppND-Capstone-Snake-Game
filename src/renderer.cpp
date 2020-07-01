#include "renderer.h"
#include <iostream>
#include <string>

// Feat: Render the Game Intro Window to ask the user to choose Normal/Difficult Game mode
// For Normal Mode (press n) and For Difficult Mode (press d)
// Default mode is Normal
GameMode Renderer::RenderGameIntro(const std::size_t screen_width, const std::size_t screen_height, const char* imageFileName)
{
  GameMode gameMode;

  // Feat: create the game intro window in the center of the screen with the input width/height
  SDL_Window *winIntro =  SDL_CreateWindow("Snake 2D Game Intro", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, 0);
  // Feat: get the window surface to load the image on it
  SDL_Surface *Surface = SDL_GetWindowSurface(winIntro);

  // Feat: load the Game intro image 
  SDL_Surface *image = SDL_LoadBMP(imageFileName);
 
  if(!image)
  {
      std::cout << "Failed to load image\n";
      std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
  }

// Feat: check the user key input and the set the game mode accordingly
  bool keep_window_open = true;
  while(keep_window_open)
  {
    SDL_Event e;
    while(SDL_PollEvent(&e) > 0)
    {
        if (e.type == SDL_QUIT) 
        {
            keep_window_open = false;
            break;
        }
        else if (e.type == SDL_KEYDOWN) 
        {
          switch (e.key.keysym.sym) 
          {
            case SDLK_n:
              gameMode = GameMode::Normal;
              break;
            case SDLK_d:
              gameMode = GameMode::Difficult;
              break;
            default:
              gameMode = GameMode::Normal;
              break;
          }
          keep_window_open = false;
          break;
        }
        // Feat: keep showing the game intro image until a successful key input from the user
        SDL_BlitSurface(image, NULL, Surface, NULL);
        SDL_UpdateWindowSurface(winIntro);
    }
  } 
  // Feat: free the window surface from the loaded image and destroy the game intro window 
  SDL_FreeSurface(image);
  SDL_DestroyWindow(winIntro);
  return gameMode;
}

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  
  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}


void Renderer::Render(Snake const snake, SDL_Point const &food, Obstacle const &obstacle) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Feat: Render Obstacles (color: green) based on the obstacle body points
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x80, 0x00, 0xFF);
  for (SDL_Point const &point : obstacle.GetObstacleBody()) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

// Feat: add level and mode to be updated in the window title
void Renderer::UpdateWindowTitle(int score, int fps, int level, GameMode mode) {
  std::string modeStr = (mode == GameMode::Normal) ? "Normal" : "Difficult";
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps) + "\t\t Level:" + std::to_string(level)+ "\t\t Game Mode:" + modeStr};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
