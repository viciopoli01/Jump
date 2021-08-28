#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>
#include <types.h>

/**
 * @brief Parent class for all the game objects like player, obstacles and
 * clouds
 *
 */
class GameObject {
 public:
  /**
   * @brief Construct a new Game Object object
   *
   * @param grid_width  width of the grid for placing the objects
   * @param grid_height height of the grid for placing the objects
   */
  GameObject(int grid_width, int grid_height);

  /**
   * @brief Pure virtual function to handle the update of the scene. Every
   * object has its won movement, this method implement the movement
   */
  virtual void Update() = 0;

  /**
   * @brief Pure vertual function for rendering the object. Each object has its
   * hown shape. this method implements and render the shape of the object.
   *
   * @param sdl_renderer  SDL_Renderer obj, for rendering the object
   * @param screen_height screen height of the window the obj is going to be
   * rendered
   * @param screen_width  screen width of the window the obj is going to be
   * rendered
   * @param grid_height   discretization of the window
   * @param grid_width    discretization of the window
   */
  virtual void Render(SDL_Renderer *sdl_renderer, int screen_height,
                      int screen_width) = 0;

  /**
   * @brief Speed of the object is going to move
   */
  float speed{0.1f};

  /**
   * @brief Set the Speed object
   *
   * @param speed new speed of the obj
   */
  void setSpeed(float speed);

  /**
   * @brief Set the Position object
   *
   * @param x new x position
   * @param y new y position
   */
  void setPosition(float x, float y);

  /**
   * @brief Check whether the current obj and the object 'other' collide
   *
   * @param a
   * @return true   the two obj intersect
   * @return false  the two obj don't intersect
   */
  bool colliding(GameObject const &other) const;

  /**
   * @brief x and y position of the object. default position is the center of
   * the screen.
   *
   */
  float x, y;

  /**
   * @brief color of the object, it's used in the rendering part.
   *
   */
  Color color;

 protected:
  /**
   * @brief Useful for rendering.
   *
   */
  int grid_width_, grid_height_;
};

#endif