#ifndef CLOUD_H
#define CLOUD_H

#include <game_object.h>

class Cloud : public GameObject {
 public:
  Cloud(int grid_width, int grid_height)
      : GameObject(grid_width, grid_height) {
    color = Colors().White;
    speed = 1.0;
  };
  void Update();

  void Render(SDL_Renderer *sdl_renderer, int screen_height, int screen_width, int grid_height, int grid_width);

 private:
  int grid_width;
  int grid_height;
};

#endif