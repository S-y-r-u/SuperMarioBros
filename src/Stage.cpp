#include "Stage.h"
#include "algorithm"

Stage::Stage(PlayerInformation &info) : information(info)
{
    source = {0, 0, 3424, 240};
    dest = {0, 0, 10272, 720};
    Reset_Game = false;
}

Stage::~Stage()
{

    enemy_map.clear();

    for (Item *item : items)
        delete item;
    items.clear();

    for (Block *block : blocks)
        delete block;
    blocks.clear();

    for (Enemy *enemy : enemies)
        delete enemy;
    enemies.clear();

    for(FireBall *fireball : fireballs)
        delete fireball;
    fireballs.clear();

    if (player)
    {
        delete player;
        player = nullptr;
    }

    Score_Manager &score_manager = Score_Manager::GetInstance();
    score_manager.ClearScores();

    Keyboard.clear();

    // Unload textures if necessary
    UnloadTexture(MapTexture);
}

void Stage::Run()
{
    Player_Update();

    if (!player->Get_isTransforming())
    {
        Non_Player_Update();
    }
    Cool_Down_After_Die(GetFrameTime());
}

void Stage::Cool_Down_After_Die(float dt)
{
    if (!player->Get_isActive() && !Reset_Game)
    {
        timer_after_die += dt;
    }
    if (timer_after_die >= cool_down_after_die)
    {
        Reset_Game = true;
        timer_after_die = 0.0f;
    }
}

void Stage::Player_Update()
{
    if (IsKeyPressed(KEY_A))
        Keyboard.emplace_back(KEY_A);
    if (IsKeyReleased(KEY_A))
        Keyboard.erase(std::remove(Keyboard.begin(), Keyboard.end(), KEY_A), Keyboard.end());
    if (IsKeyPressed(KEY_D))
        Keyboard.emplace_back(KEY_D);
    if (IsKeyReleased(KEY_D))
        Keyboard.erase(std::remove(Keyboard.begin(), Keyboard.end(), KEY_D), Keyboard.end());
    if (IsKeyPressed(KEY_W))
        player->Jump();
    else if (IsKeyReleased(KEY_W))
        player->Cut_Jump();
    if(IsKeyPressed(KEY_SPACE))
        player->Shoot(fireballs);
    if (Keyboard.empty())
        player->StopMoving();
    else if (Keyboard.back() == KEY_A)
        player->MoveLeft();
    else
        player->MoveRight();
    player->updateCoolDown(GetFrameTime());
    player->update(GetFrameTime());
    information.Update(GetFrameTime());
    std::cout << "Player position: " << player->getPosition().x << ", " << player->getPosition().y << std::endl;

    Score_Manager &score_manager = Score_Manager::GetInstance();
    score_manager.Update();

    if (!player->Get_isDead())
    {
        Check_Player_Vs_Ground();
        Check_Player_Vs_Enemy();
        Check_Block_Vs_Block();
        Check_Player_Vs_Block();
    }

    Vector2 top_left = GetScreenToWorld2D({0, 0}, camera);
    Vector2 bottom_right = GetScreenToWorld2D({(float)GetScreenWidth(), (float)GetScreenHeight()}, camera);

    Rectangle screen_rect_world = {
        top_left.x,
        top_left.y,
        bottom_right.x - top_left.x,
        bottom_right.y - top_left.y};
    if (player->getPosition().x <= screen_rect_world.x)
    {
        player->Set_Pos({screen_rect_world.x, player->getPosition().y});
        player->Set_Velocity({0, player->get_Velocity().y});
    }
}

void Stage::Non_Player_Update()
{
    camera.target.x = std::max(camera.target.x, player->getPosition().x - Screen_w / 2.0f);

    Check_Item_Vs_Ground();
    Check_Item_Vs_Block();
    Check_Enemy_Vs_Ground();
    Check_Enemy_Vs_Block();
    Check_Enemy_Vs_Enemy();
    Check_FireBall_Vs_World();

    for (Item *item : items)
    {
        Rectangle player_rec = player->get_draw_rec();
        Rectangle rec_item = item->Get_Draw_Rec();
        if (CheckCollisionRecs(player_rec, rec_item) && !item->Is_Appear_Animation())
        {
            item->Activate_(*player, information);
        }
    }

    Vector2 top_left = GetScreenToWorld2D({0, 0}, camera);
    Vector2 bottom_right = GetScreenToWorld2D({(float)GetScreenWidth(), (float)GetScreenHeight()}, camera);

    Rectangle screen_rect_world = {
        top_left.x,
        top_left.y,
        bottom_right.x - top_left.x,
        bottom_right.y - top_left.y};

    for (size_t i = 0; i < items.size();)
    {
        Rectangle rec_item = items[i]->Get_Draw_Rec();
        if (items[i]->Get_Is_Delete())
        {
            delete items[i];
            items.erase(items.begin() + i);
        }
        else if (rec_item.x + rec_item.width <= screen_rect_world.x)
        {
            // Item is completely off-screen to the left
            delete items[i];
            items.erase(items.begin() + i);
        }
        else
            i++;
    }

    for (size_t i = 0; i < blocks.size();)
    {
        if (blocks[i]->Get_Is_Delete())
        {
            delete blocks[i];
            blocks.erase(blocks.begin() + i);
        }
        else
            i++;
    }

    for (size_t i = 0; i < enemies.size();)
    {
        Rectangle rec_enemy = enemies[i]->Get_Draw_Rec();
        if (rec_enemy.x + rec_enemy.width <= screen_rect_world.x)
        {
            enemy_map.erase(enemies[i]);
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
        }
        if (i < enemies.size() && !enemies[i]->Get_Is_Active())
        {
            enemy_map.erase(enemies[i]);
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
        }
        else
            i++;
    }

    for(size_t i=0; i<fireballs.size();){
        if(!fireballs[i]->getActive()){
            delete fireballs[i];
            fireballs.erase(fireballs.begin()+i);
        }
        else i++;
    }

    for (Item *item : items)
        item->Update_();

    for (Block *block : blocks)
        block->Update_();

    size_t size_before = enemies.size();
    for (size_t i = 0; i < size_before; ++i)
    {
        enemies[i]->Update(GetFrameTime());
    }

    for(FireBall *fireball : fireballs)
        fireball->update(GetFrameTime(), camera);
}

void Stage::Draw()
{
    BeginMode2D(camera);
    player->draw();

    for (Item *item : items)
        item->Draw_();

    for (Block *block : blocks)
        block->Draw_();

    for (Enemy *enemy : enemies)
        enemy->Draw();

    for (FireBall* fireball : fireballs)
        fireball->draw();

    DrawTexturePro(MapTexture, source, dest, {0, 0}, 0, WHITE);
    Score_Manager &score_manager = Score_Manager::GetInstance();
    
    score_manager.Draw();

    EndMode2D();

    information.Draw();
}

void Stage::Check_Player_Vs_Block()
{
    // rectangle của frame trước
    Rectangle preRec = player->Get_Previous_Rec();

    // current Rectangle
    Rectangle currentRec = player->get_draw_rec();
    Vector2 prevPos = player->getPosition();
    Vector2 velocity = player->get_Velocity();
    float deltaTime = GetFrameTime();

    // compute next
    Vector2 sufPos = prevPos;
    sufPos.x += velocity.x * deltaTime;
    velocity.y += player->getGravity() * deltaTime; // Gravity effect
    sufPos.y += velocity.y * deltaTime;
    Rectangle playerRec = {sufPos.x, sufPos.y, currentRec.width, currentRec.height};

    for (Block *block : blocks)
    {
        Rectangle rec_map = block->Get_Draw_Rec();
        if (!CheckCollisionRecs(playerRec, rec_map))
            continue;

        // Tính toán độ sâu va chạm
        float overlapX = std::min(playerRec.x + playerRec.width - rec_map.x,
                                  rec_map.x + rec_map.width - playerRec.x);
        float overlapY = std::min(playerRec.y + playerRec.height - rec_map.y,
                                  rec_map.y + rec_map.height - playerRec.y);

        // Xác định hướng va chạm
        if (overlapX < overlapY && velocity.x != 0)
        {
            // Va chạm ngang
            if (prevPos.x + preRec.width <= rec_map.x)
            {
                if (!block->Surrounded_Block[2])
                {
                    // Va chạm từ bên trái
                    player->Set_Pos({rec_map.x - playerRec.width, player->getPosition().y});
                    player->Set_Velocity({0, player->get_Velocity().y});
                }
            }
            else
            {
                if (!block->Surrounded_Block[3])
                {
                    // Va chạm từ bên phải
                    player->Set_Pos({rec_map.x + rec_map.width, player->getPosition().y});
                    player->Set_Velocity({0, player->get_Velocity().y});
                }
            }
        }
        else
        {
            // Va chạm dọc
            if (prevPos.y + preRec.height < rec_map.y && !block->Surrounded_Block[0] && player->get_Velocity().y >= 0)
            {
                // Va chạm từ trên xuống (đáp xuống mặt đất)
                player->Set_Pos({player->getPosition().x, rec_map.y - playerRec.height});
                player->Set_Velocity({player->get_Velocity().x, 0.f});
                player->Set_isGround(true);
            }
            else if (prevPos.y > rec_map.y + rec_map.height && !block->Surrounded_Block[1] && player->get_Velocity().y < 0)
            {
                // Va chạm từ dưới lên (đụng đầu)
                player->Set_Pos({player->getPosition().x, rec_map.y + rec_map.height});
                player->Set_Velocity({player->get_Velocity().x, 0.f});
                block->On_Hit(items, *player, information);
            }
        }
    }
}

void Stage::Check_Player_Vs_Ground()
{
    // rectangle của frame trước
    Rectangle preRec = player->Get_Previous_Rec();

    // current Rectangle
    Rectangle currentRec = player->get_draw_rec();
    Vector2 prevPos = player->getPosition();
    Vector2 velocity = player->get_Velocity();
    float deltaTime = GetFrameTime();

    // compute next
    Vector2 sufPos = prevPos;
    sufPos.x += velocity.x * deltaTime;
    velocity.y += player->getGravity() * deltaTime; // Gravity effect
    sufPos.y += velocity.y * deltaTime;
    Rectangle playerRec = {sufPos.x, sufPos.y, currentRec.width, currentRec.height};
    for (int i = 0; i < sizeof(Map[0]) / sizeof(Map[0][0]); i++)
    {
        for (int j = 0; j < sizeof(Map) / sizeof(Map[0]); j++)
        {
            int id = Map[j][i];
            if (id == 0)
                continue;

            Rectangle rec_map = {j * 16.0f * scale_screen, i * 16.0f * scale_screen, 16.0f * scale_screen, 16.0f * scale_screen};
            if (!CheckCollisionRecs(playerRec, rec_map))
                continue;

            // Tính toán độ sâu va chạm
            float overlapX = std::min(playerRec.x + playerRec.width - rec_map.x,
                                      rec_map.x + rec_map.width - playerRec.x);
            float overlapY = std::min(playerRec.y + playerRec.height - rec_map.y,
                                      rec_map.y + rec_map.height - playerRec.y);

            // Xác định hướng va chạm
            if (overlapX < overlapY && velocity.x != 0)
            {
                // Va chạm ngang
                if (prevPos.x + preRec.width < rec_map.x)
                {
                    // Va chạm từ bên trái
                    if (Map[j - 1][i] == 0)
                    {
                        player->Set_Pos({rec_map.x - currentRec.width, player->getPosition().y});
                        player->Set_Velocity({0, player->get_Velocity().y});
                    }
                }
                else
                {
                    // Va chạm từ bên phải
                    if (Map[j + 1][i] == 0)
                    {
                        player->Set_Pos({rec_map.x + rec_map.width, player->getPosition().y});
                        player->Set_Velocity({0, player->get_Velocity().y});
                    }
                }
            }
            else
            {
                // Va chạm dọc
                if (prevPos.y + preRec.height < rec_map.y && Map[j][i - 1] == 0 && player->get_Velocity().y >= 0)
                {
                    // Va chạm từ trên xuống (đáp xuống mặt đất)
                    player->Set_Pos({player->getPosition().x, rec_map.y - currentRec.height});
                    player->Set_Velocity({player->get_Velocity().x, -500.0f * deltaTime});
                    player->Set_isGround(true);
                }
                else if (prevPos.y > rec_map.y + rec_map.height && Map[j][i + 1] == 0 && player->get_Velocity().y < 0)
                {
                    // Va chạm từ dưới lên (đụng đầu)
                    player->Set_Pos({player->getPosition().x, rec_map.y + rec_map.height});
                    player->Set_Velocity({player->get_Velocity().x, 0.f});
                }
            }
        }
    }
}

void Stage::Check_Player_Vs_Enemy()
{
    Rectangle playerRec = player->get_draw_rec();

    for (Enemy *enemy : enemies)
    {
        if (!enemy || !enemy->Get_Is_Active() || enemy->Get_Is_Dead())
            continue;

        Rectangle enemyRec = enemy->Get_Draw_Rec();

        if (!CheckCollisionRecs(playerRec, enemyRec))
            continue;

        // Tính toán độ sâu va chạm
        float overlapX = std::min(playerRec.x + playerRec.width - enemyRec.x,
                                  enemyRec.x + enemyRec.width - playerRec.x);
        float overlapY = std::min(playerRec.y + playerRec.height - enemyRec.y,
                                  enemyRec.y + enemyRec.height - playerRec.y);

        // Xác định hướng va chạm
        if (overlapX < overlapY)
        {

            // Va chạm ngang (trái/phải)
            if (playerRec.x + playerRec.width / 2 < enemyRec.x + enemyRec.width / 2)
            {
                // Player ở bên trái enemy
                // Xử lý va chạm từ bên trái
                if (enemy->Can_Be_Kicked())
                {
                    enemy->Notify_Be_Kicked(1, information);
                    SoundManager::GetInstance().PlaySoundEffect("kick");
                }
                else
                {
                    player->Die();
                }
            }
            else
            {
                // Player ở bên phải enemy
                // Xử lý va chạm từ bên phải
                if (enemy->Can_Be_Kicked())
                {
                    SoundManager::GetInstance().PlaySoundEffect("kick");
                    enemy->Notify_Be_Kicked(-1, information);
                }
                else
                {
                    player->Die();
                }
            }
        }
        else
        {
            // Va chạm dọc (trên/dưới)
            if (playerRec.y + playerRec.height / 2 < enemyRec.y + enemyRec.height / 2)
            {
                if (enemy->Can_Be_Kicked())
                {
                    player->Set_Velocity({player->get_Velocity().x, fmax(-player->get_Velocity().y, -300.0f)});
                    player->Set_Pos({player->getPosition().x, player->getPosition().y - 30.0f});
                    SoundManager::GetInstance().PlaySoundEffect("kick");
                    enemy->Notify_Be_Kicked(-1, information);
                }
                // Player ở phía trên enemy - nhảy lên đầu enemy
                else if (enemy->Can_Be_Stomped())
                {
                    player->Set_Velocity({player->get_Velocity().x, fmax(-player->get_Velocity().y, -300.0f)});
                    enemy->Notify_Be_Stomped(information);
                    SoundManager::GetInstance().PlaySoundEffect("stomp");
                }
                else
                {
                    player->Die();
                }
            }
            else
            {
                player->Die();
                // Player ở phía dưới enemy
            }
        }
    }
}

void Stage::Check_Item_Vs_Ground()
{
    for (Item *item : items)
    {
        bool avoid_branch = 0;
        if (item->Is_Appear_Animation())
            return;

        Mush_Room *mush_room = dynamic_cast<Mush_Room *>(item);
        Star *star = dynamic_cast<Star *>(item);
        if (!mush_room && !star)
            return;

        Rectangle rec_item = item->Get_Draw_Rec();
        Vector2 prev = item->Get_Previous_Frame_Pos();
        float w = rec_item.width;
        float h = rec_item.height;

        item->Notify_Fall();

        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 214; j++)
            {
                int id = Map[j][i];
                if (id == 0)
                    continue;

                Rectangle rec_map = {j * 16.0f * scale_screen, i * 16.0f * scale_screen, 16.0f * scale_screen, 16.0f * scale_screen};

                if (!CheckCollisionRecs(rec_item, rec_map))
                    continue;

                // Va chạm từ trên xuống
                if (prev.y <= rec_map.y &&
                    i > 0 &&
                    Map[j][i - 1] == 0)
                {
                    item->Set_Pos({item->Get_Pos().x, rec_map.y});
                    item->Notify_On_Ground();
                }
                // Va chạm từ bên trái
                else if (prev.x + w / 2.0f <= rec_map.x && !avoid_branch)
                {
                    item->Set_Pos({rec_map.x - w / 2.0f, item->Get_Pos().y});
                    item->Notify_Change_Direct();
                    avoid_branch = 1;
                }
                // Va chạm từ bên phải
                else if (prev.x - w / 2.0f >= rec_map.x + rec_map.width && !avoid_branch)
                {
                    item->Set_Pos({rec_map.x + rec_map.width + w / 2.0f, item->Get_Pos().y});
                    item->Notify_Change_Direct();
                    avoid_branch = 1;
                }
            }
        }
    }
}

void Stage::Check_Item_Vs_Block()
{
    for (Item *item : items)
    {
        bool avoid_branch = 0;
        if (item->Is_Appear_Animation())
            continue;
        if (!item->Can_Move())
            continue;

        Mush_Room *mush_room = dynamic_cast<Mush_Room *>(item);
        Star *star = dynamic_cast<Star *>(item);

        Rectangle rec_item = item->Get_Draw_Rec();
        Vector2 prev = item->Get_Previous_Frame_Pos();
        float w = rec_item.width;
        float h = rec_item.height;
        for (Block *block : blocks)
        {
            Rectangle rec_block = block->Get_Draw_Rec();

            if (!CheckCollisionRecs(rec_item, rec_block))
                continue;

            if (!block->Get_Elapse())
            {
                if (prev.y <= rec_block.y)
                {
                    item->Set_Pos({item->Get_Pos().x, rec_block.y});
                    item->Notify_On_Ground();
                }

                else if (prev.x + w / 2.0f <= rec_block.x && !avoid_branch)
                {
                    item->Set_Pos({rec_block.x - w / 2.0f, item->Get_Pos().y});
                    item->Notify_Change_Direct();
                    avoid_branch = 1;
                }

                else if (prev.x - w / 2.0f >= rec_block.x + rec_block.width && !avoid_branch)
                {
                    item->Set_Pos({rec_block.x + rec_block.width + w / 2.0f, item->Get_Pos().y});
                    item->Notify_Change_Direct();
                    avoid_branch = 1;
                }
            }
            else
            {
                if (mush_room)
                {

                    if ((mush_room->Get_Direct() && prev.x + w / 2.0f > rec_block.x) || (!mush_room->Get_Direct() && prev.x - w / 2.0f < rec_block.x + rec_block.width))
                    {
                        mush_room->Set_Pos({mush_room->Get_Pos().x, rec_block.y});
                        mush_room->Notify_Jump();

                        if ((mush_room->Get_Direct() && rec_item.x < rec_block.x + rec_block.width / 2.0f) ||
                            (!mush_room->Get_Direct() && rec_item.x >= rec_block.x + rec_block.width / 2.0f))
                        {
                            mush_room->Notify_Change_Direct();
                        }
                    }
                }
                if (star)
                {
                    if ((star->Get_Direct() && prev.x + w / 2.0f > rec_block.x) || (!star->Get_Direct() && prev.x - w / 2.0f < rec_block.x + rec_block.width))
                    {
                        star->Set_Pos({star->Get_Pos().x, rec_block.y});
                        star->Notify_On_Ground();
                    }
                }
            }
        }
    }
}

void Stage::Check_Enemy_Vs_Block()
{
    for (Enemy *enemy : enemies)
    {
        if (!enemy->Get_Is_Active() || enemy->Get_Is_Dead() || !enemy->Need_Check_Ground_Block())
            continue;

        Rectangle rec_enemy = enemy->Get_Draw_Rec();
        Vector2 prev = enemy->Get_Previous_Pos();
        float w = rec_enemy.width;
        float h = rec_enemy.height;

        bool avoid_branch = false;

        for (Block *block : blocks)
        {
            Rectangle rec_block = block->Get_Draw_Rec();

            if (!CheckCollisionRecs(rec_enemy, rec_block))
                continue;

            if (prev.y > rec_block.y + rec_block.height && !block->Surrounded_Block[1] && enemy->Get_Velocity().y < 0)
            {
                // Va chạm từ dưới lên (đụng đầu)
                enemy->Set_Pos({enemy->Get_Pos().x, rec_block.y + rec_block.height + h});
                enemy->Set_Velocity({enemy->Get_Velocity().x, 0.f});
            }
            else if (!block->Get_Elapse()) // Nếu block đứng yên
            {
                if (prev.y <= rec_block.y)
                {
                    enemy->Set_Pos({enemy->Get_Pos().x, rec_block.y});
                    enemy->Notify_On_Ground();
                }
                else if (prev.x + w / 2.0f <= rec_block.x && !avoid_branch)
                {
                    enemy->Set_Pos({rec_block.x - w / 2.0f, enemy->Get_Pos().y});
                    enemy->Notify_Change_Direct();
                    avoid_branch = true;
                }
                else if (prev.x - w / 2.0f >= rec_block.x + rec_block.width && !avoid_branch)
                {
                    enemy->Set_Pos({rec_block.x + rec_block.width + w / 2.0f, enemy->Get_Pos().y});
                    enemy->Notify_Change_Direct();
                    avoid_branch = true;
                }
            }
            else // Nếu block đang "nảy" lên
            {
                if (enemy->Can_Jump())
                {
                    if ((enemy->Get_Velocity().x > 0 && prev.x + w / 2.0f > rec_block.x) || (enemy->Get_Velocity().x < 0 && prev.x - w / 2.0f < rec_block.x + rec_block.width))
                    {
                        enemy->Set_Pos({enemy->Get_Pos().x, rec_block.y});
                        enemy->Notify_Jump();

                        if ((enemy->Get_Velocity().x > 0 && rec_enemy.x < rec_block.x + rec_block.width / 2.0f) ||
                            (enemy->Get_Velocity().x < 0 && rec_enemy.x >= rec_block.x + rec_block.width / 2.0f))
                        {
                            enemy->Notify_Change_Direct();
                        }
                    }
                }
                else
                {
                    enemy->Notify_Be_Fired_Or_Hit(information);
                    break;
                }
            }
        }
    }
}

void Stage::Check_Enemy_Vs_Ground()
{
    for (Enemy *enemy : enemies)
    {
        if (!enemy || !enemy->Get_Is_Active() || enemy->Get_Is_Dead() || !enemy->Need_Check_Ground_Block())
            continue;

        Rectangle rec_enemy = enemy->Get_Draw_Rec();
        Vector2 prev = enemy->Get_Previous_Pos();
        float w = rec_enemy.width;
        float h = rec_enemy.height;

        enemy->Notify_Fall(GetFrameTime());

        bool avoid_branch = false;

        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 214; j++)
            {
                int id = Map[j][i];
                if (id == 0)
                    continue;

                Rectangle rec_map = {j * 16.0f * scale_screen, i * 16.0f * scale_screen, 16.0f * scale_screen, 16.0f * scale_screen};

                if (!CheckCollisionRecs(rec_enemy, rec_map))
                    continue;

                // Va chạm từ trên xuống
                if (prev.y <= rec_map.y &&
                    i > 0 &&
                    Map[j][i - 1] == 0)
                {
                    enemy->Set_Pos({enemy->Get_Pos().x, rec_map.y});
                    enemy->Notify_On_Ground();
                }
                // Va chạm từ bên trái
                else if (prev.x + w / 2.0f <= rec_map.x && !avoid_branch)
                {
                    enemy->Set_Pos({rec_map.x - w / 2.0f, enemy->Get_Pos().y});
                    enemy->Notify_Change_Direct();
                    avoid_branch = true;
                }
                // Va chạm từ bên phải
                else if (prev.x - w / 2.0f >= rec_map.x + rec_map.width && !avoid_branch)
                {
                    enemy->Set_Pos({rec_map.x + rec_map.width + w / 2.0f, enemy->Get_Pos().y});
                    enemy->Notify_Change_Direct();
                    avoid_branch = true;
                }
            }
        }
    }
}

void Stage::Check_Enemy_Vs_Enemy()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        Enemy *enemy1 = enemies[i];
        if (!enemy1 || !enemy1->Get_Is_Active() || enemy1->Get_Is_Dead() || !enemy1->Need_Check_Collision_With_Other_Enemy())
            continue;
        Rectangle rec_enemy1 = enemy1->Get_Draw_Rec();

        for (int j = i + 1; j < enemies.size(); j++)
        {
            Enemy *enemy2 = enemies[j];
            if (enemy1 == enemy2 || !enemy2->Get_Is_Active() || enemy2->Get_Is_Dead() || !enemy2->Need_Check_Collision_With_Other_Enemy())
                continue;
            Rectangle rec_enemy2 = enemy2->Get_Draw_Rec();

            if (!CheckCollisionRecs(rec_enemy1, rec_enemy2))
            {
                enemy_map[enemy1].erase(std::remove(enemy_map[enemy1].begin(), enemy_map[enemy1].end(), enemy2), enemy_map[enemy1].end());
                enemy_map[enemy2].erase(std::remove(enemy_map[enemy2].begin(), enemy_map[enemy2].end(), enemy1), enemy_map[enemy2].end());
                continue;
            }
            auto &v1 = enemy_map[enemy1];
            if (std::find(v1.begin(), v1.end(), enemy2) != v1.end())
                continue;

            auto &v2 = enemy_map[enemy2];
            if (std::find(v2.begin(), v2.end(), enemy1) != v2.end())
                continue;
            if (enemy1->Kill_Other_Enemies())
            {
                enemy2->Notify_Be_Fired_Or_Hit(information);
            }
            else if (enemy2->Kill_Other_Enemies())
            {
                enemy1->Notify_Be_Fired_Or_Hit(information);
            }

            else
            {
                Vector2 velo1 = enemy1->Get_Velocity();
                Vector2 velo2 = enemy2->Get_Velocity();
                Vector2 pos1 = enemy1->Get_Pos();
                Vector2 pos2 = enemy2->Get_Pos();
                enemy1->Collision_With_Other_Enemy(velo2, pos2);
                enemy2->Collision_With_Other_Enemy(velo1, pos1);
                enemy_map[enemy1].push_back(enemy2);
                enemy_map[enemy2].push_back(enemy1);
                break;
            }
        }
    }
}

void Stage::Check_Block_Vs_Block()
{
    const float Tile_Size = 16.0f * 3.0f; // scale_screen = 3.0f

    for (Block *mainblock : blocks)
    {
        // Reset surrounded blocks state
        mainblock->Surrounded_Block = {false, false, false, false}; // top, bottom, left, right

        Vector2 mainPos = mainblock->Get_Pos();

        for (Block *block : blocks)
        {
            if (mainblock == block)
                continue; // Skip checking with itself

            Vector2 blockPos = block->Get_Pos();

            // Calculate position differences
            float dx = blockPos.x - mainPos.x;
            float dy = blockPos.y - mainPos.y;

            // Check if blocks are adjacent (within tile size tolerance)
            const float tolerance = Tile_Size * 0.1f; // Small tolerance for floating point comparison

            // Check top (block above mainblock)
            if (abs(dx) <= tolerance && dy < 0 && abs(dy) <= Tile_Size + tolerance)
            {
                mainblock->Surrounded_Block[0] = true; // top
            }
            // Check bottom (block below mainblock)
            else if (abs(dx) <= tolerance && dy > 0 && abs(dy) <= Tile_Size + tolerance)
            {
                mainblock->Surrounded_Block[1] = true; // bottom
            }
            // Check left (block to the left of mainblock)
            else if (abs(dy) <= tolerance && dx < 0 && abs(dx) <= Tile_Size + tolerance)
            {
                mainblock->Surrounded_Block[2] = true; // left
            }
            // Check right (block to the right of mainblock)
            else if (abs(dy) <= tolerance && dx > 0 && abs(dx) <= Tile_Size + tolerance)
            {
                mainblock->Surrounded_Block[3] = true; // right
            }
        }
    }
}

void Stage::Check_FireBall_Vs_World()
{
    for (auto* fireball : fireballs) 
    {
        if (!fireball->getActive()) continue;
        Rectangle rec_fireball = fireball->get_draw_rec();

        bool rebound = 0;

        for (Block* block : blocks) 
        {
            Rectangle rec_block = block->Get_Draw_Rec();
            if (CheckCollisionRecs(rec_fireball, rec_block))
            {
                if (fireball->getVelocity().y > 0 && rec_fireball.y + rec_fireball.height - 
                (fireball->getVelocity().y * GetFrameTime()) <= rec_block.y) 
                {
                    fireball->setPosition({rec_fireball.x, rec_block.y - rec_fireball.height});
                    fireball->reboundOnSurface(); 
                    rebound = 1;
                    goto end_collision_check_for_this_fireball;
                } 
                else
                {
                    fireball->explode();
                    goto next_fireball; 
                }
            }
        }

        for(int i=0; i<15; i++) for(int j=0; j<214; j++)
        {
            if(Map[j][i] == 0)  continue;
            Rectangle rec_map = {j * 16.0f * scale_screen, i * 16.0f * scale_screen, 16.0f * scale_screen, 16.0f * scale_screen};
            if(CheckCollisionRecs(rec_fireball, rec_map))
            {
                if (fireball->getVelocity().y > 0 && rec_fireball.y + rec_fireball.height - (fireball->getVelocity().y * GetFrameTime()) <= rec_map.y){
                    fireball->setPosition({rec_fireball.x, rec_map.y - rec_fireball.height});
                    fireball->reboundOnSurface();
                    rebound = 1;
                    goto end_collision_check_for_this_fireball;
                } 
                else
                {
                    fireball->explode();
                    goto next_fireball;
                }
            }
        }

        end_collision_check_for_this_fireball:;
        if (rebound)
        {
            fireball->notifyOnGround();
        }

        for (Enemy* enemy : enemies) 
        {
            if (!enemy->Get_Is_Active() || enemy->Get_Is_Dead()) continue;
            if (CheckCollisionRecs(rec_fireball, enemy->Get_Draw_Rec())) 
            {
                fireball->explode();
                enemy->Notify_Be_Fired_Or_Hit(information);
                goto next_fireball;
            }
        }

        next_fireball:;
    }
}

void Stage::Clear_Keyboard()
{
    Keyboard.clear();
}

bool Stage::Need_Reset_Game() const
{
    return Reset_Game;
}


void Stage::LoadEnemiesFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        // Nếu không mở được file, in ra lỗi
        return;
    }
    
    int enemy_type, x, y;
    while (file >> enemy_type >> x >> y)
    {
        Vector2 position = {(float)x, (float)y};
        
        // Chuyển đổi int thành EnemyType
        EnemyType type;
        switch (enemy_type)
        {
        case 0:
            type = EnemyType::Goomba;
            break;
        case 1:
            type = EnemyType::KoopaTroopaWalking;
            break;
        case 2:
            type = EnemyType::KoopaTroopaFlying;
            break;
        case 3:
            type = EnemyType::Latiku;
            break;
        case 4:
            type = EnemyType::PiranhaPlant;
            break;
        case 5:
            type = EnemyType::BomberBill;
            break;
        default:
            continue; // Bỏ qua nếu type không hợp lệ
        }
        
        // Spawn enemy
        Spawn_Enemy::SpawnEnemies(type, position , player , enemy_map, enemies, camera);
    }
    
    file.close();
}
