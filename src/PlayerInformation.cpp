#include "PlayerInformation.h"

PlayerInformation::PlayerInformation() {
    score = 0;
    coins = 0;
    time = 1000;
    lives = 3;    
}

void PlayerInformation::SetWorld(const std::string &world) {
    this->world = world;
}

void PlayerInformation::UpdateScore(const int &s) {
    score += s;
}

void PlayerInformation::UpdateCoins(const int &c) {
    coins += c;
}

void PlayerInformation::UpdateTime(const float &dt) {
    time -= dt;
}

void PlayerInformation::Draw() const {
    Font_Sprite::DrawText("SCORE", 50, 50); //[50, 174]
    Font_Sprite::DrawText(std::to_string(score), 112 - (std::to_string(score).size() * 25 - 1) / 2.0f, 82);
    Font_Sprite::DrawText("COINS", 224, 50); //[224, 348]
    Font_Sprite::DrawText(std::to_string(coins), 286 - (std::to_string(coins).size() * 25 - 1) / 2.0f, 82);
    Font_Sprite::DrawText("WORLD", 398, 50); //[398, 522]
    Font_Sprite::DrawText(world, 460 - (world.size() * 25 - 1) / 2.0f, 82);
    Font_Sprite::DrawText("TIME", 572, 50); //[572, 671]
    Font_Sprite::DrawText(std::to_string(int(time)), 621.5f - (std::to_string(int(time)).size() * 25 - 1) / 2.0f, 82);
    Font_Sprite::DrawText("LIVES", 721, 50); //[721, 845]
    Font_Sprite::DrawText(std::to_string(lives), 783 - (std::to_string(lives).size() * 25 - 1) / 2.0f, 82);
}