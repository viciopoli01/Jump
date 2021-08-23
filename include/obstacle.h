#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <game_object.h>
#include <cmath>

class Obstacle : public GameObject {
 public:
  Obstacle(int grid_width, int grid_height)
      : GameObject(grid_width, grid_height){};
  void Update();

 private:
  int grid_width;
  int grid_height;
};

#endif