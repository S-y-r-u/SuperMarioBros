#include "Intro.h"

class Intro_Medium : public Intro_Animation
{
public:
    Intro_Medium(PlayerInformation &info, Player_Mode mode);
    virtual ~Intro_Medium();
    void Draw() override;
    void Run() override;
    bool Change_State() override;
};
