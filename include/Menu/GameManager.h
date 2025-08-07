#pragma once
#include "Constants.h"
#include "Stage.h"
#include "EasyMap.h"
#include "MediumMap.h"
#include "HardMap.h"
#include "Sprite.h"
#include "PauseManager.h"

class Stage; // Forward declaration

// Chế độ chơi
enum class Game_Mode
{
    Play_Through,
    Play_Level
};

class GameManager
{
public:
    GameManager();
    ~GameManager();

    int Update();
    void Draw();
    //Dùng để khởi tạo map mới khi từ menu chuyển sang game
    void SetDifficulty(Difficulty diff);
    //Dùng để reset game khi player chết
    void ResetGame(Difficulty diff);
    void Load_Texture();
    void Unload_Texture();
    //Set chế độ player
    void SetPlayerMode(Player_Mode mode);
    Player_Mode GetPlayerMode() const;
    //Set chế độ game
    void SetGameMode(Game_Mode mode);
    Game_Mode GetGameMode() const;
    PlayerInformation& GetPlayerInformation() const;

private:
    Stage *stage;
    // Quản lý pause
    PauseManager *pause_manager;
    // Thông tin người chơi
    PlayerInformation *player_info;
    Difficulty difficulty;
    Player_Mode player_mode = Player_Mode::MARIO_PLAYER;
    Game_Mode game_mode = Game_Mode::Play_Through;
    // Trạng thái game over
    bool GameOver;
    bool TimeUp;
};
