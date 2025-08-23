#include "Intro.h"

class Intro_Easy : public Intro_Animation
{
public:
    Intro_Easy(PlayerInformation &info, Player_Mode mode);
    virtual ~Intro_Easy();
    void Draw() override;
    void Run() override;
    bool Change_State() override;
};
