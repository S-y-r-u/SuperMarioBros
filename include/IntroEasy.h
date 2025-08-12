#include "GameManager/I_Stage.h"
#include "GameManager/PlayerInformation.h"

class Intro_Easy : public I_Stage
{
private:
    Texture2D intro_easy;
    PlayerInformation& player_info;
    Player_Mode player_mode;
public:
    Intro_Easy(PlayerInformation& info, Player_Mode mode);
    virtual ~Intro_Easy();
    void Draw() override;
    void Run() override;
};
