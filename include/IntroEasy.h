#include "GameManager/I_Stage.h"
#include "GameManager/PlayerInformation.h"

class Intro_Easy : public I_Stage
{
private:
    Texture2D intro_easy;
    PlayerInformation& player_info;
    Player_Mode player_mode;
    float timer_;
    const float End_Intro = 2.0f;
public:
    Intro_Easy(PlayerInformation& info, Player_Mode mode);
    virtual ~Intro_Easy();
    void Draw() override;
    void Run() override;
    bool Change_State() override;
};
