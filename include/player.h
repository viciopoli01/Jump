#ifndef PLAYER_H
#define PLAYER_H

#include <game_object.h>
#include <cmath>

class Player : public GameObject {
 public:
  enum class Action { JUMP, STAY };

  Player(int grid_width, int grid_height)
      : GameObject(grid_width, grid_height) {
    x = (int)(grid_width * 0.2);
    color = Colors().Blue;
  };
  void Update();
  void Died();

  int jump_intensity{0};

  bool alive = true;

  Action direction = Action::JUMP;

 private:
  int grid_width;
  int grid_height;
};

#endif