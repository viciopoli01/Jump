#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <body_controller.h>
#include <cloud.h>
#include <controller.h>
#include <obstacle.h>
#include <player.h>
#include <renderer.h>
#include <types.h>
#include <random>

template <class T>
class Game {
 public:
  /**
   * @brief Construct a new Game object
   *
   * @param grid_width
   * @param grid_height
   */
  Game(std::size_t grid_width, std::size_t grid_height);

  /**
   * @brief Start the game
   *
   * @param controller            controller can be either BodyController or
   *                              Controller
   * @param renderer              the render object that render the game
   * @param target_frame_duration target frame rate
   */
  void Run(T& controller, Renderer& renderer,
           std::size_t target_frame_duration);

  /**
   * @brief Get the Score object
   * 
   * @return int score
   */
  int GetScore() const;

 private:
  std::random_device dev_;
  std::mt19937 engine_;
  std::uniform_int_distribution<int> random_w_;

  Player player_;
  std::vector<Obstacle> obstacles_;
  std::vector<Cloud> clouds_;
  
  float speed_{0.01};
  int score_{0};
  const int max_width_, max_height_;

  void PlaceObstacles();

  void PlaceFood();
  void Update();
};

#endif