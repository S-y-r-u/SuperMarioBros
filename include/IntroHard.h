#include "Intro.h"

class Intro_Hard : public Intro_Animation
{
public:
    Intro_Hard(PlayerInformation &info, Player_Mode mode);
    virtual ~Intro_Hard();
    void Draw() override;
    void Run() override;
    bool Change_State() override;
};