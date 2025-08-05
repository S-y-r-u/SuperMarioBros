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

class Spawn_Enemy
{
public:
    static void Spawn_Goomba(std::vector<Enemy *> &enemies, Vector2 pos, std::unordered_map<Enemy *, std::vector<Enemy *>> &enemy_map);
    static void Spawn_KoopaTroopa(std::vector<Enemy *> &enemies, Vector2 pos, std::unordered_map<Enemy *, std::vector<Enemy *>> &enemy_map, bool is_flying = false);
    static void Spawn_Latiku(std::vector<Enemy *> &enemies, Vector2 pos, Player *player, std::unordered_map<Enemy *, std::vector<Enemy *>> &enemy_map);
    static void Spawn_PiranhaPlant(std::vector<Enemy *> &enemies, Vector2 pos, Player *player, std::unordered_map<Enemy *, std::vector<Enemy *>> &enemy_map);
    static void Spawn_BomberBill(std::vector<Enemy *> &enemies, Vector2 pos, std::unordered_map<Enemy *, std::vector<Enemy *>> &enemy_map);
};
