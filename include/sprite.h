#pragma once
#include "raylib.h"
#include <vector>

struct SpriteSheet
{
    Texture2D sprite;
    Image image;
    Color *pixel = nullptr;
    void Load_(const char *path);
    void Unload_();
    Color Get_Pixel(int x, int y) const;
};

namespace Mario
{
    namespace Small
    {
        namespace Stance
        {
            extern Rectangle stance;
            extern std::vector<Rectangle> stance_;
        }
        namespace Jump
        {
            extern Rectangle jump;
            extern std::vector<Rectangle> jump_;
        }
        namespace Die
        {
            extern Rectangle die;
            extern std::vector<Rectangle> die_;
        }
        namespace Walk
        {
            extern Rectangle w1;
            extern Rectangle w2;
            extern Rectangle w3;
            extern std::vector<Rectangle> walk_;
        }
        namespace Slide
        {
            extern Rectangle slide;
            extern std::vector<Rectangle> slide_;
        }
        namespace Climb
        {
            extern Rectangle c1;
            extern Rectangle c2;
            extern std::vector<Rectangle> climb_;
        }
        namespace Small_To_Super
        {
            // x3
            extern Rectangle s1;
            extern Rectangle s2;
            //
            extern Rectangle s3;
            extern Rectangle s4;
            extern Rectangle s5;
            extern Rectangle s6;
            extern std::vector<Rectangle> small_to_super;
        }
    }

    namespace Invincible
    {
        namespace Stance
        {
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            extern std::vector<Rectangle> stance_;
        }
        namespace Jump
        {
            extern Rectangle j1;
            extern Rectangle j2;
            extern Rectangle j3;
            extern Rectangle j4;
            extern std::vector<Rectangle> jump_;
        }
        namespace Walk
        {
            extern Rectangle w1;
            extern Rectangle w2;
            extern Rectangle w3;
            extern Rectangle w4;
            extern Rectangle w5;
            extern Rectangle w6;
            extern Rectangle w7;
            extern Rectangle w8;
            extern Rectangle w9;
            extern Rectangle w10;
            extern Rectangle w11;
            extern Rectangle w12;
            extern std::vector<Rectangle> walk_;
        }
        namespace Climb
        {
            extern Rectangle c1;
            extern Rectangle c2;
            extern Rectangle c3;
            extern Rectangle c4;
            extern Rectangle c5;
            extern Rectangle c6;
            extern Rectangle c7;
            extern Rectangle c8;
            extern std::vector<Rectangle> climb_;
        }
        namespace Slide
        {
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            extern std::vector<Rectangle> slide_;
        }
        namespace Small_To_Super
        {
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            extern Rectangle s5;
            extern Rectangle s6;
            extern Rectangle s7;
            extern Rectangle s8;
            extern Rectangle s9;
            extern Rectangle s10;
            extern Rectangle s11;
            extern Rectangle s12;
            extern Rectangle s13;
            // x2
            extern Rectangle s14;
            extern Rectangle s15;
            extern Rectangle s16;
            extern Rectangle s17;
            //
            extern std::vector<Rectangle> small_to_super;
        }
    }

    namespace Super
    {
        namespace Stance
        {
            extern Rectangle stance;
            extern std::vector<Rectangle> stance_;
        }
        namespace Stance_To_Fire
        {
            // x3
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            //
            extern std::vector<Rectangle> stance_to_fire;
        }
        namespace Crouch
        {
            extern Rectangle crouch;
            extern std::vector<Rectangle> crouch_;
        }
        namespace Crouch_To_Fire
        {
            // x3
            extern Rectangle c1;
            extern Rectangle c2;
            extern Rectangle c3;
            extern Rectangle c4;
            //
            extern std::vector<Rectangle> crouch_to_fire;
        }
        namespace Jump
        {
            extern Rectangle jump;
            extern std::vector<Rectangle> jump_;
        }
        namespace Jump_To_Fire
        {
            // x3
            extern Rectangle j1;
            extern Rectangle j2;
            extern Rectangle j3;
            extern Rectangle j4;
            //
            extern std::vector<Rectangle> jump_to_fire;
        }
        namespace Walk
        {
            extern Rectangle w1;
            extern Rectangle w2;
            extern Rectangle w3;
            extern std::vector<Rectangle> walk_;
        }
        namespace Walk_To_Fire
        {
            // x3
            extern Rectangle w1;
            extern Rectangle w2;
            extern Rectangle w3;
            extern Rectangle w4;
            //
            extern std::vector<Rectangle> walk_to_fire;
        }
        namespace Slide
        {
            extern Rectangle slide;
            extern std::vector<Rectangle> slide_;
        }
        namespace Slide_To_Fire
        {
            // x3
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            //
            extern std::vector<Rectangle> slide_to_fire;
        }
        namespace Climb
        {
            extern Rectangle c1;
            extern Rectangle c2;
            extern std::vector<Rectangle> climb_;
        }
        namespace Hit
        {
            extern Rectangle h1;
            extern Rectangle h2;
            // x6
            extern Rectangle h3;
            extern Rectangle h4;
            //
            extern Rectangle h5;
            extern std::vector<Rectangle> hit_;
        }
    }

    namespace Invincible_Super
    {
        namespace Stance
        {
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            extern std::vector<Rectangle> stance_;
        }
        namespace Jump
        {
            extern Rectangle j1;
            extern Rectangle j2;
            extern Rectangle j3;
            extern Rectangle j4;
            extern std::vector<Rectangle> jump_;
        }
        namespace Crouch
        {
            extern Rectangle c1;
            extern Rectangle c2;
            extern Rectangle c3;
            extern Rectangle c4;
            extern std::vector<Rectangle> crouch_;
        }
        namespace Slide
        {
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            extern std::vector<Rectangle> slide_;
        }
        namespace Climb
        {
            extern Rectangle c1;
            extern Rectangle c2;
            extern Rectangle c3;
            extern Rectangle c4;
            extern Rectangle c5;
            extern Rectangle c6;
            extern Rectangle c7;
            extern Rectangle c8;
            extern std::vector<Rectangle> climb_;
        }
        namespace Shoot_Fire
        {
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            extern std::vector<Rectangle> shoot_fire;
        }
        namespace Walk
        {
            extern Rectangle w1;
            extern Rectangle w2;
            extern Rectangle w3;
            extern Rectangle w4;
            extern Rectangle w5;
            extern Rectangle w6;
            extern Rectangle w7;
            extern Rectangle w8;
            extern Rectangle w9;
            extern Rectangle w10;
            extern Rectangle w11;
            extern Rectangle w12;
            extern std::vector<Rectangle> walk_;
        }
    }

    namespace Fire
    {
        namespace Stance
        {
            extern Rectangle stance;
            extern std::vector<Rectangle> stance_;
        }
        namespace Crouch
        {
            extern Rectangle crouch;
            extern std::vector<Rectangle> crouch_;
        }
        namespace Jump
        {
            extern Rectangle jump;
            extern std::vector<Rectangle> jump_;
        }
        namespace Walk
        {
            extern Rectangle w1;
            extern Rectangle w2;
            extern Rectangle w3;
            extern std::vector<Rectangle> walk_;
        }
        namespace Slide
        {
            extern Rectangle slide;
            extern std::vector<Rectangle> slide_;
        }
        namespace Climb
        {
            extern Rectangle c1;
            extern Rectangle c2;
            extern std::vector<Rectangle> climb_;
        }
        namespace Shoot
        {
            extern Rectangle shoot;
            extern std::vector<Rectangle> shoot_;
        }
        namespace Hit
        {
            extern Rectangle h1;
            extern Rectangle h2;
            // x6
            extern Rectangle h3;
            extern Rectangle h4;
            //
            extern Rectangle h5;
            extern std::vector<Rectangle> hit_;
        }
    }
}

namespace Luigi
{
    namespace Small
    {
        namespace Stance
        {
            extern Rectangle stance;
            extern std::vector<Rectangle> stance_;
        }
        namespace Jump
        {
            extern Rectangle jump;
            extern std::vector<Rectangle> jump_;
        }
        namespace Die
        {
            extern Rectangle die;
            extern std::vector<Rectangle> die_;
        }
        namespace Walk
        {
            extern Rectangle w1;
            extern Rectangle w2;
            extern Rectangle w3;
            extern std::vector<Rectangle> walk_;
        }
        namespace Slide
        {
            extern Rectangle slide;
            extern std::vector<Rectangle> slide_;
        }
        namespace Climb
        {
            extern Rectangle c1;
            extern Rectangle c2;
            extern std::vector<Rectangle> climb_;
        }
        namespace Small_To_Super
        {
            // x3
            extern Rectangle s1;
            extern Rectangle s2;
            //
            extern Rectangle s3;
            extern Rectangle s4;
            extern Rectangle s5;
            extern Rectangle s6;
            extern std::vector<Rectangle> small_to_super;
        }
    }

    namespace Invincible
    {
        namespace Stance
        {
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            extern std::vector<Rectangle> stance_;
        }
        namespace Jump
        {
            extern Rectangle j1;
            extern Rectangle j2;
            extern Rectangle j3;
            extern Rectangle j4;
            extern std::vector<Rectangle> jump_;
        }
        namespace Walk
        {
            extern Rectangle w1;
            extern Rectangle w2;
            extern Rectangle w3;
            extern Rectangle w4;
            extern Rectangle w5;
            extern Rectangle w6;
            extern Rectangle w7;
            extern Rectangle w8;
            extern Rectangle w9;
            extern Rectangle w10;
            extern Rectangle w11;
            extern Rectangle w12;
            extern std::vector<Rectangle> walk_;
        }
        namespace Climb
        {
            extern Rectangle c1;
            extern Rectangle c2;
            extern Rectangle c3;
            extern Rectangle c4;
            extern Rectangle c5;
            extern Rectangle c6;
            extern Rectangle c7;
            extern Rectangle c8;
            extern std::vector<Rectangle> climb_;
        }
        namespace Slide
        {
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            extern std::vector<Rectangle> slide_;
        }
        namespace Small_To_Super
        {
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            extern Rectangle s5;
            extern Rectangle s6;
            extern Rectangle s7;
            extern Rectangle s8;
            extern Rectangle s9;
            extern Rectangle s10;
            extern Rectangle s11;
            extern Rectangle s12;
            extern Rectangle s13;
            // x2
            extern Rectangle s14;
            extern Rectangle s15;
            extern Rectangle s16;
            extern Rectangle s17;
            //
            extern std::vector<Rectangle> small_to_super;
        }
    }

    namespace Super
    {
        namespace Stance
        {
            extern Rectangle stance;
            extern std::vector<Rectangle> stance_;
        }
        namespace Stance_To_Fire
        {
            // x3
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            //
            extern std::vector<Rectangle> stance_to_fire;
        }
        namespace Crouch
        {
            extern Rectangle crouch;
            extern std::vector<Rectangle> crouch_;
        }
        namespace Crouch_To_Fire
        {
            // x3
            extern Rectangle c1;
            extern Rectangle c2;
            extern Rectangle c3;
            extern Rectangle c4;
            //
            extern std::vector<Rectangle> crouch_to_fire;
        }
        namespace Jump
        {
            extern Rectangle jump;
            extern std::vector<Rectangle> jump_;
        }
        namespace Jump_To_Fire
        {
            // x3
            extern Rectangle j1;
            extern Rectangle j2;
            extern Rectangle j3;
            extern Rectangle j4;
            //
            extern std::vector<Rectangle> jump_to_fire;
        }
        namespace Walk
        {
            extern Rectangle w1;
            extern Rectangle w2;
            extern Rectangle w3;
            extern std::vector<Rectangle> walk_;
        }
        namespace Walk_To_Fire
        {
            // x3
            extern Rectangle w1;
            extern Rectangle w2;
            extern Rectangle w3;
            extern Rectangle w4;
            //
            extern std::vector<Rectangle> walk_to_fire;
        }
        namespace Slide
        {
            extern Rectangle slide;
            extern std::vector<Rectangle> slide_;
        }
        namespace Slide_To_Fire
        {
            // x3
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            //
            extern std::vector<Rectangle> slide_to_fire;
        }
        namespace Climb
        {
            extern Rectangle c1;
            extern Rectangle c2;
            extern std::vector<Rectangle> climb_;
        }
        namespace Hit
        {
            extern Rectangle h1;
            extern Rectangle h2;
            // x6
            extern Rectangle h3;
            extern Rectangle h4;
            //
            extern Rectangle h5;
            extern std::vector<Rectangle> hit_;
        }
    }

    namespace Invincible_Super
    {
        namespace Stance
        {
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            extern std::vector<Rectangle> stance_;
        }
        namespace Jump
        {
            extern Rectangle j1;
            extern Rectangle j2;
            extern Rectangle j3;
            extern Rectangle j4;
            extern std::vector<Rectangle> jump_;
        }
        namespace Crouch
        {
            extern Rectangle c1;
            extern Rectangle c2;
            extern Rectangle c3;
            extern Rectangle c4;
            extern std::vector<Rectangle> crouch_;
        }
        namespace Slide
        {
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            extern std::vector<Rectangle> slide_;
        }
        namespace Climb
        {
            extern Rectangle c1;
            extern Rectangle c2;
            extern Rectangle c3;
            extern Rectangle c4;
            extern Rectangle c5;
            extern Rectangle c6;
            extern Rectangle c7;
            extern Rectangle c8;
            extern std::vector<Rectangle> climb_;
        }
        namespace Shoot_Fire
        {
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            extern std::vector<Rectangle> shoot_fire;
        }
        namespace Walk
        {
            extern Rectangle w1;
            extern Rectangle w2;
            extern Rectangle w3;
            extern Rectangle w4;
            extern Rectangle w5;
            extern Rectangle w6;
            extern Rectangle w7;
            extern Rectangle w8;
            extern Rectangle w9;
            extern Rectangle w10;
            extern Rectangle w11;
            extern Rectangle w12;
            extern std::vector<Rectangle> walk_;
        }
    }

    namespace Fire
    {
        namespace Stance
        {
            extern Rectangle stance;
            extern std::vector<Rectangle> stance_;
        }
        namespace Crouch
        {
            extern Rectangle crouch;
            extern std::vector<Rectangle> crouch_;
        }
        namespace Jump
        {
            extern Rectangle jump;
            extern std::vector<Rectangle> jump_;
        }
        namespace Walk
        {
            extern Rectangle w1;
            extern Rectangle w2;
            extern Rectangle w3;
            extern std::vector<Rectangle> walk_;
        }
        namespace Slide
        {
            extern Rectangle slide;
            extern std::vector<Rectangle> slide_;
        }
        namespace Climb
        {
            extern Rectangle c1;
            extern Rectangle c2;
            extern std::vector<Rectangle> climb_;
        }
        namespace Shoot
        {
            extern Rectangle shoot;
            extern std::vector<Rectangle> shoot_;
        }
        namespace Hit
        {
            extern Rectangle h1;
            extern Rectangle h2;
            // x6
            extern Rectangle h3;
            extern Rectangle h4;
            //
            extern Rectangle h5;
            extern std::vector<Rectangle> hit_;
        }
    }
}
