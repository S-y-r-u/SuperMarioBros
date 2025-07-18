#include "Stage.h"

Stage::Stage() {
    source = {0, 0, 3424, 240};
    dest = {0, 0, 10272, 720};
}

Stage::~Stage() {}

void Stage::Run() {
    if(IsKeyPressed(KEY_A))
        player->MoveLeft();
    else if(IsKeyPressed(KEY_D))
        player->MoveRight();

    player->update(GetFrameTime());

    camera.target = player->getPosition();
}

void Stage::Draw() {
    Run();
    BeginMode2D(camera);
    DrawTexturePro(MapTexture, source, dest, {0, 0}, 0, WHITE);
    player->draw();
    EndMode2D();
}