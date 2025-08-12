#pragma once
#include "raylib.h"
#include "Constants.h"
#include "Mario.h"
#include "Luigi.h"
#include "Item/Item.h"
#include "Item/MushRoom.h"
#include "Item/Star.h"
#include "Item/Spawn_Item.h"
#include "Block/Block.h"
#include "Enemy/Enemy.h"
#include "Enemy/Goomba.h"
#include "Enemy/Latiku.h"
#include "Enemy/PiranhaPlant.h"
#include "Enemy/KoopaTroopa.h"
#include "Enemy/BomberBill.h"
#include "Enemy/Spawn_Enemy.h"
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <string>
#include "GameManager/PlayerInformation.h"
#include "GameManager/DrawScore.h"
#include "GameManager/Win_Animation.h"

class Stage
{
private:
    Rectangle source;
    Rectangle dest;

protected:
    Texture MapTexture;
    std::vector < std::vector < int > > Map;
    Player *player;
    PlayerInformation &information;
    Win_Animation_Manager *win_animation;
    Camera2D camera = {0};
    std::vector<KeyboardKey> Keyboard;

    std::vector<Item *> items;
    std::vector<Block *> blocks;
    std::vector<Enemy *> enemies;
    std::vector<FireBall *> fireballs;
    std::unordered_map<Enemy *, std::vector<Enemy *>> enemy_map;
    Player_Mode player_mode;
    Flag_Pole *flag_pole;
    // Thời gian chờ khi nhân vật chết
    float cool_down_after_die = 3.0f;
    float timer_after_die = 0.0f;
    bool Reset_Game;
    bool is_game_won;

public:
    Stage(PlayerInformation &info);
    virtual ~Stage();
    void Run();
    void Draw();

    void Cool_Down_After_Die(float dt);
    void Player_Update();
    void Non_Player_Update();
    void Check_Player_Vs_Ground();
    void Check_Player_Vs_Block();
    void Check_Player_Vs_Enemy();
    void Check_Enemy_Vs_Ground();
    void Check_Enemy_Vs_Block();
    void Check_Enemy_Vs_Enemy();
    void Check_Item_Vs_Block();
    void Check_Item_Vs_Ground();
    void Check_Block_Vs_Block();
    void Check_FireBall_Vs_World();
    void Clear_Keyboard();
    bool Need_Reset_Game() const;
    void LoadBlockFromFile(const std::string &filename);
    void LoadEnemiesFromFile(const std::string &filename);
    void LoadMapFromFile(const std::string &filename);
};