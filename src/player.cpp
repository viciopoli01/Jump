#include <player.h>

#include <iostream>

void Player::setPosition(float x, float y) {
  this->y = y;
  starting_y = y;
}

void Player::Update() {
  if (is_jumping_) Jump();  // the jump held for more than one frame

  if (!is_jumping_ && action == Player::Action::JUMP) {
    action = Player::Action::STAY;
    std::cout << "Jump\n";
    is_jumping_ = true;
    speed = 10.0;
    Jump();
  }
}

void Player::Jump() {
  std::cout << "Y : " << y << "\n";

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