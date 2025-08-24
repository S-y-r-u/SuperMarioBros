#include "raylib.h"
#include "sprite.h"
#include "Constants.h"
#include "GameManager/Animation.h"

class Fire_Block
{
private:
    Animation fire_animation;
    Vector2 pos;

public:
    Fire_Block(Vector2 pos);
    void Update();
    void Draw();
    Vector2 Get_Pos();
};
