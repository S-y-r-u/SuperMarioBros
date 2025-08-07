#include "Enemy/Spawn_Enemy.h"

void Spawn_Enemy::Spawn_Goomba(std::vector<Enemy *> &enemies, Vector2 pos, std::unordered_map<Enemy *, std::vector<Enemy *>> &enemy_map)
{
    Goomba *goomba = new Goomba(pos);
    enemies.push_back(goomba);
    enemy_map[goomba] = std::vector<Enemy *>();
}

void Spawn_Enemy::Spawn_KoopaTroopa(std::vector<Enemy *> &enemies, Vector2 pos, std::unordered_map<Enemy *, std::vector<Enemy *>> &enemy_map, bool is_flying)
{
    KoopaTroopa *koopa = new KoopaTroopa(pos, is_flying);
    enemies.push_back(koopa);
    enemy_map[koopa] = std::vector<Enemy *>();
}

void Spawn_Enemy::Spawn_Latiku(std::vector<Enemy *> &enemies, Vector2 pos, Player *player, std::unordered_map<Enemy *, std::vector<Enemy *>> &enemy_map, Camera2D& camera)
{
    Latiku *latiku = new Latiku(pos, player, &enemies, enemy_map, camera);
    enemies.push_back(latiku);
}

void Spawn_Enemy::Spawn_PiranhaPlant(std::vector<Enemy *> &enemies, Vector2 pos, Player *player, std::unordered_map<Enemy *, std::vector<Enemy *>> &enemy_map)
{
    PiranhaPlant *piranha = new PiranhaPlant(pos, player);
    enemies.push_back(piranha);
}

void Spawn_Enemy::Spawn_BomberBill(std::vector<Enemy *> &enemies, Vector2 pos, std::unordered_map<Enemy *, std::vector<Enemy *>> &enemy_map)
{
    BomberBill *bomber = new BomberBill(pos);
    enemies.push_back(bomber);
    enemy_map[bomber] = std::vector<Enemy *>();
}


