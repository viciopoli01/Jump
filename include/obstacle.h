#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <game_object.h>
#include <cmath>

/**
 * @brief Obstacle class, parent of GameObject
 *
 */
class Obstacle : public GameObject {
 public:
  /**
   * @brief Construct a new Obstacle object
   *
   * @param grid_width
   * @param grid_height
   */
  Obstacle(int grid_width, int grid_height)
      : GameObject(grid_width, grid_height){};

  /**
   * @brief Declare pure virtual functions of the parent
   */
  void Update();
  void Render(SDL_Renderer *sdl_renderer, int screen_height, int screen_width);
};

#endif