#ifndef GENERAL_CONTROLLER_H
#define GENERAL_CONTROLLER_H

#include <player.h>

/**
 * @brief Parent class for the controller
 *
 */
class GeneralController {
 public:
  /**
   * @brief Each controller handle the inputs in diferent ways
   *
   * @param running
   * @param player
   */
  virtual void HandleInput(bool &running, Player &player) = 0;

 protected:
  /**
   * @brief all the controllers command the same object, with the same action
   *
   * @param player  obj that execute the command
   * @param input   command
   */
  void ChangeDirection(Player &player, Player::Action input) const {
    player.action = input;
  }
};

#endif