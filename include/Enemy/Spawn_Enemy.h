#pragma once
#include "Enemy.h"
#include "Enemy/Latiku.h"
#include "Enemy/Goomba.h"
#include "Enemy/KoopaTroopa.h"
#include "Enemy/PiranhaPlant.h"
#include "Enemy/BomberBill.h"
#include "Enemy/Spiny.h"
#include "Player.h"
#include <string>
#include <unordered_map>
#include "Constants.h"


class Spawn_Enemy
{
private:
    static void Spawn_Goomba(Vector2 pos , std::unordered_map<Enemy *, std::vector<Enemy *>>& enemy_map, std::vector<Enemy *>& enemies);
    static void Spawn_KoopaTroopa(Vector2 pos, std::unordered_map<Enemy *, std::vector<Enemy *>>& enemy_map, std::vector<Enemy *>& enemies ,bool is_flying = false);
    static void Spawn_Latiku(Vector2 pos, std::unordered_map<Enemy *, std::vector<Enemy *>>& enemy_map, std::vector<Enemy *>& enemies , Player* player, Camera2D& camera);
    static void Spawn_PiranhaPlant(Vector2 pos, std::vector<Enemy *>& enemies, Player* player);
    static void Spawn_BomberBill(Vector2 pos, std::unordered_map<Enemy *, std::vector<Enemy *>>& enemy_map, std::vector<Enemy *>& enemies);

public:
    static void SpawnEnemies(EnemyType type, Vector2 spawn_position , Player* player , std::unordered_map<Enemy *, std::vector<Enemy *>>& enemy_map, std::vector<Enemy *>& enemies , Camera2D& camera);
};