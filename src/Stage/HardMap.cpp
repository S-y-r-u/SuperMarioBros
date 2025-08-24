#include "Stage/HardMap.h"

HardMap::HardMap(PlayerInformation &info, Player *&player, Player_Mode &player_mode) : Stage(info, player, player_mode)
{
    MapTexture = LoadTexture("map/Hard/Hard.png");
    map = new MapManagement("map/Hard/Hard.txt");
    LoadBlockFromFile("map/Hard/Block_Hard.txt");
    Layer[0] = LoadTexture("map/Hard/First_Layer.png");
    LoadEnemiesFromFile("map/Hard/Enemy_Hard.txt");
    source = {0, 0, static_cast<float>(MapTexture.width), static_cast<float>(MapTexture.height)};
    dest = {0, 0, static_cast<float>(MapTexture.width * scale_screen), static_cast<float>(MapTexture.height * scale_screen)};

    win_animation = new Win_Animation_Save_Prince({6840, 480}, {7440, 624}, info, player);
    camera.target = {0, 0};
    camera.offset = {0, 0};
    camera.rotation = 0;
    camera.zoom = 1;
}

HardMap::~HardMap()
{
    UnloadTexture(MapTexture);
    for (auto it : up_platforms)
        delete it;
    up_platforms.clear();
    for (auto it : down_platforms)
        delete it;
    down_platforms.clear();
}

void HardMap::Spawn_Platform()
{
    if (up_platforms.empty())
        up_platforms.push_back(new Vertical_Platform({4152, Screen_h}, -150));
    if (down_platforms.empty())
        down_platforms.push_back(new Vertical_Platform({4296, -24}, 150));
    while (!up_platforms.empty() && up_platforms.back()->Get_Bounding_Box().y < -480)
    {
        delete up_platforms.back();
        up_platforms.pop_back();
    }
    while (!down_platforms.empty() && down_platforms.back()->Get_Bounding_Box().y > Screen_h)
    {
        delete down_platforms.back();
        down_platforms.pop_back();
    }
    if (up_platforms.back()->Get_Bounding_Box().y < Screen_h * 2 / 3)
        up_platforms.push_back(new Vertical_Platform({4152, Screen_h}, -150));
    if (down_platforms.back()->Get_Bounding_Box().y > Screen_h / 3)
        down_platforms.push_back(new Vertical_Platform({4296, -24}, 150));
}

void HardMap::Check_Player_Platform()
{
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
    for (int i = 0; i < up_platforms.size(); i++)
    {
        Rectangle rec_map = up_platforms[i]->Get_Bounding_Box();
        if (!CheckCollisionRecs(currRec, rec_map))
            continue;
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
                    player->Set_Pos({rec_map.x - pw / 2.0f, player->getPosition().y});
                    player->Set_Velocity({0, player->get_Velocity().y});
                }
                else
                {
                    // Từ phải sang
                    player->Set_Pos({rec_map.x + rec_map.width + pw / 2.0f, player->getPosition().y});
                    player->Set_Velocity({0, player->get_Velocity().y});
                }
            }
            else
            {
                // Va chạm dọc
                if (currRec.y <= rec_map.y && player->get_Velocity().y >= 0)
                {
                    // Từ trên xuống
                    player->Set_Pos({player->getPosition().x, rec_map.y});
                    player->Set_Velocity({player->get_Velocity().x, 0});
                    player->Set_isGround(true);
                }
                else if (currRec.y + currRec.height > rec_map.y + rec_map.height && player->get_Velocity().y < 0)
                {
                    // Từ dưới lên
                    player->Set_Pos({player->getPosition().x, rec_map.y + rec_map.height + ph});
                    player->Set_Velocity({player->get_Velocity().x, 0});
                }
            }
        }
    }
    for (int i = 0; i < down_platforms.size(); i++)
    {
        Rectangle rec_map = down_platforms[i]->Get_Bounding_Box();
        if (!CheckCollisionRecs(currRec, rec_map))
            continue;
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
                    player->Set_Pos({rec_map.x - pw / 2.0f, player->getPosition().y});
                    player->Set_Velocity({0, player->get_Velocity().y});
                }
                else
                {
                    // Từ phải sang
                    player->Set_Pos({rec_map.x + rec_map.width + pw / 2.0f, player->getPosition().y});
                    player->Set_Velocity({0, player->get_Velocity().y});
                }
            }
            else
            {
                // Va chạm dọc
                if (currRec.y <= rec_map.y && player->get_Velocity().y >= 0)
                {
                    // Từ trên xuống
                    player->Set_Pos({player->getPosition().x, rec_map.y});
                    player->Set_Velocity({player->get_Velocity().x, down_platforms[i]->Get_Velocity().y});
                    player->Set_isGround(true);
                }
                else if (currRec.y + currRec.height > rec_map.y + rec_map.height && player->get_Velocity().y < 0)
                {
                    // Từ dưới lên
                    player->Set_Pos({player->getPosition().x, rec_map.y + rec_map.height + ph});
                    player->Set_Velocity({player->get_Velocity().x, down_platforms[i]->Get_Velocity().y});
                }
            }
        }
    }
}

void HardMap::Draw()
{
    Stage::Draw();
    BeginMode2D(camera);
    DrawTexturePro(MapTexture, source, dest, {0, 0}, 0, WHITE);

    for (Block *block : blocks)
    {
        if (!block->Get_Is_Delete())
            block->Draw_();
    }

    for (FireBall *fireball : fireballs)
        fireball->draw();

    Score_Manager::GetInstance().Draw();

    for (auto it : up_platforms)
        it->Draw();
    for (auto it : down_platforms)
        it->Draw();
    for (auto it : fire_blocks)
        it->Draw();
    player->draw();
    EndMode2D();
    information.Draw();
}

void HardMap::Run()
{
    Spawn_Platform();
    Spawn_Fire_Block();
    Delete_Fire_Block();
    Stage::Run();
    if (!player->Get_isDead())
        Check_Player_Platform();
    if (!player->Get_isTransforming())
    {
        for (auto it : up_platforms)
            it->Update();
        if (!player->Get_isTransforming())
        {
            for (auto it : down_platforms)
                it->Update();
        }
    }
    for (auto it : fire_blocks)
        it->Update();
}

void HardMap::Spawn_Fire_Block()
{
    if (fire_blocks.empty())
    {
        for (int i = 1; i < map->GetWidth(); i++)
        {
            for (int j = 1; j < map->GetHeight(); j++)
            {
                if (map->GetTile(i, j) == 2 && map->GetTile(i, j - 1) == 0)
                    fire_blocks.push_back(new Fire_Block({i * Tile_Size + Tile_Size / 2.0f, Tile_Size * (j + 1)}));
            }
        }
    }
    Vector2 top_left = GetScreenToWorld2D({0, 0}, camera);
    Vector2 bottom_right = GetScreenToWorld2D({(float)GetScreenWidth(), (float)GetScreenHeight()}, camera);

    Rectangle screen_rect_world = {
        top_left.x,
        top_left.y,
        bottom_right.x - top_left.x,
        bottom_right.y - top_left.y};

    int col = (screen_rect_world.x + screen_rect_world.width) / Tile_Size;
    for (int i = 1; i < map->GetHeight(); i++)
    {
        if (map->GetTile(col, i) == 2 && map->GetTile(col, i - 1) == 0)
        {
            if (fire_blocks.empty())
                fire_blocks.push_back(new Fire_Block({col * Tile_Size + Tile_Size / 2.0f, Tile_Size * (i + 1)}));
            else if (fire_blocks.back()->Get_Pos().x < col * Tile_Size + Tile_Size / 2.0f)
                fire_blocks.push_back(new Fire_Block({col * Tile_Size + Tile_Size / 2.0f, Tile_Size * (i + 1)}));
        }
    }
}

void HardMap::Delete_Fire_Block()
{
    Vector2 top_left = GetScreenToWorld2D({0, 0}, camera);
    Vector2 bottom_right = GetScreenToWorld2D({(float)GetScreenWidth(), (float)GetScreenHeight()}, camera);

    Rectangle screen_rect_world = {
        top_left.x,
        top_left.y,
        bottom_right.x - top_left.x,
        bottom_right.y - top_left.y};

    for (auto it = fire_blocks.begin(); it != fire_blocks.end();)
    {
        if ((*it)->Get_Pos().x + Tile_Size / 2.0f < screen_rect_world.x)
        {
            delete *it;
            it = fire_blocks.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

json HardMap::to_json() const
{
    json j = Stage::to_json();
    // Serialize specific attributes for HardMap
    j["up_platforms"] = json::array();
    for (const auto &platform : up_platforms)
    {
        j["up_platforms"].push_back(platform->to_json());
    }
    j["down_platforms"] = json::array();
    for (const auto &platform : down_platforms)
    {
        j["down_platforms"].push_back(platform->to_json());
    }
    // j["fire_blocks"] = json::array();
    // for (const auto &fire_block : fire_blocks)
    // {
    //     j["fire_blocks"].push_back(fire_block->to_json());
    // }
    return j;
}

void HardMap::from_json(const json &j)
{
    Stage::from_json(j);
    // Deserialize specific attributes for HardMap
    for (auto &it : up_platforms)
        delete it;
    up_platforms.clear();
    for (auto &it : down_platforms)
        delete it;
    down_platforms.clear();
    for (const auto &item : j.at("up_platforms"))
    {
        I_Platform *platform = new Vertical_Platform({4152, Screen_h}, -150);
        platform->from_json(item);
        up_platforms.push_back(platform);
    }
    for (const auto &item : j.at("down_platforms"))
    {
        I_Platform *platform = new Vertical_Platform({4296, -24}, 150);
        platform->from_json(item);
        down_platforms.push_back(platform);
    }
    // for (const auto &item : j.at("fire_blocks"))
    // {
    //     Fire_Block *fire_block = new Fire_Block();
    //     fire_block->from_json(item);
    //     fire_blocks.push_back(fire_block);
    // }
}