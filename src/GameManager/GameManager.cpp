#include "GameManager/GameManager.h"
#include "raylib.h"

GameManager::GameManager()
    : stage(nullptr),
      intro_stage(nullptr),
      current_stage(nullptr),
      pause_manager(new PauseManager()),
      player_info(nullptr),
      outro_stage(nullptr),
      player(nullptr),
      prev_player_info(nullptr) {}

GameManager::~GameManager()
{
    delete stage;
    delete pause_manager;
    delete intro_stage;
    delete stage;
    delete outro_stage;
    current_stage = nullptr;
    delete player_info;
    delete prev_player_info;
    delete player;
}

void GameManager::SetDifficulty(Difficulty diff)
{
    // Vào Game từ menu, cần khởi tạo stage và player_info
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
    if (outro_stage)
    {
        delete outro_stage;
        outro_stage = nullptr;
    }
    if (player_info)
    {
        delete player_info;
        player_info = nullptr;
    }
    if (prev_player_info)
    {
        delete prev_player_info;
        prev_player_info = nullptr;
    }
    if (player)
    {
        delete player;
        player = nullptr;
    }

    // Vào Game từ chọn map
    if (game_mode == Game_Mode::Play_Level)
    {
        switch (difficulty)
        {
        case Difficulty::Easy:
            if (player_mode == Player_Mode::MARIO_PLAYER)
                player = new Mario({400, 200});
            else if (player_mode == Player_Mode::LUIGI_PLAYER)
                player = new Luigi({400, 200});
            player_info = new PlayerInformation(400, 3);
            player_info->SetWorld("EASY");
            intro_stage = new Intro_Easy(*player_info, player_mode);
            stage = new EasyMap(*player_info, player); // Replace with your actual Easy stage class
            break;
        case Difficulty::Medium:
            if (player_mode == Player_Mode::MARIO_PLAYER)
                player = new Mario({144, 624});
            else if (player_mode == Player_Mode::LUIGI_PLAYER)
                player = new Luigi({144, 624});
            player_info = new PlayerInformation(400, 3);
            player_info->SetWorld("MEDIUM");
            intro_stage = new Intro_Medium(*player_info, player_mode);
            stage = new MediumMap(*player_info, player); // Replace with your actual Medium stage class
            break;
        case Difficulty::Hard:
            if (player_mode == Player_Mode::MARIO_PLAYER)
                player = new Mario({48, 336});
            else if (player_mode == Player_Mode::LUIGI_PLAYER)
                player = new Luigi({48, 336});
            player_info = new PlayerInformation(400, 3);
            player_info->SetWorld("HARD");
            intro_stage = new Intro_Hard(*player_info, player_mode);
            stage = new HardMap(*player_info, player); // Replace with your actual Hard stage class
            break;
        default:
            stage = nullptr;
            break;
        }
    }
    // Vào Game từ Play
    if (game_mode == Game_Mode::Play_Through)
    {
        if (player_mode == Player_Mode::MARIO_PLAYER)
            player = new Mario({400, 200});
        else if (player_mode == Player_Mode::LUIGI_PLAYER)
            player = new Luigi({400, 200});
        player_info = new PlayerInformation(400, 6);
        player_info->SetWorld("EASY");
        intro_stage = new Intro_Easy(*player_info, player_mode);
        stage = new EasyMap(*player_info, player);
    }
    outro_stage = new Outro_Manager(player);
    current_stage = intro_stage;
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
    if (outro_stage)
    {
        delete outro_stage;
        outro_stage = nullptr;
    }
    if (player)
    {
        delete player;
        player = nullptr;
    }

    // Create a new stage based on the selected difficulty
    if (game_mode == Game_Mode::Play_Level)
    {
        player_info->ResetScore(0);
        player_info->ResetCoin(0);
        player_info->ResetTime();
    }
    else if (game_mode == Game_Mode::Play_Through)
    {
        if (prev_player_info)
        {
            player_info->ResetScore(prev_player_info->GetScore());
            player_info->ResetCoin(prev_player_info->GetCoins());
        }
        else
        {
            player_info->ResetScore(0);
            player_info->ResetCoin(0);
        }
        player_info->ResetTime();
    }

    switch (difficulty)
    {
    case Difficulty::Easy:
        if (player_mode == Player_Mode::MARIO_PLAYER)
            player = new Mario({400, 200});
        else if (player_mode == Player_Mode::LUIGI_PLAYER)
            player = new Luigi({400, 200});
        intro_stage = new Intro_Easy(*player_info, player_mode);
        stage = new EasyMap(*player_info, player); // Replace with your actual Easy stage class
        break;
    case Difficulty::Medium:
        if (player_mode == Player_Mode::MARIO_PLAYER)
            player = new Mario({144, 624});
        else if (player_mode == Player_Mode::LUIGI_PLAYER)
            player = new Luigi({144, 624});
        intro_stage = new Intro_Medium(*player_info, player_mode);
        stage = new MediumMap(*player_info, player); // Replace with your actual Medium stage class
        break;
    case Difficulty::Hard:
        if (player_mode == Player_Mode::MARIO_PLAYER)
            player = new Mario({48, 336});
        else if (player_mode == Player_Mode::LUIGI_PLAYER)
            player = new Luigi({48, 336});
        intro_stage = new Intro_Hard(*player_info, player_mode);
        stage = new HardMap(*player_info, player); // Replace with your actual Hard stage class
        break;
    default:
        stage = nullptr;
        break;
    }
    outro_stage = new Outro_Manager(player);
    current_stage = intro_stage;
}

void GameManager::TransGame()
{
    switch (difficulty)
    {
    case Difficulty::Easy:
        prev_player_info = new PlayerInformation(*player_info);
        player_info->SetWorld("MEDIUM");
        difficulty = Difficulty::Medium;
        break;
    case Difficulty::Medium:
        prev_player_info = new PlayerInformation(*player_info);
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
        player->Set_Pos({144, 624});
        player->Set_Disappear(false);
        stage = new MediumMap(*player_info, player); // Replace with your actual Medium stage class
        break;
    case Difficulty::Hard:
        intro_stage = new Intro_Hard(*player_info, player_mode);
        player->Set_Pos({48, 336});
        player->Set_Disappear(false);
        stage = new HardMap(*player_info, player); // Replace with your actual Hard stage class
        break;
    }
    current_stage = intro_stage;
}

int GameManager::Update()
{

    if (current_stage == intro_stage)
    {
        current_stage->Run();
        if (current_stage->Change_State())
            current_stage = stage; // Transition to the main stage after intro
    }
    else if (current_stage == stage)
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
        if (pause_select == PauseSelect::Pause_Save_Select)
        {
            json save_data = to_json();
            std::ofstream f("save.json");
            if (f.is_open())
            {
                f << save_data.dump(4);
                f.close();
            }
            return menuState;
        }
        // Chơi lại từ đầu
        if (pause_select == PauseSelect::Pause_Restart_Select && game_mode == Game_Mode::Play_Level)
        {
            SetDifficulty(difficulty);
            return gameManagerState;
        }
        if (pause_select == PauseSelect::Pause_Restart_Select && game_mode == Game_Mode::Play_Through)
        {
            SetDifficulty(Difficulty::Easy);
            return gameManagerState;
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
            return gameManagerState;
        }
        if (player_info->GetTime() <= 0.0f && !cur_stage->Game_Won())
        {
            return timeUpState;
        }
        if (cur_stage->Change_State() && difficulty != Difficulty::Hard && game_mode == Game_Mode::Play_Through)
        {
            TransGame();
        }
        else if (cur_stage->Change_State() && game_mode == Game_Mode::Play_Level)
            current_stage = outro_stage; // Transition to outro stage after completing the level
        else if (cur_stage->Change_State() && game_mode == Game_Mode::Play_Through && difficulty == Difficulty::Hard)
            current_stage = outro_stage;
    }
    else if (current_stage == outro_stage)
    {
        current_stage->Run();
        if (current_stage->Change_State())
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
    Outro_Animation::outro_.Load_("../resources/sprite/Outro.png");
    SavePrince::save_prince_.Load_("../resources/sprite/SavePrince.png");
    Bowser_Sprite::bowser_.Load_("../resources/sprite/Bowser.png");
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
    Outro_Animation::outro_.Unload_();
    SavePrince::save_prince_.Unload_();
    Bowser_Sprite::bowser_.Unload_();
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

json GameManager::to_json() const
{
    json j;
    j["difficulty"] = static_cast<int>(difficulty);

    j["player_mode"] = static_cast<int>(player_mode);
    j["game_mode"] = static_cast<int>(game_mode);
    if (player_info)
    {
        j["player_info"] = player_info->to_json();
    }
    if (prev_player_info)
    {
        j["prev_player_info"] = prev_player_info->to_json();
    }
    if (player)
    {
        j["player"] = player->to_json();
    }
    if (stage)
    {
        j["stage"] = stage->to_json();
    }
    // Có thể lưu thêm thông tin khác nếu cần
    return j;
}

void GameManager::from_json(const json &j)
{
    difficulty = static_cast<Difficulty>(j["difficulty"].get<int>());
    player_mode = static_cast<Player_Mode>(j.at("player_mode").get<int>());
    game_mode = static_cast<Game_Mode>(j.at("game_mode").get<int>());
    if (j.contains("player_info"))
    {
        if (player_info)
            delete player_info;
        player_info = new PlayerInformation(200, 5);
        player_info->from_json(j.at("player_info"));
    }
    if (j.contains("prev_player_info"))
    {
        if (prev_player_info)
            delete prev_player_info;
        prev_player_info = new PlayerInformation(200, 5);
        prev_player_info->from_json(j.at("prev_player_info"));
    }
    if (j.contains("player"))
    {
        if (player)
            delete player;
        if (player_mode == Player_Mode::MARIO_PLAYER)
        {
            player = new Mario({100, 100});
        }
        else if (player_mode == Player_Mode::LUIGI_PLAYER)
        {
            player = new Luigi({100, 100});
        }
        else
        {
            player = new Mario({100, 100});
        }
        player->from_json(j.at("player"));
    }
    if (j.contains("stage"))
    {
        if (stage)
            delete stage;
        switch (difficulty)
        {
        case Difficulty::Easy:
            stage = new EasyMap(*player_info, player);
            break;
        case Difficulty::Medium:
            stage = new MediumMap(*player_info, player);
            break;
        case Difficulty::Hard:
            stage = new HardMap(*player_info, player);
            break;
        }
        stage->from_json(j.at("stage"));
    }
    current_stage = stage;
    std::cerr << "Resources reinitialized." << std::endl;
}