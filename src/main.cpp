#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

#include "bodycontroller.h"

int main() {
  constexpr std::size_t kFramesPerSecond{30}; //same as camera rate
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{1280};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{64};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);

#ifdef BODY_CONTROL
  BodyController controller;
  controller.start(0);
  Game<BodyController> game(kGridWidth, kGridHeight);
#else
  Controller controller;
  Game<Controller> game(kGridWidth, kGridHeight);
#endif

  game.Run(controller, renderer, kMsPerFrame);

  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  return 0;
}