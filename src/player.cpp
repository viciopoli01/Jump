#include <player.h>

void Player::Update() { y += speed * jump_intensity; }
void Player::Died() {
  alive = false;
  color = Colors().Red;
}