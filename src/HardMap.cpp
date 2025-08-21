#include "HardMap.h"

HardMap::HardMap(PlayerInformation &info, Player *&player) : Stage(info, player)
{
    MapTexture = LoadTexture("map/Hard/Hard.png");
    LoadMapFromFile("map/Hard/Hard.txt");
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
        up_platforms.push_back(new Vertical_Platform({3480, Screen_h}, -150));
    if (down_platforms.empty())
        down_platforms.push_back(new Vertical_Platform({3624, -24}, 150));
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
    for (auto it : up_platforms)
        it->Draw();
    for (auto it : down_platforms)
        it->Draw();
    EndMode2D();
}

void HardMap::Run()
{
    Spawn_Platform();
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
}