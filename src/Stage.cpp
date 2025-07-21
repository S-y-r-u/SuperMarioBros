#include "Stage.h"

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

    delete player;
}

void Stage::Run()
{
    if (IsKeyPressed(KEY_A))
        player->MoveLeft();
    else if (IsKeyPressed(KEY_D))
        player->MoveRight();

    player->update(GetFrameTime());

    camera.target = player->getPosition();
    /*
    Check_Item_Vs_Ground();
    Check_Item_Vs_Block();
    for (Item *item : items)
        item->Update_();
    for (Block *block : blocks)
        block->Update_();
    */
}

void Stage::Draw()
{
    Run();
    BeginMode2D(camera);
    DrawTexturePro(MapTexture, source, dest, {0, 0}, 0, WHITE);
    player->draw();
    /*
    for(Item* item : items) 
        item->Draw_();
    */
    EndMode2D();
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
