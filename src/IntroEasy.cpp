#include "IntroEasy.h"

Intro_Easy::Intro_Easy(PlayerInformation &info, Player_Mode mode) : player_info(info), player_mode(mode)
{
    intro_easy = LoadTexture("../resources/map/Easy/Intro_Easy.png");
}

Intro_Easy::~Intro_Easy()
{
    UnloadTexture(intro_easy);
}

void Intro_Easy::Draw()
{
    ClearBackground(BLACK);
    player_info.Draw();
    Rectangle src_texture = {0, 0, intro_easy.width, intro_easy.height};
    float scale = 3.0f;
    Rectangle dest_texture = {(Screen_w - intro_easy.width * scale) / 2.0f, Screen_h * 2 / 3 - intro_easy.height * scale / 2.0f, intro_easy.width * scale, intro_easy.height * scale};
    DrawTexturePro(intro_easy, src_texture, dest_texture, {0, 0}, 0.0f, WHITE);

    Vector2 x = {(Screen_w - (8 * scale + 1.0f)) / 2.0f, dest_texture.y - 70.0f};
    Font_Sprite::DrawText("X", x.x, x.y, WHITE, scale);
    Vector2 live = {x.x + 8 * scale + 1.0f + 30.0f, x.y};
    Font_Sprite::DrawText(std::to_string(player_info.GetLives()), live.x, live.y, WHITE, scale);

    std::string world = "WORLD - EASY";
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

void Intro_Easy::Run()
{
    // Implement the run logic for the intro stage
}
