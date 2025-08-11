#include "GameManager/GameManager.h"
#include "raylib.h"

GameManager::GameManager() : stage(nullptr), pause_manager(new PauseManager()), player_info(nullptr) {}

GameManager::~GameManager()
{
    delete stage;
    delete pause_manager;
    delete player_info;
}

void GameManager::SetDifficulty(Difficulty diff)
{
    // Vào Game từ menu, cần khởi tạo stage và player_info
    difficulty = diff;

    // Delete the old stage if it exists
    if (stage)
    {
        delete stage;
        stage = nullptr;
    }
    if (player_info)
    {
        delete player_info;
        player_info = nullptr;
    }

    // Vào Game từ chọn map
    if (game_mode == Game_Mode::Play_Level)
    {
        switch (difficulty)
        {
        case Difficulty::Easy:
            player_info = new PlayerInformation(400, 3);
            player_info->SetWorld("EASY");
            stage = new EasyMap(player_mode, *player_info); // Replace with your actual Easy stage class
            break;
        case Difficulty::Medium:
            player_info = new PlayerInformation(400, 3);
            player_info->SetWorld("MEDIUM");
            stage = new MediumMap(player_mode, *player_info); // Replace with your actual Medium stage class
            break;
        case Difficulty::Hard:
            player_info = new PlayerInformation(400, 3);
            player_info->SetWorld("HARD");
            stage = new HardMap(player_mode, *player_info); // Replace with your actual Hard stage class
            break;
        default:
            stage = nullptr;
            break;
        }
    }
    // Vào Game từ Play
    if (game_mode == Game_Mode::Play_Through)
    {
        player_info = new PlayerInformation(400, 6);
        player_info->SetWorld("EASY");
        stage = new EasyMap(player_mode, *player_info);
    }
}

// Reset game when player dies
void GameManager::ResetGame(Difficulty diff)
{
    difficulty = diff;
    SoundManager::GetInstance().PlayMusic("playingMusic",true);
    // Delete the old stage if it exists
    if (stage)
    {
        delete stage;
        stage = nullptr;
    }

    // Create a new stage based on the selected difficulty
    if (game_mode == Game_Mode::Play_Level)
    {
        player_info->ResetScore();
        player_info->ResetCoin();
        player_info->ResetTime();
        switch (difficulty)
        {
        case Difficulty::Easy:
            stage = new EasyMap(player_mode, *player_info); // Replace with your actual Easy stage class
            break;
        case Difficulty::Medium:
            stage = new MediumMap(player_mode, *player_info); // Replace with your actual Medium stage class
            break;
        case Difficulty::Hard:
            stage = new HardMap(player_mode, *player_info); // Replace with your actual Hard stage class
            break;
        default:
            stage = nullptr;
            break;
        }
    }

    // Reset game for Play_Through mode
    if (game_mode == Game_Mode::Play_Through)
    {
        player_info->ResetTime();
        switch (difficulty)
        {
        case Difficulty::Easy:
            stage = new EasyMap(player_mode, *player_info); // Replace with your actual Easy stage class
            break;
        case Difficulty::Medium:
            stage = new MediumMap(player_mode, *player_info); // Replace with your actual Medium stage class
            break;
        case Difficulty::Hard:
            stage = new HardMap(player_mode, *player_info); // Replace with your actual Hard stage class
            break;
        default:
            stage = nullptr;
            break;
        }
    }
}

int GameManager::Update()
{
    // Lấy trạng thái pause
    int pause_select = pause_manager->Get_Pause_Select(); // Get_Pause_Select() sử dụng Update_() của I_Pause_State
    if (pause_select == PauseSelect::Pause_Exit_Select)
    {
        return menuState;
    }
    // Chơi lại từ đầu
    if (pause_select == PauseSelect::Pause_Restart_Select && game_mode == Game_Mode::Play_Level)
    {
        SetDifficulty(difficulty);
    }
    if (pause_select == PauseSelect::Pause_Restart_Select && game_mode == Game_Mode::Play_Through)
    {
        SetDifficulty(Difficulty::Easy);
    }

    if (pause_manager->Get_Pause_State() == PauseState::Pause_None_State)
    {
        stage->Run();
    }
    else
        stage->Clear_Keyboard();

    // Reset game if player dies
    if (stage->Need_Reset_Game())
    {
        player_info->DecreaseLives();
        if (player_info->GetLives() <= 0)
            return gameOverState; // Trả về trạng thái Game Over nếu hết mạng
        // Trả về trạng thái Time Up nếu hết thời gian
        ResetGame(difficulty);
    }
    if (player_info->GetTime() <= 0.0f)
    {
        return timeUpState;
    }
    return gameManagerState; // Continue in game manager state
}

void GameManager::Draw()
{
    stage->Draw(); // Assuming Stage has a Draw method
    // Draw stage and game elements here
    if (pause_manager->Get_Pause_State() != PauseState::Pause_None_State)
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{0, 0, 0, 128});
    }
    pause_manager->Draw();
}

void GameManager::Load_Texture()
{
    Mario_Sprite::mario_sprite.Load_("../resources/sprite/Mario.png");
    Luigi_Sprite::luigi_sprite.Load_("../resources/sprite/Luigi.png");
    Item_Sprite::item_.Load_("../resources/sprite/Items_Blocks.png");
    Font_Sprite::font_.Load_("../resources/sprite/Font.png");
    Enemies_Sprite::enemies_.Load_("../resources/sprite/Enemies.png");
    Screen_Sprite::screen_.Load_("../resources/sprite/GameOver_TimeUp.png");
    Win_Animation::win_animation_.Load_("../resources/tiles/Tiles.png");
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
    Win_Animation::win_animation_.Unload_();
    BomberBill_Sprite::bomber_bill_.Unload_();
}

void GameManager::SetPlayerMode(Player_Mode mode)
{
    player_mode = mode;
}

Player_Mode GameManager::GetPlayerMode() const
{
    return player_mode;
}

void GameManager::SetGameMode(Game_Mode mode)
{
    game_mode = mode;
}

Game_Mode GameManager::GetGameMode() const
{
    return game_mode;
}

PlayerInformation &GameManager::GetPlayerInformation() const
{
    return *player_info;
}