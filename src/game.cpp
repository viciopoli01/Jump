#include "game.h"
#include <iostream>
#include "SDL.h"

template <typename T>
Game<T>::Game(std::size_t grid_width, std::size_t grid_height)
    : player_(grid_width, grid_height),
      engine_(dev_()),
      random_w_(0, static_cast<int>(grid_width - 1)),
      max_width_(static_cast<int>(grid_width)),
      max_height_(static_cast<int>(grid_height)) {
  player_.setPosition(0, (int)(PLAYER_POSITION * grid_height));

  for (int i = 0; i < 6; i++) {
    Obstacle p(grid_width, grid_height);
    p.setPosition(grid_width + 10 * i, (int)(PLAYER_POSITION * grid_height));
    p.color = Colors().Green;
    obstacles_.emplace_back(p);
  }
  for (int i = 0; i < 2; i++) {
    Cloud c(grid_width, grid_height);
    c.speed = c.speed * i;
    c.setPosition(grid_width + 10 * i, 50 * (i + 1));
    clouds_.emplace_back(c);
  }
  for (int i = 0; i < 3; i++) {
    Cloud c(grid_width, grid_height);
    c.speed = c.speed * (3 - i);
    c.setPosition(grid_width + 10 * i, 60 * (i + 1));
    clouds_.emplace_back(c);
  }
}

template <typename T>
void Game<T>::Run(T& controller, Renderer& renderer,
                  std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, player_);

    Update();

    renderer.ClearScreen();
    for (Obstacle& o : obstacles_) renderer.PrepareRendering(o);
    for (Cloud& c : clouds_) renderer.PrepareRendering(c);
    renderer.PrepareRendering(player_);
    renderer.Render();

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score_, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

template <typename T>
void Game<T>::Update() {
  if (!player_.alive) return;

  player_.Update();
  for (int i = 0; i < clouds_.size(); i++) {
    if (clouds_[i].x < 0) clouds_[i].x += i + max_width_;
    clouds_[i].Update();
  }

  int x_rand = random_w_(engine_);
  for (int i = 0; i < obstacles_.size(); i++) {
    if (obstacles_[i].x < 0)
      obstacles_[i].x += 100 * i * obstacles_[i].speed + max_width_;
    obstacles_[i].Update();
    if (obstacles_[i].colliding(player_)) player_.Died();
    if (obstacles_[i].speed < 0.5) obstacles_[i].speed += 0.02;
  }
  score_++;
}

template <typename T>
int Game<T>::GetScore() const {
  return score_;
}

#ifdef BODY_CONTROL
template class Game<BodyController>;
#else
template class Game<Controller>;
#endif