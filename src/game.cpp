#include "game.h"
#include <iostream>
#include "SDL.h"

template <typename T>
Game<T>::Game(std::size_t grid_width, std::size_t grid_height)
    : peppe(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      max_width_(static_cast<int>(grid_width)),
      max_height_(static_cast<int>(grid_height)) {
  peppe.setPosition(0, (int)(0.9 * grid_height));

  for (int i = 0; i < 5; i++) {
    Obstacle p(grid_width, grid_height);
    p.setPosition(grid_width + 10 * i, (int)(0.9 * grid_height));
    p.color = Colors().Green;
    obstacles_.emplace_back(p);
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
    controller.HandleInput(running, peppe);
    Update();
    renderer.ClearScreen();
    for (Obstacle& o : obstacles_) renderer.PrepareRendering(o);
    renderer.PrepareRendering(peppe);
    // renderer.PrepareRendering(peppe);
    renderer.Render();
    // renderer.Render(snake, food, obstacles_);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
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

// template <typename T>
// void Game<T>::PlaceObstacles() {
//   for (SDL_Point& o : obstacles_) {
//     o.x = o.x - 1;
//     std::cout << max_width_ << std::endl;
//     if (o.x < 0) {
//       o.x = max_width_ + 1;
//     }
//   }
// }

template <typename T>
void Game<T>::Update() {
  if (!peppe.alive) return;

  // snake.Update();
  peppe.Update();

  int x_rand = random_w(engine);
  for (int i = 0; i < obstacles_.size(); i++) {
    if (obstacles_[i].x < 0)
      obstacles_[i].x += 100 * i * obstacles_[i].speed + max_width_;
    obstacles_[i].Update();
    // if(o.colliding(peppe))peppe.Died();
    if (obstacles_[i].speed < 0.5) obstacles_[i].speed += 0.02;
  }
  score++;
}

template <typename T>
int Game<T>::GetScore() const {
  return score;
}

template <typename T>
int Game<T>::GetSize() const {
  return 1;  // snake.size;
}

template class Game<BodyController>;
template class Game<Controller>;