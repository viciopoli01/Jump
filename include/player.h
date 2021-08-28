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
    speed = 1.0;
  };
    
  void Render(SDL_Renderer *sdl_renderer, int screen_height, int screen_width);

  void Update();
  void Died();

  int jump_intensity{0};

  bool alive = true;

  Action action = Action::STAY;

  void setPosition(float x, float y);

 private:
  void Jump();
  int steps_{0};
  bool is_jumping_ = false;
  bool jump_max_ = false;
  int grid_width;
  int grid_height;
  float starting_y{0.0};
};

#endif