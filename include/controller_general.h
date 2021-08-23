#ifndef GENERAL_CONTROLLER_H
#define GENERAL_CONTROLLER_H

#include "player.h"

class GeneralController {
 public:
  virtual void HandleInput(bool &running, Player &player) = 0;

 protected:
  void ChangeDirection(Player &player, Player::Action input) const {
    player.direction = input;
    return;
  }
};

#endif