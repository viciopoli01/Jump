#ifndef PLAYER_H
#define PLAYER_H

#include <game_object.h>
#include <cmath>

/**
 * @brief Define the player class as child of the GameObject class
 *
 */
class Player : public GameObject {
 public:
  /**
   * @brief Set of actions a player can do
   */
  enum class Action { JUMP, STAY };

  /**
   * @brief Construct a new Player object
   *
   * @param grid_width
   * @param grid_height
   */
  Player(int grid_width, int grid_height)
      : GameObject(grid_width, grid_height) {
    x = (int)(grid_width * 0.2);
    color = Colors().Blue;
    speed = 1.0;
  };

  /**
   * @brief Define the pure virtual function of the parent class
   *
   */
  void Update();
  void Render(SDL_Renderer *sdl_renderer, int screen_height, int screen_width);

  /**
   * @brief Set alive to false and end the game rendering.
   */
  void Died();

  /**
   * @brief if false the render stops.
   */
  bool alive = true;

  /**
   * @brief the action the player is performing.
   *
   */
  Action action = Action::STAY;

  /**
   * @brief Override the setPosition method of the parent class.
   *
   * @param x
   * @param y
   */
  void setPosition(float x, float y) override;

 private:
  /**
   * @brief simulate the jump
   *
   */
  void Jump();

  bool is_jumping_ = false;
  bool jump_max_ = false;

  /**
   * @brief To know where the jump ends.
   */
  float starting_y_{0.0};
};

#endif