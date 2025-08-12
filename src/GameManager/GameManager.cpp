#include "GameManager/GameManager.h"
#include "raylib.h"

GameManager::GameManager()
    : stage(nullptr),
      intro_stage(nullptr),
      current_stage(nullptr),
      pause_manager(new PauseManager()),
      player_info(nullptr),
      timer(0.0f) {}

GameManager::~GameManager()
{
    delete stage;
    delete pause_manager;
    delete intro_stage;
    current_stage = nullptr;
    delete player_info;
}

void GameManager::SetDifficulty(Difficulty diff)
{
    // Vào Game từ menu, cần khởi tạo stage và player_info
    difficulty = diff;

    // Delete the old stage if it exists
    if (intro_stage)
    {
        delete intro_stage;
        intro_stage = nullptr;
    }
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
            intro_stage = new Intro_Easy(*player_info, player_mode);
            stage = new EasyMap(player_mode, *player_info); // Replace with your actual Easy stage class
            current_stage = intro_stage;
            break;
        case Difficulty::Medium:
            player_info = new PlayerInformation(400, 3);
            player_info->SetWorld("MEDIUM");
            intro_stage = new Intro_Medium(*player_info, player_mode);
            stage = new MediumMap(player_mode, *player_info); // Replace with your actual Medium stage class
            current_stage = intro_stage;
            break;
        case Difficulty::Hard:
            player_info = new PlayerInformation(400, 3);
            player_info->SetWorld("HARD");
            intro_stage = new Intro_Easy(*player_info, player_mode);
            stage = new HardMap(player_mode, *player_info); // Replace with your actual Hard stage class
            current_stage = intro_stage;
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
        intro_stage = new Intro_Easy(*player_info, player_mode);
        stage = new EasyMap(player_mode, *player_info);
        current_stage = intro_stage;
    }
}

// Reset game when player dies
void GameManager::ResetGame(Difficulty diff)
{
    difficulty = diff;
    SoundManager::GetInstance().PlayMusic("playingMusic", true);
    // Delete the old stage if it exists
    if (intro_stage)
    {
        delete intro_stage;
        intro_stage = nullptr;
    }
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
            intro_stage = new Intro_Easy(*player_info, player_mode);
            stage = new EasyMap(player_mode, *player_info); // Replace with your actual Easy stage class
            current_stage = intro_stage;
            break;
        case Difficulty::Medium:
            intro_stage = new Intro_Medium(*player_info, player_mode);
            stage = new MediumMap(player_mode, *player_info); // Replace with your actual Medium stage class
            current_stage = intro_stage;
            break;
        case Difficulty::Hard:
            intro_stage = new Intro_Easy(*player_info, player_mode);
            stage = new HardMap(player_mode, *player_info); // Replace with your actual Hard stage class
            current_stage = intro_stage;
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
            intro_stage = new Intro_Easy(*player_info, player_mode);
            stage = new EasyMap(player_mode, *player_info); // Replace with your actual Easy stage class
            current_stage = intro_stage;
            break;
        case Difficulty::Medium:
            intro_stage = new Intro_Medium(*player_info, player_mode);
            stage = new MediumMap(player_mode, *player_info); // Replace with your actual Medium stage class
            current_stage = intro_stage;
            break;
        case Difficulty::Hard:
            intro_stage = new Intro_Easy(*player_info, player_mode);
            stage = new HardMap(player_mode, *player_info); // Replace with your actual Hard stage class
            current_stage = intro_stage;
            break;
        default:
            stage = nullptr;
            break;
        }
    }
}

void GameManager::TransGame()
{
    switch (difficulty)
    {
    case Difficulty::Easy:
        player_info->SetWorld("MEDIUM");
        difficulty = Difficulty::Medium;
        break;
    case Difficulty::Medium:
        player_info->SetWorld("HARD");
        difficulty = Difficulty::Hard;
        break;
    default:
        break;
    }
    SoundManager::GetInstance().PlayMusic("playingMusic", true);
    // Delete the old stage if it exists
    if (intro_stage)
    {
        delete intro_stage;
        intro_stage = nullptr;
    }
    if (stage)
    {
        delete stage;
        stage = nullptr;
    }
    player_info->ResetTime();
    switch (difficulty)
    {
    case Difficulty::Medium:
        intro_stage = new Intro_Medium(*player_info, player_mode);
        stage = new MediumMap(player_mode, *player_info); // Replace with your actual Medium stage class
        current_stage = intro_stage;
        break;
    case Difficulty::Hard:
        intro_stage = new Intro_Easy(*player_info, player_mode);
        stage = new HardMap(player_mode, *player_info); // Replace with your actual Hard stage class
        current_stage = intro_stage;
        break;
    }
}

int GameManager::Update()
{
    if (current_stage == intro_stage)
    {
        timer += GetFrameTime();
        if (timer >= End_Intro)
        {
            current_stage = stage;
            timer = 0.0f;
        }
    }
    else
    // Lấy trạng thái pause
    {
        Stage *cur_stage = dynamic_cast<Stage *>(current_stage);
        int pause_select = PauseSelect::Pause_None_Select;
        if (!cur_stage->Game_Won())
            pause_select = pause_manager->Get_Pause_Select(); // Get_Pause_Select() sử dụng Update_() của I_Pause_State
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
            cur_stage->Run();
        }
        else
            cur_stage->Clear_Keyboard();

        // Reset game if player dies
        if (cur_stage->Need_Reset_Game())
        {
            player_info->DecreaseLives();
            if (player_info->GetLives() <= 0)
                return gameOverState; // Trả về trạng thái Game Over nếu hết mạng
            // Trả về trạng thái Time Up nếu hết thời gian
            ResetGame(difficulty);
        }
        if (player_info->GetTime() <= 0.0f && !cur_stage->Game_Won())
        {
            return timeUpState;
        }
        if (cur_stage->Trans_Game() && difficulty != Difficulty::Hard && game_mode == Game_Mode::Play_Through)
        {
            TransGame();
        }
        else if(cur_stage->Trans_Game())
            return menuState;
    }
    return gameManagerState; // Continue in game manager state
}

void GameManager::Draw()
{
    current_stage->Draw(); // Assuming Stage has a Draw method
    // Draw stage and game elements here
    if (pause_manager->Get_Pause_State() != PauseState::Pause_None_State)
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{0, 0, 0, 128});
    }
    if (dynamic_cast<Stage *>(current_stage))
    {
        pause_manager->Draw();
    }
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
    Intro::intro_.Load_("../resources/sprite/Intro.png");
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
    Intro::intro_.Unload_();
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