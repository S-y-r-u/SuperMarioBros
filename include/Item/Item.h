#pragma once
#include "Constants.h"
#include "Sprite.h"

class Character;

constexpr float Mush_Room_And_Star_Speed = 1.8f;
constexpr float Appear_Animation = 1.5f;
constexpr float Tile_Size = 16.0f * scale_screen;

class Item
{
private:
    SpriteSheet item_;

protected:
    Vector2 pos_;
    Rectangle rec_;
    int frame_, type_;
    bool appear_animation;
    bool is_delete;

public:
    Item(Vector2 pos);

    void Draw_();
    virtual void Update_() = 0;
    virtual void Appear_() = 0;
    //
    virtual void Activate_(Character &character) = 0;

    Vector2 Get_Pos() const;
    Rectangle Get_Source_Rec() const;
    Rectangle Get_Draw_Rec() const;
    bool Is_Appear_Animation() const;
    bool Get_Is_Delete() const;

    virtual void Notify_Fall();
    virtual void Notify_On_Ground();
    virtual void Notify_Change_Direct();
};
