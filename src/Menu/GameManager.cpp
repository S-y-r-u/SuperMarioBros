#include "Menu/GameManager.h"
#include "raylib.h"


GameManager::GameManager() : stage(nullptr) {}

GameManager::~GameManager()
{
    delete stage;
}

void GameManager::SetDifficulty(Difficulty diff)
{
    difficulty = diff;

    // Delete the old stage if it exists
    if (stage)
    {
        delete stage;
        stage = nullptr;
    }

    // Create a new stage based on the selected difficulty
    switch (difficulty)
    {
    case Difficulty::Easy:
        stage = new EasyMap(); // Replace with your actual Easy stage class
        break;
    case Difficulty::Medium:
        stage = new MediumMap(); // Replace with your actual Medium stage class
        break;
    case Difficulty::Hard:
        stage = new HardMap(); // Replace with your actual Hard stage class
        break;
    default:
        stage = nullptr;
        break;
    }
}

int GameManager::Update()
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        return menuState;
    }
    return gameManagerState; // Continue in game manager state
}


void GameManager::Draw()
{
    stage->Draw(); // Assuming Stage has a Draw method
    // Draw stage and game elements here
}

void GameManager::Load_Texture()
{
    Mario_Sprite::mario_sprite.Load_("../resources/sprite/Mario.png");
    Luigi_Sprite::luigi_sprite.Load_("../resources/sprite/Luigi.png");
    Item_Sprite::item_.Load_("../resources/sprite/Items_Blocks.png");
    Font_Sprite::font_.Load_("../resources/sprite/Font.png");
    Enemies_Sprite::enemies_.Load_("../resources/sprite/Enemies.png");
    Screen_Sprite::screen_.Load_("../resources/sprite/GameOver_TimeUp.png");
    BomberBill_Sprite::bomber_bill_.Load_("../resources/sprite/BomberBill.png");
}

void GameManager::Unload_Texture()
{
    Mario_Sprite::mario_sprite.Unload_();
    Luigi_Sprite::luigi_sprite.Unload_();
    Item_Sprite::item_.Unload_();
    Font_Sprite::font_.Unload_();
    Enemies_Sprite::enemies_.Unload_();
    Screen_Sprite::screen_.Unload_();
    BomberBill_Sprite::bomber_bill_.Unload_();
}
