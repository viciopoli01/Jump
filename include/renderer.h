#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <SDL_ttf.h>
#include "SDL.h"
#include "game_object.h"
#include "snake.h"


class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void ClearScreen();
  void PrepareRendering(GameObject &element);
  void Render();

  void Render(Snake const snake, SDL_Point const &food,
              std::vector<SDL_Point> const &obstacles);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif