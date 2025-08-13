#pragma once
#include "Constants.h"
#include "Item/Item.h"
#include "Player.h"
#include "GameManager/PlayerInformation.h"
#include "GameManager/Animation.h"
#include <raylib.h>
#include <string>
#include <vector>

class A_Block_State
{
protected:
    Animation animation_;

public:
    A_Block_State();
    virtual ~A_Block_State() = default;

    virtual void Draw_() = 0;
    virtual void Update_() = 0;
    virtual void On_Hit(std::vector<Item *> &item, Player &player, PlayerInformation &info) = 0;
    virtual bool Kill_Player(Player &player);

    virtual bool Get_Elapse() = 0;
    virtual bool Get_Is_Delete() const;

    virtual Rectangle Get_Draw_Rec() const = 0;
};
