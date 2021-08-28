#include <game_object.h>

GameObject::GameObject(int grid_width, int grid_height)
    : grid_width_(grid_width),
      grid_height_(grid_height),
      x(grid_width / 2),
      y(grid_height / 2) {}

void GameObject::setPosition(float x, float y) {
  this->x = x;
  this->y = y;
}

void GameObject::setSpeed(float speed) { this->speed = speed; }

bool GameObject::colliding(GameObject const &other) const {
  return (int)this->x == (int)other.x && (int)this->y == (int)other.y;
}
