#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <game_object.h>
#include <cmath>

class Obstacle : public GameObject {
 public:
  Obstacle(int grid_width, int grid_height)
      : GameObject(grid_width, grid_height){};
  void Update();
  void Render(SDL_Renderer *sdl_renderer, int screen_height, int screen_width);

 private:
  int grid_width;
  int grid_height;
};

#endif