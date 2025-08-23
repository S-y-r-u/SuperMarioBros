#include "Player/Character.h"

Character ::Character(Vector2 startPos) : position(startPos), isGround(1), isFacingLeft(0) {}

Character ::~Character() {}

Vector2 Character ::getPosition() const
{
    return position;
}