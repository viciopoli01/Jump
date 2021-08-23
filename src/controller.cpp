#include "controller.h"
#include <iostream>
#include "SDL.h"


void Controller::HandleInput(bool &running, Player &player) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(player, Player::Action::JUMP);
          break;
        default:
          ChangeDirection(player, Player::Action::STAY);
      }
    }
  }
}