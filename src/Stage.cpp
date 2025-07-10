#include "Stage.h"

Stage::Stage() {
    source = {0, 0, 416, 240};
    dest = {0, 0, Screen_w, Screen_h};
}

Stage::~Stage() {}

void Stage::Draw() {
    DrawTexturePro(MapTexture, source, dest, {0, 0}, 0, WHITE);
}