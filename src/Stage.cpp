#include "Stage.h"
#include "algorithm"
#include "Enemy/KoopaTroopaState.h"

Stage::Stage(PlayerInformation &info)
    : information(info),
      Reset_Game(false),
      Is_Game_Won(false) {}

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

    for (FireBall *fireball : fireballs)
        delete fireball;
    fireballs.clear();

    if (player)
    {
        delete player;
        player = nullptr;
    }

    delete flag_pole;
    delete flag_castle;
    delete win_animation;

    Score_Manager &score_manager = Score_Manager::GetInstance();
    score_manager.ClearScores();

    Keyboard.clear();

    // Unload textures if necessary
    UnloadTexture(MapTexture);
}

void Stage::Run()
{   
    std::cerr << "1" << std::endl;
    if (!Is_Game_Won)
    {
        std::cerr << "2" << std::endl;
        Is_Game_Won = win_animation->Check_Win_Animation();
        std::cerr << "3" << std::endl;
        if (Is_Game_Won)
        {
            std::cerr << "4" << std::endl;
            Keyboard.clear();
            std::cerr << "5" << std::endl;
        }
    }
    else
    {
        std::cerr << "6" << std::endl;
        win_animation->Update(GetFrameTime());
        std::cerr << "7" << std::endl;
    }
    std::cerr << "8" << std::endl;

    Player_Update();
    if (!player->Get_isTransforming())
    {
        Non_Player_Update();
    }

    if (!player->Get_isActive() && !Reset_Game)
        Cool_Down_After_Die(GetFrameTime());
    if (win_animation->End_Animation())
        Cool_Down_After_Win(GetFrameTime());
}

void Stage::Cool_Down_After_Die(float dt)
{
    timer_ += dt;
    if (timer_ >= cool_down_after_die)
    {
        Reset_Game = true;
        timer_ = 0.0f;
    }
}

void Stage::Cool_Down_After_Win(float dt)
{
    timer_ += dt;
}

void Stage::Player_Update()
{
    if (!Is_Game_Won || player->Get_isDead())
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
        if (IsKeyPressed(KEY_SPACE))
            player->Shoot(fireballs);
        if (Keyboard.empty())
            player->StopMoving();
        else if (Keyboard.back() == KEY_A)
            player->MoveLeft();
        else
            player->MoveRight();
    }

    player->updateCoolDown(GetFrameTime());
    player->update(GetFrameTime());
    information.Update(GetFrameTime());

    Score_Manager &score_manager = Score_Manager::GetInstance();
    score_manager.Update();

    if (!player->Get_isDead())
    {
        player->Set_isGround(false);
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
    if (player->getPosition().x - player->get_draw_rec().width / 2.0f <= screen_rect_world.x)
    {
        player->Set_Pos({screen_rect_world.x + player->get_draw_rec().width / 2.0f, player->getPosition().y});
        player->Set_Velocity({0, player->get_Velocity().y});
    }
}

void Stage::Non_Player_Update()
{
    camera.target.x = std::max(camera.target.x, player->getPosition().x - Screen_w / 2.0f);
    if (camera.target.x >= MapTexture.width * scale_screen - Screen_w)
        camera.target.x = MapTexture.width * scale_screen - Screen_w;

    flag_pole->Update(GetFrameTime());
    flag_castle->Update(GetFrameTime());

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
        if (!enemies[i]->Get_First_Appear() && rec_enemy.x <= screen_rect_world.x + screen_rect_world.width)
            enemies[i]->Set_First_Appear(true);
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

    for (size_t i = 0; i < fireballs.size();)
    {
        if (!fireballs[i]->getActive())
        {
            delete fireballs[i];
            fireballs.erase(fireballs.begin() + i);
        }
        else
            i++;
    }

    for (Item *item : items)
        item->Update_();

    for (Block *block : blocks)
        block->Update_();

    size_t size_before = enemies.size();
    for (size_t i = 0; i < size_before; ++i)
    {
        if (enemies[i]->Get_First_Appear())
            enemies[i]->Update(GetFrameTime());
    }

    for (FireBall *fireball : fireballs)
        fireball->update(GetFrameTime(), camera);
}

void Stage::Draw()
{
    BeginMode2D(camera);

    DrawLayer();

    for (Enemy *enemy : enemies)
    {
        PiranhaPlant *piranha = dynamic_cast<PiranhaPlant *>(enemy);
        if (piranha && enemy->Get_First_Appear())
        {
            piranha->Draw();
        }
    }
    
    flag_pole->Draw();
    flag_castle->Draw();

    DrawTexturePro(MapTexture, source, dest, {0, 0}, 0, WHITE);

    for (Enemy *enemy : enemies)
    {
        if (PiranhaPlant *piranha = dynamic_cast<PiranhaPlant *>(enemy))
            continue;
        if (enemy->Get_First_Appear())
            enemy->Draw();
    }

    for (Item *item : items)
    {
        if (!item->Get_Is_Delete())
            item->Draw_();
    }

    for (Block *block : blocks)
    {
        if (!block->Get_Is_Delete())
            block->Draw_();
    }

    for (FireBall *fireball : fireballs)
        fireball->draw();

    Score_Manager &score_manager = Score_Manager::GetInstance();

    score_manager.Draw();

    if (!win_animation->Player_Disappear())
        player->draw();

    EndMode2D();

    information.Draw();
}

void Stage::Check_Player_Vs_Block()
{
    // Lấy pos center-bottom ở frame trước và hiện tại
    Vector2 currCenterBottom = player->getPosition();
    Vector2 velocity = player->get_Velocity();

    // Lấy kích thước player
    Rectangle currRec = player->get_draw_rec();
    float pw = currRec.width;
    float ph = currRec.height;

    // Rectangle hiện tại
    Rectangle currRect = {
        currCenterBottom.x - pw / 2.0f,
        currCenterBottom.y - ph,
        pw,
        ph};

    for (Block *block : blocks)
    {
        if (block->Kill_Player(*player))
        {
            player->Die();
            return;
        }
        Rectangle rec_map = block->Get_Draw_Rec();
        if (!CheckCollisionRecs(currRect, rec_map))
            continue;

        // Tính overlap
        float overlapX = std::min(currRect.x + currRect.width - rec_map.x,
                                  rec_map.x + rec_map.width - currRect.x);
        float overlapY = std::min(currRect.y + currRect.height - rec_map.y,
                                  rec_map.y + rec_map.height - currRect.y);

        if (overlapX < overlapY && velocity.x != 0)
        {
            // Va chạm ngang
            if (currRec.x < rec_map.x)
            {
                if (!block->Surrounded_Block[2])
                {
                    // Từ trái sang
                    player->Set_Pos({rec_map.x - pw / 2.0f - 0.1f, player->getPosition().y});
                    player->Set_Velocity({0, player->get_Velocity().y});
                }
            }
            else
            {
                if (!block->Surrounded_Block[3])
                {
                    // Từ phải sang
                    player->Set_Pos({rec_map.x + rec_map.width + pw / 2.0f + 0.1f, player->getPosition().y});
                    player->Set_Velocity({0, player->get_Velocity().y});
                }
            }
        }
        else
        {
            // Va chạm dọc
            if (currRec.y <= rec_map.y && !block->Surrounded_Block[0] && velocity.y >= 0)
            {
                // Từ trên xuống
                player->Set_Pos({player->getPosition().x, rec_map.y});
                player->Set_Velocity({player->get_Velocity().x, 0.f});
                player->Set_isGround(true);
            }
            else if (currRec.y + currRec.height > rec_map.y + rec_map.height && !block->Surrounded_Block[1] && velocity.y < 0)
            {
                // Từ dưới lên
                player->Set_Pos({player->getPosition().x, rec_map.y + rec_map.height + ph});
                player->Set_Velocity({player->get_Velocity().x, 0.f});
                if (player->getPosition().x > rec_map.x + rec_map.width &&
                    !block->Surrounded_Block[3])
                {
                    block->On_Hit(items, *player, information);
                }
                else if (player->getPosition().x < rec_map.x &&
                         !block->Surrounded_Block[2])
                {
                    block->On_Hit(items, *player, information);
                }
                else if (player->getPosition().x <= rec_map.x + rec_map.width && player->getPosition().x >= rec_map.x)
                {
                    block->On_Hit(items, *player, information);
                }
            }
        }
    }
}

void Stage::Check_Player_Vs_Ground()
{
    // Vị trí center-bottom của frame trước và hiện tại
    Vector2 currCenterBottom = player->getPosition();
    Vector2 velocity = player->get_Velocity();

    // Lấy kích thước player
    Rectangle currDrawRec = player->get_draw_rec();
    float pw = currDrawRec.width;
    float ph = currDrawRec.height;

    // Rectangle hiện tại
    Rectangle currRec = {
        currCenterBottom.x - pw / 2.0f,
        currCenterBottom.y - ph,
        pw,
        ph};
    int mapHeight = Map.size();
    int mapWidth = Map[0].size();
    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            int id = Map[i][j];
            if (id == 0)
                continue;

            Rectangle rec_map = {
                j * 16.0f * scale_screen,
                i * 16.0f * scale_screen,
                16.0f * scale_screen,
                16.0f * scale_screen};

            if (!CheckCollisionRecs(currRec, rec_map))
                continue;

            if (id == 2)
            {
                player->Die();
            }
            else
            {
                float overlapX = std::min(currRec.x + currRec.width - rec_map.x,
                                          rec_map.x + rec_map.width - currRec.x);
                float overlapY = std::min(currRec.y + currRec.height - rec_map.y,
                                          rec_map.y + rec_map.height - currRec.y);
                if (overlapX < overlapY)
                {
                    // Va chạm ngang
                    if (currRec.x < rec_map.x)
                    {
                        // Từ trái sang
                        if (Map[i][j - 1] == 0)
                        {
                            player->Set_Pos({rec_map.x - pw / 2.0f, player->getPosition().y});
                            player->Set_Velocity({0, player->get_Velocity().y});
                        }
                    }
                    else
                    {
                        // Từ phải sang
                        if (Map[i][j + 1] == 0)
                        {
                            player->Set_Pos({rec_map.x + rec_map.width + pw / 2.0f, player->getPosition().y});
                            player->Set_Velocity({0, player->get_Velocity().y});
                        }
                    }
                }
                else
                {
                    // Va chạm dọc
                    if (currRec.y <= rec_map.y && Map[i - 1][j] == 0 && player->get_Velocity().y >= 0)
                    {
                        // Từ trên xuống
                        player->Set_Pos({player->getPosition().x, rec_map.y});
                        player->Set_Velocity({player->get_Velocity().x, 0});
                        player->Set_isGround(true);
                    }
                    else if (currRec.y + currRec.height > rec_map.y + rec_map.height && Map[i + 1][j] == 0 && player->get_Velocity().y < 0)
                    {
                        // Từ dưới lên
                        player->Set_Pos({player->getPosition().x, rec_map.y + rec_map.height + ph});
                        player->Set_Velocity({player->get_Velocity().x, 0});
                    }
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
        if (!enemy || !enemy->Get_Is_Active() || enemy->Get_Is_Dead() || !enemy->Get_First_Appear())
            continue;

        Rectangle enemyRec = enemy->Get_Draw_Rec();

        if (!CheckCollisionRecs(playerRec, enemyRec))
            continue;

        if (player->Get_isInvincible())
        {
            enemy->Notify_Be_Fired_Or_Hit(information);
            SoundManager::GetInstance().PlaySoundEffect("stomp");
            continue;
        }

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

        for (int i = 0; i < Map.size(); i++)
        {
            for (int j = 0; j < Map[i].size(); j++)
            {
                int id = Map[i][j];
                if (id == 0)
                    continue;

                Rectangle rec_map = {j * 16.0f * scale_screen, i * 16.0f * scale_screen, 16.0f * scale_screen, 16.0f * scale_screen};

                if (!CheckCollisionRecs(rec_item, rec_map))
                    continue;

                // Va chạm từ trên xuống
                if (prev.y <= rec_map.y &&
                    i > 0 &&
                    Map[i - 1][j] == 0)
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
        for (int i = 0; i < Map.size(); i++)
        {
            for (int j = 0; j < Map[0].size(); j++)
            {
                int id = Map[i][j];
                if (id == 0)
                    continue;

                Rectangle rec_map = {j * 16.0f * scale_screen, i * 16.0f * scale_screen, 16.0f * scale_screen, 16.0f * scale_screen};

                if (!CheckCollisionRecs(rec_enemy, rec_map))
                    continue;

                // Va chạm từ trên xuống
                if (prev.y <= rec_map.y &&
                    i > 0 &&
                    Map[i - 1][j] == 0)
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
    for (auto *fireball : fireballs)
    {
        if (!fireball->getActive())
            continue;
        Rectangle rec_fireball = fireball->get_draw_rec();

        bool rebound = 0;

        for (Block *block : blocks)
        {
            Rectangle rec_block = block->Get_Draw_Rec();
            if (CheckCollisionRecs(rec_fireball, rec_block))
            {
                if (fireball->getVelocity().y > 0 && rec_fireball.y + rec_fireball.height -
                                                             (fireball->getVelocity().y * GetFrameTime()) <=
                                                         rec_block.y)
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

        for (int i = 0; i < Map.size(); i++)
            for (int j = 0; j < Map[0].size(); j++)
            {
                if (Map[i][j] == 0)
                    continue;
                Rectangle rec_map = {j * 16.0f * scale_screen, i * 16.0f * scale_screen, 16.0f * scale_screen, 16.0f * scale_screen};
                if (CheckCollisionRecs(rec_fireball, rec_map))
                {
                    if (Map[i][j] == 2)
                    {
                        fireball->explode();
                        goto next_fireball;
                    }
                    else if (fireball->getVelocity().y > 0 && rec_fireball.y + rec_fireball.height - (fireball->getVelocity().y * GetFrameTime()) <= rec_map.y)
                    {
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

        for (Enemy *enemy : enemies)
        {
            if (!enemy->Get_Is_Active() || enemy->Get_Is_Dead())
                continue;
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

void Stage::LoadEnemiesFromFile(const std::string &filename)
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
        Spawn_Enemy::SpawnEnemies(type, position, player, enemy_map, enemies, camera);
    }

    file.close();
}

void Stage::LoadBlockFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        // Nếu không mở được file, in ra lỗi
        return;
    }
    for (int i = 0; i < Map.size(); ++i)
    {
        for (int j = 0; j < Map[0].size(); ++j)
        {
            int var;
            file >> var;
            Vector2 pos = {(j + 0.5) * Tile_Size, (i + 1) * Tile_Size};
            if (var < 100)
                continue;
            int type_block = var / 100;
            int type_item = (var % 100) / 10;
            int item_cnt = var % 10;
            if (type_block == 1 && type_item == 0 && item_cnt == 0)
                blocks.push_back(new Block(pos, 0, "", "question"));
            else if (type_block == 1 && type_item == 0)
                blocks.push_back(new Block(pos, item_cnt, "super_mushroom", "question"));
            else if (type_block == 1 && type_item == 1)
                blocks.push_back(new Block(pos, item_cnt, "one_up_mushroom", "question"));
            else if (type_block == 1 && type_item == 2)
                blocks.push_back(new Block(pos, item_cnt, "posion_mushroom", "question"));
            else if (type_block == 1 && type_item == 3)
                blocks.push_back(new Block(pos, item_cnt, "hidden_coin", "question"));
            else if (type_block == 1 && type_item == 4)
                blocks.push_back(new Block(pos, item_cnt, "flower", "question"));
            else if (type_block == 1 && type_item == 5)
                blocks.push_back(new Block(pos, item_cnt, "star", "question"));
            else if (type_block == 2 && type_item == 0 && item_cnt == 0)
                blocks.push_back(new Block(pos, 0, "", "normal"));
            else if (type_block == 2 && type_item == 0)
                blocks.push_back(new Block(pos, item_cnt, "super_mushroom", "normal"));
            else if (type_block == 2 && type_item == 1)
                blocks.push_back(new Block(pos, item_cnt, "one_up_mushroom", "normal"));
            else if (type_block == 2 && type_item == 2)
                blocks.push_back(new Block(pos, item_cnt, "posion_mushroom", "normal"));
            else if (type_block == 2 && type_item == 3)
                blocks.push_back(new Block(pos, item_cnt, "hidden_coin", "normal"));
            else if (type_block == 2 && type_item == 4)
                blocks.push_back(new Block(pos, item_cnt, "flower", "normal"));
            else if (type_block == 2 && type_item == 5)
                blocks.push_back(new Block(pos, item_cnt, "star", "normal"));
            else if (type_block == 3 && type_item == 0 && item_cnt == 0)
                blocks.push_back(new Block(pos, 0, "rotating_bar", "unbreakable"));
        }
    }
    file.close();
}

void Stage::LoadMapFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Cannot open file: " << filename << "\n";
        return;
    }

    Map.clear();
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::vector<int> row;
        int value;
        while (ss >> value)
        {
            row.push_back(value);
        }
        if (!row.empty())
        {
            Map.push_back(row);
        }
    }

    file.close();
}

void Stage::DrawLayer()
{
    for (int i = 0; i < 2; i++)
    {
        if (Layer[i].width == 0 || Layer[i].height == 0)
            continue; // tránh lỗi ảnh hỏng
        int x = 0;
        float scale = dest.height / (float)Layer[i].height;

        while (x <= dest.width)
        {
            Rectangle source = {0, 0, (float)Layer[i].width, (float)Layer[i].height};
            Rectangle destRect = {(float)x, 0, Layer[i].width * scale, Layer[i].height * scale};
            DrawTexturePro(Layer[i], source, destRect, {0, 0}, 0, WHITE);
            x += Layer[i].width * scale;
        }
    }
}

bool Stage::Game_Won() const
{
    return Is_Game_Won;
}

bool Stage::Change_State() 
{
    return Is_Game_Won && timer_ >= cool_down_after_win;
}


json Stage::to_json() const {
    json j;
    j["source"] = {source.x, source.y, source.width, source.height};
    j["dest"] = {dest.x, dest.y, dest.width, dest.height};
    j["Map"] = Map;
    j["player_mode"] = static_cast<int>(player_mode);
    j["timer_"] = timer_;
    j["Reset_Game"] = Reset_Game;
    j["Is_Game_Won"] = Is_Game_Won;
    if (player) {
        j["player"] = player->to_json();
    }
    j["camera"] = {
        camera.offset.x, camera.offset.y,
        camera.target.x, camera.target.y,
        camera.rotation,
        camera.zoom
    };
    j["enemies_size"] = enemies.size();
    for (const auto& enemy : enemies) {
        int type = -1;
        if (dynamic_cast<Goomba*>(enemy)) type = static_cast<int>(EnemyType::Goomba);
        else if (dynamic_cast<KoopaTroopa*>(enemy)) type = static_cast<int>(EnemyType::KoopaTroopaWalking);
        else if (dynamic_cast<Latiku*>(enemy)) type = static_cast<int>(EnemyType::Latiku);
        else if (dynamic_cast<PiranhaPlant*>(enemy)) type = static_cast<int>(EnemyType::PiranhaPlant);
        else if (dynamic_cast<BomberBill*>(enemy)) type = static_cast<int>(EnemyType::BomberBill);
        else if (dynamic_cast<Spiny*>(enemy)) type = static_cast<int>(EnemyType::Spiny);
        json enemy_json = enemy->to_json();
        // Đặt type lên đầu object
        json result_json;
        result_json["type"] = type;
        for (auto it = enemy_json.begin(); it != enemy_json.end(); ++it) {
            result_json[it.key()] = it.value();
        }
        j["enemies"].push_back(result_json);
    }
    return j;
}

void Stage::from_json(const json& j) {
    auto src = j.at("source");
    source = {src[0], src[1], src[2], src[3]};
    auto dst = j.at("dest");
    dest = {dst[0], dst[1], dst[2], dst[3]};
    Map = j.at("Map").get<std::vector<std::vector<int>>>();
    player_mode = static_cast<Player_Mode>(j.at("player_mode").get<int>());
    timer_ = j.at("timer_").get<float>();
    Reset_Game = j.at("Reset_Game").get<bool>();
    Is_Game_Won = j.at("Is_Game_Won").get<bool>();
    if (j.contains("player")) {
        if (player) delete player;
        if (player_mode == Player_Mode::MARIO_PLAYER) {
            player = new Mario({100,100});
        }
        else if (player_mode == Player_Mode::LUIGI_PLAYER) {
            player = new Luigi({100,100});
        }
        else {
            player = new Mario({100,100});
        }
        player->from_json(j.at("player"));
    }
    if (j.contains("camera")) {
        auto cam = j.at("camera");
        camera.offset = {cam[0], cam[1]};
        camera.target = {cam[2], cam[3]};
        camera.rotation = cam[4];
        camera.zoom = cam[5];
    }
    
    if (win_animation) delete win_animation;
    win_animation = new Win_Animation_Manager(*player, *flag_pole, *flag_castle, information);

    // Xóa các enemy cũ nếu có
    for (auto e : enemies) delete e;
    const_cast<std::vector<Enemy*>&>(enemies).clear();
    const_cast<std::unordered_map<Enemy*, std::vector<Enemy*>>&>(enemy_map).clear();
    if (j.contains("enemies")) {
        for (const auto& enemy_j : j.at("enemies")) {
            int type = enemy_j.value("type", -1);
            Vector2 pos = {0,0};
            if (enemy_j.contains("position")) {
                auto p = enemy_j["position"];
                pos = {p[0], p[1]};
            }
            Spawn_Enemy::SpawnEnemies(static_cast<EnemyType>(type), pos, player, const_cast<std::unordered_map<Enemy*, std::vector<Enemy*>>&>(enemy_map), const_cast<std::vector<Enemy*>&>(enemies), camera);
            if (!enemies.empty()) {
                json enemy_data = enemy_j;
                enemy_data.erase("type");
                enemies.back()->from_json(enemy_data);
            }
        }
    }
    // Khởi tạo lại các resource/phức tạp nếu cần
}