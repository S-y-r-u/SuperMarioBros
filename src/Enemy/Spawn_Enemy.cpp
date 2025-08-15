#include "Enemy/Spawn_Enemy.h"

void Spawn_Enemy::Spawn_Goomba(Vector2 pos, std::unordered_map<Enemy *, std::vector<Enemy *>>& enemy_map, std::vector<Enemy *>& enemies )
{
    Goomba *goomba = new Goomba(pos);
    enemies.push_back(goomba);
    enemy_map[goomba] = std::vector<Enemy *>();
}

void Spawn_Enemy::Spawn_KoopaTroopa(Vector2 pos, std::unordered_map<Enemy *, std::vector<Enemy *>>& enemy_map, std::vector<Enemy *>& enemies ,bool is_flying)
{
    KoopaTroopa *koopa = new KoopaTroopa(pos, is_flying);
    enemies.push_back(koopa);
    enemy_map[koopa] = std::vector<Enemy *>();
}

void Spawn_Enemy::Spawn_Latiku(Vector2 pos, std::unordered_map<Enemy *, std::vector<Enemy *>>& enemy_map, std::vector<Enemy *>& enemies , Player* player, Camera2D& camera)
{
    Latiku *latiku = new Latiku(pos, player, &enemies, enemy_map, camera);
    enemies.push_back(latiku);
}

void Spawn_Enemy::Spawn_PiranhaPlant(Vector2 pos,  std::vector<Enemy *>& enemies , Player* player)
{
    PiranhaPlant *piranha = new PiranhaPlant(pos, player);
    enemies.push_back(piranha);
}

void Spawn_Enemy::Spawn_BomberBill(Vector2 pos, std::unordered_map<Enemy *, std::vector<Enemy *>>& enemy_map, std::vector<Enemy *>& enemies )
{
    BomberBill *bomber = new BomberBill(pos);
    enemies.push_back(bomber);
    enemy_map[bomber] = std::vector<Enemy *>();
}

void Spawn_Enemy::Spawn_Bowser(Vector2 pos, std::unordered_map<Enemy *, std::vector<Enemy *>>& enemy_map, std::vector<Enemy *>& enemies, Player* player, Camera2D& camera){
    Bowser *bowser = new Bowser(pos, player,enemies);
    enemies.push_back(bowser);
    enemy_map[bowser] = std::vector<Enemy *>();
}

void Spawn_Enemy::Spawn_LaserFire(Vector2 pos,  std::vector<Enemy *>& enemies ,Player* player)
{
    LaserFire *laser = new LaserFire(pos, player->getPosition());
    enemies.push_back(laser);
}

void Spawn_Enemy::Spawn_Podoboo(Vector2 pos,  std::vector<Enemy *>& enemies )
{
    Podoboo *podoboo= new Podoboo(pos);
    enemies.push_back(podoboo);
}

void Spawn_Enemy::SpawnEnemies(EnemyType type, Vector2 spawn_position , Player* player , std::unordered_map<Enemy *, std::vector<Enemy *>>& enemy_map, std::vector<Enemy *>& enemies, Camera2D& camera)
{   
    std::cout << "[Spawn_Enemy] Spawning enemy type: " << static_cast<int>(type) << " at position: (" << spawn_position.x << ", " << spawn_position.y << ")\n";
    if (type == EnemyType::Goomba)
    {
        Spawn_Goomba(spawn_position, enemy_map, enemies);
    }
    else if (type == EnemyType::KoopaTroopaWalking)
    {
        Spawn_KoopaTroopa(spawn_position, enemy_map, enemies, false);
    }
    else if (type == EnemyType::KoopaTroopaFlying)
    {
        Spawn_KoopaTroopa(spawn_position, enemy_map, enemies, true);
    }
    else if (type == EnemyType::Latiku)
    {
        Spawn_Latiku(spawn_position, enemy_map, enemies, player, camera);
    }
    else if (type == EnemyType::PiranhaPlant)
    {
        Spawn_PiranhaPlant(spawn_position, enemies, player);
    }
    else if (type == EnemyType::BomberBill)
    {
        Spawn_BomberBill(spawn_position, enemy_map, enemies);
    }
    else if (type == EnemyType::Bowser)
    {
        Spawn_Bowser(spawn_position, enemy_map, enemies, player, camera);
    }
    else if (type == EnemyType::LaserFire)
    {
        Spawn_LaserFire(spawn_position, enemies, player);
    }
    else if (type == EnemyType::Podoboo)
    {
        Spawn_Podoboo(spawn_position, enemies);
    }
}