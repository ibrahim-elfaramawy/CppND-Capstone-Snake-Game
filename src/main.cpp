#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  
  // Feat: Render the Game Intro Window to ask the user to choose Normal/Difficult Game mode
  // For Normal Mode (press n) and For Difficult Mode (press d)
  // Normal Mode: snake initial speed is 0.1 and no obstacles created
  // Difficult Mode: snake initial speed is 0.2 and obstacles created 
  GameMode mode = Renderer::RenderGameIntro(kScreenWidth,kScreenHeight,"../GameIntro.bmp");
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  
  Controller controller;
  Game game(kGridWidth, kGridHeight, mode);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}
