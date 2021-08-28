#include <obstacle.h>

void Obstacle::Update() {
  x -= speed;
} 

void Obstacle::Render(SDL_Renderer *sdl_renderer, int screen_height, int screen_width) {
  SDL_Rect block;
  block.w = screen_width / grid_width_;
  block.h = screen_height / grid_height_;

  // Render the obstacles
  block.x = static_cast<int>(x) * block.w;
  block.h = (screen_height / grid_height_);
  block.y = static_cast<int>(y) * block.h;
  SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g,
                         color.b, color.a);
  SDL_RenderFillRect(sdl_renderer, &block);
}