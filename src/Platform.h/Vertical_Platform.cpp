#include "Platform/Vertical_Platform.h"

Vertical_Platform::Vertical_Platform(Vector2 position, float speed)
    : I_Platform(position, Vector2{0, speed})
{
    animation = Animation(&Win_Animation::win_animation_, Platform::vertical_);
}
