#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <types.h>
#include "SDL.h"

class GameObject {
 public:
  GameObject(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        x(grid_width / 2),
        y(grid_height / 2) {}

  virtual void Update() = 0;
  virtual void Render(SDL_Renderer *sdl_renderer, int screen_height, int screen_width, int grid_height, int grid_width) = 0;

  float speed{0.1f};
  void setSpeed(float speed);
  void setPosition(float x, float y);

  bool colliding(GameObject const &a) const;

  float x, y, height{1.0f};
  Color color;

 private:
  int grid_width;
  int grid_height;
};

#endif