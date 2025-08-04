#pragma once
#include "Constants.h"
#include "Item/Item.h"
#include "Player.h"
#include "PlayerInformation.h"
#include <raylib.h>
#include <string>
#include <vector>

class A_Block_State
{
protected:
    Rectangle rec_;

public:
    virtual ~A_Block_State() = default;

    virtual void Draw_() = 0;
    virtual void Update_() = 0;
    virtual void On_Hit(std::vector<Item *> &item, Player &player, PlayerInformation &info) = 0;

    virtual bool Get_Elapse() = 0;
    virtual bool Get_Is_Delete() const;

    Rectangle Get_Source_Rec() const;
    virtual Rectangle Get_Draw_Rec() const = 0;
};
