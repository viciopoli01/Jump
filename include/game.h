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
  Game(std::size_t grid_width, std::size_t grid_height);

  void Run(T& controller, Renderer& renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  Player player_;
  std::vector<Obstacle> obstacles_;
  std::vector<Cloud> clouds_;
  float speed_{0.01};  // pixels per iteration
  int score{0};
  const int max_width_, max_height_;

  void PlaceObstacles();

  void PlaceFood();
  void Update();
};

#endif