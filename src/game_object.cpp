#include <game_object.h>
#include <iostream>

void GameObject::setPosition(float x, float y) {
  this->x = x;
  this->y = y;
}

void GameObject::setSpeed(float speed) { this->speed = speed; }

bool GameObject::colliding(GameObject const &a) const {
  return (int)this->x == (int)a.x && (int)this->y == (int)a.y;
}

