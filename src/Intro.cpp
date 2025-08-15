#include "Intro.h"

Intro_Animation::Intro_Animation(PlayerInformation &player_info, Player_Mode player_mode)
    : player_info(player_info),
      player_mode(player_mode),
      timer_(0.0f) {}
