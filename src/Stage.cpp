#include "Stage.h"
#include "algorithm"

Stage::Stage()
{
    source = {0, 0, 3424, 240};
    dest = {0, 0, 10272, 720};
}

Stage::~Stage()
{
    for (Item *item : items)
        delete item;
    items.clear();

    for (Block *block : blocks)
        delete block;
    blocks.clear();

    for (Enemy *enemy : enemies)
        delete enemy;
    enemies.clear();

    delete player;
}

void Stage::Run()
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
    if (Keyboard.empty())
        player->StopMoving();
    else if (Keyboard.back() == KEY_A)
        player->MoveLeft();
    else
        player->MoveRight();
    
    player->update(GetFrameTime());

    camera.target.x = std::max(camera.target.x, player->getPosition().x - Screen_w / 2.0f);
    Check_Player_Vs_Ground();
    Check_Player_Vs_Enemy();
    Check_Block_Vs_Block();
    Check_Player_Vs_Block();
    Check_Item_Vs_Ground();
    Check_Item_Vs_Block();
    Check_Enemy_Vs_Ground();

    for (Item *item : items)
    {
        Rectangle player_rec = player->get_draw_rec();
        Rectangle rec_item = item->Get_Draw_Rec();
        if (CheckCollisionRecs(player_rec, rec_item) && !item->Is_Appear_Animation())
            item->Activate_(*player);
    }


    for (size_t i = 0; i < items.size();)
    {
        if (items[i]->Get_Is_Delete())
            items.erase(items.begin() + i);
        else
            i++;
    }

    for (size_t i = 0; i < blocks.size();)
    {
        if (blocks[i]->Get_Is_Delete())
            blocks.erase(blocks.begin() + i);
        else
            i++;
    }

    for (size_t i = 0; i < enemies.size();)
    {
        if (!enemies[i]->Get_Is_Active())
            enemies.erase(enemies.begin() + i);
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
        enemies[i]->Update(GetFrameTime());
    }
}

void Stage::Draw()
{
    Run();
    BeginMode2D(camera);
    DrawTexturePro(MapTexture, source, dest, {0, 0}, 0, WHITE);
    player->draw();

    for (Item *item : items)
        item->Draw_();
    for (Block *block : blocks)
        block->Draw_();
    for (Enemy *enemy : enemies)
        enemy->Draw();
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
    velocity.y += 500.0f * deltaTime; // Gravity effect
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
            if ( prevPos.x + preRec.width <= rec_map.x)
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
            else if (prevPos.y > rec_map.y + rec_map.height  && !block->Surrounded_Block[1] && player->get_Velocity().y < 0)
            {
                // Va chạm từ dưới lên (đụng đầu)
                player->Set_Pos({player->getPosition().x, rec_map.y + rec_map.height});
                player->Set_Velocity({player->get_Velocity().x, 0.f});
                block->On_Hit(items, *player);
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
    velocity.y += 500.0f * deltaTime; // Gravity effect
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
                if ( prevPos.x + preRec.width < rec_map.x  )
                {
                    // Va chạm từ bên trái
                    if (Map[j-1][i] == 0)
                    {
                        player->Set_Pos({rec_map.x - currentRec.width, player->getPosition().y});
                        player->Set_Velocity({0, player->get_Velocity().y});
                    }
                }
                else{
                    // Va chạm từ bên phải
                    if (Map[j+1][i] == 0)
                    {
                        player->Set_Pos({rec_map.x + rec_map.width , player->getPosition().y});
                        player->Set_Velocity({0, player->get_Velocity().y});
                    }
                }
            }
            else
            {
                // Va chạm dọc
                if (prevPos.y + preRec.height < rec_map.y && Map[j][i-1] == 0 && player->get_Velocity().y >= 0)
                {  
                    // Va chạm từ trên xuống (đáp xuống mặt đất)
                    player->Set_Pos({player->getPosition().x, rec_map.y - currentRec.height});
                    player->Set_Velocity({player->get_Velocity().x, -500.0f * deltaTime});
                    player->Set_isGround(true);
                }
                else if (prevPos.y > rec_map.y + rec_map.height && Map[j][i+1] == 0 && player->get_Velocity().y < 0)
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
                    enemy->Notify_Be_Kicked(1);
                }
                else
                {
                    player->Set_Pos({player->getPosition().x, 200.0f}); 
                }
            }
            else
            {
                // Player ở bên phải enemy
                // Xử lý va chạm từ bên phải
                if (enemy->Can_Be_Kicked()) 
                {       
                    enemy->Notify_Be_Kicked(-1);
                }
                else  
                {
                    player->Set_Pos({player->getPosition().x, 200.0f}); 
                }
            }
        }
        else
        {
            // Va chạm dọc (trên/dưới)
            if (playerRec.y + playerRec.height / 2 < enemyRec.y + enemyRec.height / 2)
            {
                // Player ở phía trên enemy - nhảy lên đầu enemy
                if (enemy->Can_Be_Stomped())
                {
                    player ->Set_Velocity({player->get_Velocity().x, -player->get_Velocity().y });
                    enemy->Notify_Be_Stomped();
                }
                else {
                    player->Set_Pos({player->getPosition().x, 200.0f}); 
                }
            }
            else
            {
                player->Set_Pos({player->getPosition().x, 200.0f}); // Đẩy player lên trên nếu va chạm từ dưới
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

        Mush_Room *mush_room = dynamic_cast<Mush_Room *>(item);
        Star *star = dynamic_cast<Star *>(item);

        if (!mush_room && !star)
            continue;

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

void Stage::Check_Enemy_Vs_Ground()
{
    for (Enemy *enemy : enemies)
    {
        if (Latiku *latiku = dynamic_cast<Latiku *>(enemy))
            continue;
        if (PiranhaPlant *piranha = dynamic_cast<PiranhaPlant *>(enemy))
            continue;
        if (!enemy || !enemy->Get_Is_Active() || enemy->Get_Is_Dead())
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

void Stage::Check_Block_Vs_Block()
{
    const float Tile_Size = 16.0f * 3.0f; // scale_screen = 3.0f
    
    for (Block *mainblock : blocks) {
        // Reset surrounded blocks state
        mainblock->Surrounded_Block = {false, false, false, false}; // top, bottom, left, right
        
        Vector2 mainPos = mainblock->Get_Pos();
        
        for (Block *block : blocks) {
            if (mainblock == block) continue; // Skip checking with itself
            
            Vector2 blockPos = block->Get_Pos();
            
            // Calculate position differences
            float dx = blockPos.x - mainPos.x;
            float dy = blockPos.y - mainPos.y;
            
            // Check if blocks are adjacent (within tile size tolerance)
            const float tolerance = Tile_Size * 0.1f; // Small tolerance for floating point comparison
            
            // Check top (block above mainblock)
            if (abs(dx) <= tolerance && dy < 0 && abs(dy) <= Tile_Size + tolerance) {
                mainblock->Surrounded_Block[0] = true; // top
            }
            // Check bottom (block below mainblock) 
            else if (abs(dx) <= tolerance && dy > 0 && abs(dy) <= Tile_Size + tolerance) {
                mainblock->Surrounded_Block[1] = true; // bottom
            }
            // Check left (block to the left of mainblock)
            else if (abs(dy) <= tolerance && dx < 0 && abs(dx) <= Tile_Size + tolerance) {
                mainblock->Surrounded_Block[2] = true; // left
            }
            // Check right (block to the right of mainblock)
            else if (abs(dy) <= tolerance && dx > 0 && abs(dx) <= Tile_Size + tolerance) {
                mainblock->Surrounded_Block[3] = true; // right
            }
        }
    }
}



