#include "player.hpp"

const point_t& Player::position() const
{
  return position_;
}

double Player::getSpeed() const
{
  return speed_;
}

char Player::getSymbol() const
{
  return symbol_;
}

void Player::setSpeed(double speed)
{
  speed_ = speed;
}

void Player::setSymbol(char symbol)
{
  symbol_ = symbol;
}

void Player::moveBy(double dx, double dy)
{
  position_.x += dx;
  position_.y += dy;
}

void Player::rotate(double angle)
{
  viewDirectionAngle_ += angle;
}

double Player::getRotationSpeed() const
{
  return rotationSpeed_;
}

void Player::setRotationSpeed(double speed)
{
  rotationSpeed_ = speed;
}

double Player::getViewDirectionAngle() const
{
  return viewDirectionAngle_;
}

void Player::moveTo(const point_t& point)
{
  position_ = point;
}

double Player::getFOV() const
{
  return FOV_;
}

void Player::setFOV(double FOV)
{
  FOV_ = FOV;
}

double Player::getVisibilityRange() const
{
  return visibilityRange_;
}

void Player::setVisibilityRange(double visibilityRange)
{
  visibilityRange_ = visibilityRange;
}
