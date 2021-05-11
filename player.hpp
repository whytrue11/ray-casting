#ifndef PLAYER_HPP
#define PLAYER_HPP

#define _USE_MATH_DEFINES
#include <math.h>

struct point_t
{
  double x;
  double y;
};

class Player
{
public:
  const point_t& position() const;

  double getSpeed() const;
  double getRotationSpeed() const;
  double getViewDirectionAngle() const;
  double getVisibilityRange() const;
  double getFOV() const;
  char getSymbol() const;

  void setSpeed(double speed);
  void setRotationSpeed(double speed);
  void setFOV(double FOV);
  void setVisibilityRange(double visibilityRange);
  void setSymbol(char symbol);

  void moveBy(double dx, double dy);
  void moveTo(const point_t& point);
  void rotate(double angle);

private:
  point_t position_ = {1, 1};
  double viewDirectionAngle_ = 0.8;
  int visibilityRange_ = 20;
  double FOV_ = M_PI / 3;

  double speed_ = 2;
  double rotationSpeed_ = 1;

  char symbol_ = '*';
};

#endif