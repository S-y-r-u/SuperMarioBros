#pragma once
#include "raylib.h"
#include <vector>
#include <string>

struct SpriteSheet
{
    Texture2D sprite;
    Image image;
    Color *pixel = nullptr;
    void Load_(const char *path);
    void Unload_();
    Color Get_Pixel(int x, int y) const;
};

// Mario.png
namespace Mario_Sprite
{
    extern SpriteSheet mario_sprite;

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
        namespace Enter_Pipe
        {
            extern Rectangle enter;
            extern std::vector<Rectangle> enter_pipe;
        }
        namespace Fade_Out
        {
            extern Rectangle f1;
            extern Rectangle f2;
            extern Rectangle f3;
            extern Rectangle f4;
            extern Rectangle f5;
            extern Rectangle f6;
            extern Rectangle f7;
            extern Rectangle f8;
            extern Rectangle f9;
            extern Rectangle f10;
            extern Rectangle f11;
            extern Rectangle f12;
            extern Rectangle f13;
            extern Rectangle f14;
            extern std::vector<Rectangle> fade_out;
        }
        namespace Small_To_Super
        {
            // x3
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            extern Rectangle s5;
            extern Rectangle s6;
            //
            extern Rectangle s7;
            extern Rectangle s8;
            extern Rectangle s9;
            extern Rectangle s10;
            extern std::vector<Rectangle> small_to_super;
        }
        namespace Pose
        {
            extern Rectangle p1;
            extern Rectangle p2;
            extern std::vector<Rectangle> pose;
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
            extern Rectangle w13;
            extern Rectangle w14;
            extern Rectangle w15;
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
        namespace Enter_Pipe
        {
            extern Rectangle e1;
            extern Rectangle e2;
            extern Rectangle e3;
            extern Rectangle e4;
            extern std::vector<Rectangle> enter_pipe;
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
        namespace Pose
        {
            extern Rectangle p1;
            extern Rectangle p2;
            extern Rectangle p3;
            extern Rectangle p4;
            extern Rectangle p5;
            extern Rectangle p6;
            extern Rectangle p7;
            extern Rectangle p8;
            extern std::vector<Rectangle> pose;
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
            extern Rectangle s5;
            extern Rectangle s6;
            extern Rectangle s7;
            extern Rectangle s8;
            extern Rectangle s9;
            extern Rectangle s10;
            extern Rectangle s11;
            extern Rectangle s12;
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
            extern Rectangle c5;
            extern Rectangle c6;
            extern Rectangle c7;
            extern Rectangle c8;
            extern Rectangle c9;
            extern Rectangle c10;
            extern Rectangle c11;
            extern Rectangle c12;
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
            extern Rectangle j5;
            extern Rectangle j6;
            extern Rectangle j7;
            extern Rectangle j8;
            extern Rectangle j9;
            extern Rectangle j10;
            extern Rectangle j11;
            extern Rectangle j12;
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
            extern Rectangle w5;
            extern Rectangle w6;
            extern Rectangle w7;
            extern Rectangle w8;
            extern Rectangle w9;
            extern Rectangle w10;
            extern Rectangle w11;
            extern Rectangle w12;
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
            extern Rectangle s5;
            extern Rectangle s6;
            extern Rectangle s7;
            extern Rectangle s8;
            extern Rectangle s9;
            extern Rectangle s10;
            extern Rectangle s11;
            extern Rectangle s12;
            //
            extern std::vector<Rectangle> slide_to_fire;
        }
        namespace Climb
        {
            extern Rectangle c1;
            extern Rectangle c2;
            extern std::vector<Rectangle> climb_;
        }
        namespace Enter_Pipe
        {
            extern Rectangle enter;
            extern std::vector<Rectangle> enter_pipe;
        }
        namespace Fade_Out
        {
            extern Rectangle f1;
            extern Rectangle f2;
            extern Rectangle f3;
            extern Rectangle f4;
            extern Rectangle f5;
            extern Rectangle f6;
            extern Rectangle f7;
            extern Rectangle f8;
            extern Rectangle f9;
            extern Rectangle f10;
            extern Rectangle f11;
            extern Rectangle f12;
            extern Rectangle f13;
            extern Rectangle f14;
            extern std::vector<Rectangle> fade_out;
        }
        namespace Hit
        {
            extern Rectangle h1;
            extern Rectangle h2;
            // x6
            extern Rectangle h3;
            extern Rectangle h4;
            extern Rectangle h5;
            extern Rectangle h6;
            extern Rectangle h7;
            extern Rectangle h8;
            extern Rectangle h9;
            extern Rectangle h10;
            extern Rectangle h10;
            extern Rectangle h11;
            //
            extern Rectangle h12;
            extern std::vector<Rectangle> hit_;
        }
        namespace Pose
        {
            extern Rectangle p1;
            extern Rectangle p2;
            extern std::vector<Rectangle> pose;
        }
    }

    namespace Invincible_Super_And_Fire
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
            extern Rectangle w13;
            extern Rectangle w14;
            extern Rectangle w15;
            extern std::vector<Rectangle> walk_;
        }
        namespace Enter_Pipe
        {
            extern Rectangle e1;
            extern Rectangle e2;
            extern Rectangle e3;
            extern Rectangle e4;
            extern std::vector<Rectangle> enter_pipe;
        }
        namespace Pose
        {
            extern Rectangle p1;
            extern Rectangle p2;
            extern Rectangle p3;
            extern Rectangle p4;
            extern Rectangle p5;
            extern Rectangle p6;
            extern Rectangle p7;
            extern Rectangle p8;
            extern std::vector<Rectangle> pose;
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
        namespace Enter_Pipe
        {
            extern Rectangle enter;
            extern std::vector<Rectangle> enter_pipe;
        }
        namespace Fade_Out
        {
            extern Rectangle f1;
            extern Rectangle f2;
            extern Rectangle f3;
            extern Rectangle f4;
            extern Rectangle f5;
            extern Rectangle f6;
            extern Rectangle f7;
            extern Rectangle f8;
            extern Rectangle f9;
            extern Rectangle f10;
            extern Rectangle f11;
            extern Rectangle f12;
            extern Rectangle f13;
            extern Rectangle f14;
            extern std::vector<Rectangle> fade_out;
        }
        namespace Hit
        {
            extern Rectangle h1;
            extern Rectangle h2;
            // x6
            extern Rectangle h3;
            extern Rectangle h4;
            extern Rectangle h5;
            extern Rectangle h6;
            extern Rectangle h7;
            extern Rectangle h8;
            extern Rectangle h9;
            extern Rectangle h10;
            extern Rectangle h11;
            extern Rectangle h12;
            //
            extern Rectangle h13;
            extern std::vector<Rectangle> hit_;
        }
        namespace Pose
        {
            extern Rectangle p1;
            extern Rectangle p2;
            extern std::vector<Rectangle> pose;
        }
    }
}

// Luigi.png
namespace Luigi_Sprite
{
    extern SpriteSheet luigi_sprite;

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
        namespace Enter_Pipe
        {
            extern Rectangle enter;
            extern std::vector<Rectangle> enter_pipe;
        }
        namespace Fade_Out
        {
            extern Rectangle f1;
            extern Rectangle f2;
            extern Rectangle f3;
            extern Rectangle f4;
            extern Rectangle f5;
            extern Rectangle f6;
            extern Rectangle f7;
            extern Rectangle f8;
            extern Rectangle f9;
            extern Rectangle f10;
            extern Rectangle f11;
            extern Rectangle f12;
            extern Rectangle f13;
            extern Rectangle f14;
            extern std::vector<Rectangle> fade_out;
        }
        namespace Small_To_Super
        {
            // x3
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            extern Rectangle s5;
            extern Rectangle s6;
            //
            extern Rectangle s7;
            extern Rectangle s8;
            extern Rectangle s9;
            extern Rectangle s10;
            extern std::vector<Rectangle> small_to_super;
        }
        namespace Pose
        {
            extern Rectangle p1;
            extern Rectangle p2;
            extern std::vector<Rectangle> pose;
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
            extern Rectangle w13;
            extern Rectangle w14;
            extern Rectangle w15;
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
        namespace Enter_Pipe
        {
            extern Rectangle e1;
            extern Rectangle e2;
            extern Rectangle e3;
            extern Rectangle e4;
            extern std::vector<Rectangle> enter_pipe;
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
            //
            extern std::vector<Rectangle> small_to_super;
        }
        namespace Pose
        {
            extern Rectangle p1;
            extern Rectangle p2;
            extern Rectangle p3;
            extern Rectangle p4;
            extern Rectangle p5;
            extern Rectangle p6;
            extern Rectangle p7;
            extern Rectangle p8;
            extern std::vector<Rectangle> pose;
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
            extern Rectangle s5;
            extern Rectangle s6;
            extern Rectangle s7;
            extern Rectangle s8;
            extern Rectangle s9;
            extern Rectangle s10;
            extern Rectangle s11;
            extern Rectangle s12;
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
            extern Rectangle c5;
            extern Rectangle c6;
            extern Rectangle c7;
            extern Rectangle c8;
            extern Rectangle c9;
            extern Rectangle c10;
            extern Rectangle c11;
            extern Rectangle c12;
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
            extern Rectangle j5;
            extern Rectangle j6;
            extern Rectangle j7;
            extern Rectangle j8;
            extern Rectangle j9;
            extern Rectangle j10;
            extern Rectangle j11;
            extern Rectangle j12;
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
            extern Rectangle w5;
            extern Rectangle w6;
            extern Rectangle w7;
            extern Rectangle w8;
            extern Rectangle w9;
            extern Rectangle w10;
            extern Rectangle w11;
            extern Rectangle w12;
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
            extern Rectangle s5;
            extern Rectangle s6;
            extern Rectangle s7;
            extern Rectangle s8;
            extern Rectangle s9;
            extern Rectangle s10;
            extern Rectangle s11;
            extern Rectangle s12;
            //
            extern std::vector<Rectangle> slide_to_fire;
        }
        namespace Climb
        {
            extern Rectangle c1;
            extern Rectangle c2;
            extern std::vector<Rectangle> climb_;
        }
        namespace Enter_Pipe
        {
            extern Rectangle enter;
            extern std::vector<Rectangle> enter_pipe;
        }
        namespace Fade_Out
        {
            extern Rectangle f1;
            extern Rectangle f2;
            extern Rectangle f3;
            extern Rectangle f4;
            extern Rectangle f5;
            extern Rectangle f6;
            extern Rectangle f7;
            extern Rectangle f8;
            extern Rectangle f9;
            extern Rectangle f10;
            extern Rectangle f11;
            extern Rectangle f12;
            extern Rectangle f13;
            extern Rectangle f14;
            extern std::vector<Rectangle> fade_out;
        }
        namespace Hit
        {
            extern Rectangle h1;
            extern Rectangle h2;
            // x6
            extern Rectangle h3;
            extern Rectangle h4;
            extern Rectangle h5;
            extern Rectangle h6;
            extern Rectangle h7;
            extern Rectangle h8;
            extern Rectangle h9;
            extern Rectangle h10;
            extern Rectangle h11;
            extern Rectangle h12;
            //
            extern Rectangle h13;
            extern std::vector<Rectangle> hit_;
        }
        namespace Pose
        {
            extern Rectangle p1;
            extern Rectangle p2;
            extern std::vector<Rectangle> pose;
        }
    }

    namespace Invincible_Super_And_Fire
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
            extern Rectangle w13;
            extern Rectangle w14;
            extern Rectangle w15;
            extern std::vector<Rectangle> walk_;
        }
        namespace Enter_Pipe
        {
            extern Rectangle e1;
            extern Rectangle e2;
            extern Rectangle e3;
            extern Rectangle e4;
            extern std::vector<Rectangle> enter_pipe;
        }
        namespace Pose
        {
            extern Rectangle p1;
            extern Rectangle p2;
            extern Rectangle p3;
            extern Rectangle p4;
            extern Rectangle p5;
            extern Rectangle p6;
            extern Rectangle p7;
            extern Rectangle p8;
            extern std::vector<Rectangle> pose;
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
        namespace Enter_Pipe
        {
            extern Rectangle enter;
            extern std::vector<Rectangle> enter_pipe;
        }
        namespace Fade_Out
        {
            extern Rectangle f1;
            extern Rectangle f2;
            extern Rectangle f3;
            extern Rectangle f4;
            extern Rectangle f5;
            extern Rectangle f6;
            extern Rectangle f7;
            extern Rectangle f8;
            extern Rectangle f9;
            extern Rectangle f10;
            extern Rectangle f11;
            extern Rectangle f12;
            extern Rectangle f13;
            extern Rectangle f14;
            extern std::vector<Rectangle> fade_out;
        }
        namespace Hit
        {
            extern Rectangle h1;
            extern Rectangle h2;
            // x6
            extern Rectangle h3;
            extern Rectangle h4;
            extern Rectangle h5;
            extern Rectangle h6;
            extern Rectangle h7;
            extern Rectangle h8;
            extern Rectangle h9;
            extern Rectangle h10;
            extern Rectangle h11;
            extern Rectangle h12;
            //
            extern Rectangle h13;
            extern std::vector<Rectangle> hit_;
        }
        namespace Pose
        {
            extern Rectangle p1;
            extern Rectangle p2;
            extern std::vector<Rectangle> pose;
        }
    }
}

// Items_Blocks.png
namespace Item_Sprite
{
    extern SpriteSheet item_;

    namespace Mushroom
    {
        // Thành super
        extern Rectangle super_mushroom;
        // Tăng 1 mạng
        extern Rectangle one_up_mushroom;
        // Mất 1 mạng
        extern Rectangle posion_mushroom;
    }

    namespace Flower
    {
        // Thành fire
        extern Rectangle fire_flower;
    }

    namespace Star
    {
        // Thành invincible
        extern Rectangle invincible_star;
    }

    namespace Coin
    {
        // coin bình thường
        namespace Blinking
        {
            extern Rectangle b1;
            extern Rectangle b2;
            extern Rectangle b3;
            extern std::vector<Rectangle> blinking_;
        }

        // coin đập gạch
        namespace Hidden
        {
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            // hiệu ứng biến mất
            extern Rectangle s5;
            extern Rectangle s6;
            extern Rectangle s7;
            extern Rectangle s8;
            extern Rectangle s9;
            extern std::vector<Rectangle> hidden_;
        }
    }

    namespace Fire_Ball
    {
        namespace Fly
        {
            extern Rectangle f1;
            extern Rectangle f2;
            extern Rectangle f3;
            extern Rectangle f4;
            extern std::vector<Rectangle> fly_;
        }

        // Hiệu ứng khi nổ
        namespace Explode
        {
            extern Rectangle e1;
            extern Rectangle e2;
            extern Rectangle e3;
            extern std::vector<Rectangle> explode_;
        }
    }

    namespace Question_Brick
    {
        // Hiệu ứng
        extern Rectangle q1;
        extern Rectangle q2;
        extern Rectangle q3;
        extern std::vector<Rectangle> question_;
    }

    namespace Brown_Brick
    {
        extern Rectangle type_1;
        extern Rectangle type_2;
        extern Rectangle type_3;
        extern Rectangle break_;
    }

    namespace Blue_Brick
    {
        extern Rectangle type_1;
        extern Rectangle type_2;
        extern Rectangle type_3;
        extern Rectangle break_;
    }

    namespace Gray_Brick
    {
        extern Rectangle type_1;
        extern Rectangle type_2;
        extern Rectangle type_3;
        extern Rectangle break_;
    }
}

// Font.png
namespace Font_Sprite
{
    extern SpriteSheet font_;

    namespace Number
    {
        extern Rectangle n0;
        extern Rectangle n1;
        extern Rectangle n2;
        extern Rectangle n3;
        extern Rectangle n4;
        extern Rectangle n5;
        extern Rectangle n6;
        extern Rectangle n7;
        extern Rectangle n8;
        extern Rectangle n9;
        extern std::vector<Rectangle> num;
    }

    namespace Character
    {
        extern Rectangle A;
        extern Rectangle B;
        extern Rectangle C;
        extern Rectangle D;
        extern Rectangle E;
        extern Rectangle F;
        extern Rectangle G;
        extern Rectangle H;
        extern Rectangle I;
        extern Rectangle J;
        extern Rectangle K;
        extern Rectangle L;
        extern Rectangle M;
        extern Rectangle N;
        extern Rectangle O;
        extern Rectangle P;
        extern Rectangle Q;
        extern Rectangle R;
        extern Rectangle S;
        extern Rectangle T;
        extern Rectangle U;
        extern Rectangle V;
        extern Rectangle W;
        extern Rectangle X;
        extern Rectangle Y;
        extern Rectangle Z;
        extern std::vector<Rectangle> character;
    }

    void DrawText(std::string s, float x, float y, Color color, float scale = 3.0f);

    // Coin frame
    namespace Coin
    {
        extern Rectangle c1;
        extern Rectangle c2;
        extern Rectangle c3;
        extern std::vector<Rectangle> coin;
    }

    namespace Heart
    {
        // còn mạng
        extern Rectangle color;
        // không còn mạng
        extern Rectangle not_color;
    }

    // Dấu x
    namespace X
    {
        extern Rectangle x;
    }

    // Dấu " - "
    namespace Hyphen
    {
        extern Rectangle hyphen;
    }

    namespace Clock
    {
        extern Rectangle clock;
    }
    namespace Percent
    {
        extern Rectangle percent;
    }
}

// GameOver_TimeUp.png
namespace Screen_Sprite
{
    extern SpriteSheet screen_;

    extern Rectangle mario_word;
    extern Rectangle luigi_word;
    extern Rectangle world_word;
    extern Rectangle time_word;
    extern Rectangle game_over_word;
    extern Rectangle time_up_word;
    extern Rectangle arrow_;
    extern Rectangle continue_word;
    extern Rectangle save_and_continue_word;
    extern Rectangle save_and_quit_word;
}

// Enemies.png
namespace Enemies_Sprite
{
    extern SpriteSheet enemies_;

    // Nấm độc
    namespace Goomba_Brown
    {
        // Move
        namespace Normal
        {
            extern Rectangle n1;
            extern Rectangle n2;
            extern std::vector<Rectangle> normal_;
        }

        extern Rectangle be_stomped;
        extern Rectangle be_fired_or_hit;
    }

    namespace Goomba_Blue
    {
        // Move
        namespace Normal
        {
            extern Rectangle n1;
            extern Rectangle n2;
            extern std::vector<Rectangle> normal_;
        }

        extern Rectangle be_stomped;
        extern Rectangle be_fired_or_hit;
    }

    namespace Goomba_Gray
    {
        // Move
        namespace Normal
        {
            extern Rectangle n1;
            extern Rectangle n2;
            extern std::vector<Rectangle> normal_;
        }

        extern Rectangle be_stomped;
        extern Rectangle be_fired_or_hit;
    }

    namespace Piranha_Plant_Green
    {
        extern Rectangle p1;
        extern Rectangle p2;
        extern std::vector<Rectangle> plant_;
    }

    namespace Piranha_Plant_Red
    {
        extern Rectangle p1;
        extern Rectangle p2;
        extern std::vector<Rectangle> plant_;
    }

    namespace Buzzy_Beetle
    {
        namespace Normal
        {
            extern Rectangle n1;
            extern Rectangle n2;
            extern std::vector<Rectangle> normal;
        }

        extern Rectangle be_stomped;

        namespace Be_Kicked
        {
            extern Rectangle s1;
            extern Rectangle s2;
            extern Rectangle s3;
            extern Rectangle s4;
            extern std::vector<Rectangle> be_kicked;
        }
    }

    namespace Troopa_Red
    {
        namespace Normal
        {
            extern Rectangle n1;
            extern Rectangle n2;
            extern std::vector<Rectangle> normal_;
        }

        namespace Be_Kicked
        {
            extern Rectangle k1;
            extern Rectangle k2;
            extern Rectangle k3;
            extern Rectangle k4;
            extern std::vector<Rectangle> be_kicked;
        }

        extern Rectangle be_stomped;
        extern Rectangle be_fired_or_hit;
    }

    namespace Troopa_Green
    {
        namespace Normal
        {
            extern Rectangle n1;
            extern Rectangle n2;
            extern std::vector<Rectangle> normal_;
        }

        namespace Shell_Idle
        {
            extern Rectangle k1;
            extern Rectangle k2;
            extern std::vector<Rectangle> shell_idle;
        }

        namespace Shell_Moving
        {
            extern Rectangle k1;
            extern Rectangle k2;
            extern Rectangle k3;
            extern std::vector<Rectangle> shell_moving;
        }
        namespace Flying
        {
            extern Rectangle f1;
            extern Rectangle f2;
            extern std::vector<Rectangle> flying_;
        }

        extern Rectangle be_dying;
    }

    namespace Latiku
    {
        extern Rectangle fly_;
        extern Rectangle throw_;
        extern Rectangle be_fired;
    }

    namespace Spiny
    {
        namespace Egg
        {
            extern Rectangle e1;
            extern Rectangle e2;
            extern std::vector<Rectangle> egg_;
        }

        namespace Normal
        {
            extern Rectangle n1;
            extern Rectangle n2;
            extern std::vector<Rectangle> normal_;
        }

        extern Rectangle be_fired_or_hit;
    }
}

namespace BomberBill_Sprite
{
    extern SpriteSheet bomber_bill_;

    extern Rectangle n1;
    extern Rectangle n2;
    extern Rectangle n3;
    extern Rectangle n4;
    extern Rectangle n5;
    extern Rectangle n6;
    extern Rectangle n7;
    extern Rectangle n8;
    extern std::vector<Rectangle> bomber_bill_normal;
}

namespace Win_Animation
{
    extern SpriteSheet win_animation_;

    namespace flag_castle_2_side
    {
        extern Rectangle f1;
        extern Rectangle f2;
        extern Rectangle f3;
        extern std::vector<Rectangle> flag_castle_;
    }
    namespace flag_castle_top
    {
        extern Rectangle f1;
        extern Rectangle f2;
        extern Rectangle f3;
        extern Rectangle f4;
        extern std::vector<Rectangle> flag_castle_top_;
    }
    namespace flag_pole
    {
        extern Rectangle f1;
        extern Rectangle f2;
        extern Rectangle f3;
        extern std::vector<Rectangle> flag_pole_;
    }
}