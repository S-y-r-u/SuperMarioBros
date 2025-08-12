#include "GameManager/I_Stage.h"
#include "GameManager/PlayerInformation.h"

class Intro_Medium : public I_Stage
{
private:
    Texture2D intro_medium;
    PlayerInformation& player_info;
    Player_Mode player_mode;
public:
    Intro_Medium(PlayerInformation& info, Player_Mode mode);
    virtual ~Intro_Medium();
    void Draw() override;
    void Run() override;
};
