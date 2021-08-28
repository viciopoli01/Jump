#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "controller_general.h"
#include "player.h"

/**
 * @brief Keyboard controller
 * 
 */
class Controller : GeneralController {
 public:
  void HandleInput(bool &running, Player &player) override;
};

#endif