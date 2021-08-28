#include <cloud.h>

Cloud::Cloud(int grid_width, int grid_height)
    : GameObject(grid_width, grid_height) {
  color = Colors().White;
  speed = 1.0;
};

void Cloud::Update() { x -= speed; }

void Cloud::Render(SDL_Renderer *sdl_renderer, int screen_height,
                   int screen_width) {
  int d_x = screen_width / grid_width_;
  int d_y = screen_height / grid_height_;
  SDL_Rect cloud;

  for (int i = 0; i < 4; i++) {
    cloud.x = static_cast<int>(x) * d_x + (i * d_x);
    cloud.y = y - i * d_y;
    cloud.w = (10 - i * sqrt(i)) * d_x;
    cloud.h = d_y;
    SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(sdl_renderer, &cloud);
  }
}