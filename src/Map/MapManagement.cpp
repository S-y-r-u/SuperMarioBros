#include "Map/MapManagement.h"

MapManagement::MapManagement(const std::string &filename)
{
    LoadMapFromFile(filename);
}

void MapManagement::Check_Player_Vs_Ground(Player &player)
{
    Vector2 currCenterBottom = player.getPosition();
    Vector2 velocity = player.get_Velocity();

    // Lấy kích thước player
    Rectangle currDrawRec = player.get_draw_rec();
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
                player.Die();
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
                            player.Set_Pos({rec_map.x - pw / 2.0f, player.getPosition().y});
                            player.Set_Velocity({0, player.get_Velocity().y});
                        }
                    }
                    else
                    {
                        // Từ phải sang
                        if (Map[i][j + 1] == 0)
                        {
                            player.Set_Pos({rec_map.x + rec_map.width + pw / 2.0f, player.getPosition().y});
                            player.Set_Velocity({0, player.get_Velocity().y});
                        }
                    }
                }
                else
                {
                    // Va chạm dọc
                    if (currRec.y <= rec_map.y && Map[i - 1][j] == 0 && player.get_Velocity().y >= 0)
                    {
                        // Từ trên xuống
                        player.Set_Pos({player.getPosition().x, rec_map.y});
                        player.Set_Velocity({player.get_Velocity().x, 0});
                        player.Set_isGround(true);
                    }
                    else if (currRec.y + currRec.height > rec_map.y + rec_map.height && Map[i + 1][j] == 0 && player.get_Velocity().y < 0)
                    {
                        // Từ dưới lên
                        player.Set_Pos({player.getPosition().x, rec_map.y + rec_map.height + ph});
                        player.Set_Velocity({player.get_Velocity().x, 0});
                    }
                }
            }
        }
    }
}

void MapManagement::Check_Item_Vs_Ground(Item *item)
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
            if (id == 0 || id == 2)
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

void MapManagement::Check_Enemy_Vs_Ground(Enemy &enemy)
{
    if (!enemy.Get_Is_Active() || enemy.Get_Is_Dead() || !enemy.Need_Check_Map())
        return;

    Rectangle rec_enemy = enemy.Get_Draw_Rec();
    Vector2 prev = enemy.Get_Previous_Pos();
    float w = rec_enemy.width;
    float h = rec_enemy.height;

    enemy.Notify_Fall(GetFrameTime());

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
                enemy.Set_Pos({enemy.Get_Pos().x, rec_map.y});
                enemy.Notify_On_Ground();
            }
            // Va chạm từ bên trái
            else if (prev.x + w / 2.0f <= rec_map.x && !avoid_branch)
            {
                enemy.Set_Pos({rec_map.x - w / 2.0f, enemy.Get_Pos().y});
                enemy.Notify_Change_Direct();
                avoid_branch = true;
            }
            // Va chạm từ bên phải
            else if (prev.x - w / 2.0f >= rec_map.x + rec_map.width && !avoid_branch)
            {
                enemy.Set_Pos({rec_map.x + rec_map.width + w / 2.0f, enemy.Get_Pos().y});
                enemy.Notify_Change_Direct();
                avoid_branch = true;
            }
        }
    }
    if (dynamic_cast<KoopaTroopa *>(&enemy))
    {
        KoopaTroopa *koopa = dynamic_cast<KoopaTroopa *>(&enemy);
        if (koopa->Get_First_Appear())
        {
            koopa->Apply_AI(*this);
        }
    }
}

void MapManagement::LoadMapFromFile(const std::string &filename)
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

json MapManagement::to_json() const
{
    json j;
    j["Map"] = Map;
    return j;
}

void MapManagement::from_json(const json &j)
{
    Map = j.at("Map").get<std::vector<std::vector<int>>>();
}

int MapManagement::GetHeight() const
{
    return Map.size();
}

int MapManagement::GetWidth() const
{
    return Map.empty() ? 0 : Map[0].size();
}

int MapManagement::GetTile(int x, int y) const
{
    if (y < 0 || y >= Map.size() || x < 0 || x >= Map[0].size())
        return -1; // Invalid tile coordinates
    return Map[y][x];
}
