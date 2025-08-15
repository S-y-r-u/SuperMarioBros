#include "IntroHard.h"

Intro_Hard::Intro_Hard(PlayerInformation &info, Player_Mode mode)
    : Intro_Animation(info, mode)
{
    intro_ = LoadTexture("../resources/map/Hard/Intro_Hard.png");
}

Intro_Hard::~Intro_Hard()
{
    UnloadTexture(intro_);
}

void Intro_Hard::Draw()
{
    ClearBackground(BLACK);
    player_info.Draw();
    Rectangle src_texture = {0, 0, intro_.width, intro_.height};
    float scale = 3.0f;
    Rectangle dest_texture = {(Screen_w - intro_.width * scale) / 2.0f, Screen_h * 2 / 3 - intro_.height * scale / 2.0f, intro_.width * scale, intro_.height * scale};
    DrawTexturePro(intro_, src_texture, dest_texture, {0, 0}, 0.0f, WHITE);

    Vector2 x = {(Screen_w - (8 * scale + 1.0f)) / 2.0f, dest_texture.y - 70.0f};
    Font_Sprite::DrawText("X", x.x, x.y, WHITE, scale);
    Vector2 live = {x.x + 8 * scale + 1.0f + 30.0f, x.y};
    Font_Sprite::DrawText(std::to_string(player_info.GetLives()), live.x, live.y, WHITE, scale);

    std::string world = "WORLD - HARD";
    Vector2 world_pos = {(Screen_w - (world.size() * (8 * scale + 1.0f))) / 2.0f, x.y - (8 * scale + 1.0f) - 30.0f};
    Font_Sprite::DrawText(world, world_pos.x, world_pos.y, WHITE, scale);

    if (player_mode == Player_Mode::MARIO_PLAYER || player_mode == Player_Mode::LUIGI_PLAYER)
    {
        Rectangle src_player;
        if (player_mode == Player_Mode::MARIO_PLAYER)
            src_player = Intro::mario;
        else
            src_player = Intro::luigi;
        Rectangle dest_player = {x.x - src_player.width * scale - 30.0f, dest_texture.y - 80.0f, src_player.width * scale, src_player.height * scale};
        DrawTexturePro(Intro::intro_.sprite, src_player, dest_player, {0, 0}, 0.0f, WHITE);
    }
}

void Intro_Hard::Run()
{
    timer_ += GetFrameTime();
}

bool Intro_Hard::Change_State()
{
    return timer_ >= End_Intro;
}
