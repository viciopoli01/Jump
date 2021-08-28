#include <player.h>

void Player::setPosition(float x, float y) {
  this->y = y;
  starting_y = y;
}

void Player::Update() {
  if (is_jumping_) Jump();  // the jump held for more than one frame

  if (!is_jumping_ && action == Player::Action::JUMP) {
    action = Player::Action::STAY;
    is_jumping_ = true;
    speed = 10.0;
    Jump();
  }
}

void Player::Jump() {
  if (!jump_max_) {
    if (y > 20) {
      y -= 0.1 * speed;
    } else {
      jump_max_ = true;
    }
    if (speed > 1)
      speed--;
    else
      jump_max_ = true;
  } else {
    if (speed < 10.0)
      speed++;
    else {
      y = starting_y;
      jump_max_ = false;
      is_jumping_ = false;
    }
    if (y < starting_y) {
      y += 0.1 * speed;
    } else {
      y = starting_y;
      jump_max_ = false;
      is_jumping_ = false;
    }
  }
}

void Player::Died() {
  alive = false;
  color = Colors().Red;
}

void Player::Render(SDL_Renderer *sdl_renderer, int screen_height,
                    int screen_width) {
  SDL_Rect block;
  block.w = screen_width / grid_width_;
  block.h = screen_height / grid_height_;

  // Render the obstacles
  block.x = static_cast<int>(x) * block.w;
  block.h = (screen_height / grid_height_);
  block.y = static_cast<int>(y) * block.h;
  SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(sdl_renderer, &block);
}