#ifndef CLOUD_H
#define CLOUD_H

#include <game_object.h>

/**
 * @brief Cloud class to render and move the clouds.
 * Extend the GameObject parent class.
 *
 */
class Cloud : public GameObject {
 public:
  /**
   * @brief Construct a new Cloud object
   *
   * @param grid_width  Needed from the Parent constructor
   * @param grid_height Needed from the Parent constructor
   */
  Cloud(int grid_width, int grid_height);

  /**
   * @brief implement the parent pure virtual functions
   */
  void Update();
  void Render(SDL_Renderer *sdl_renderer, int screen_height, int screen_width);
};

#endif