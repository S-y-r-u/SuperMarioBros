#include "sprite.h"

void SpriteSheet::Load_(const char *path)
{
    image = LoadImage(path);
    sprite = LoadTextureFromImage(image);
    pixel = LoadImageColors(image);
}

void SpriteSheet::Unload_()
{
    if (pixel)
        UnloadImageColors(pixel);
    UnloadImage(image);
    UnloadTexture(sprite);
}

Color SpriteSheet::Get_Pixel(int x, int y) const
{
    if (x < 0 || y < 0 || x >= image.width || y >= image.height)
        return BLANK;
    return pixel[y * image.width + x];
}

namespace Mario
{
    SpriteSheet mario_sprite;

    namespace Small
    {
        namespace Stance
        {
            Rectangle stance = {7, 51, 12, 15};
            std::vector<Rectangle> stance_ = {stance};
        }
        namespace Jump
        {
            Rectangle jump = {49, 50, 16, 16};
            std::vector<Rectangle> jump_ = {jump};
        }
        namespace Die
        {
            Rectangle die = {93, 50, 16, 16};
            std::vector<Rectangle> die_ = {die};
        }
        namespace Walk
        {
            Rectangle w1 = {7, 93, 12, 15};
            Rectangle w2 = {28, 93, 12, 15};
            Rectangle w3 = {47, 92, 15, 16};
            std::vector<Rectangle> walk_ = {w1, w2, w3};
        }
        namespace Slide
        {
            Rectangle slide = {134, 134, 14, 16};
            std::vector<Rectangle> slide_ = {slide};
        }
        namespace Climb
        {
            Rectangle c1 = {6, 176, 13, 16};
            Rectangle c2 = {28, 176, 13, 15};
            std::vector<Rectangle> climb_ = {c1, c2};
        }
        namespace Enter_Pipe
        {
            Rectangle enter = {90, 176, 16, 16};
            std::vector<Rectangle> enter_pipe = {enter};
        }
        namespace Fade_Out
        {
            Rectangle f1 = {5, 224, 15, 16};
            Rectangle f2 = {27, 224, 15, 16};
            Rectangle f3 = {49, 225, 12, 15};
            Rectangle f4 = {70, 225, 12, 15};
            Rectangle f5 = {91, 225, 12, 15};
            Rectangle f6 = {112, 225, 12, 15};
            Rectangle f7 = {133, 225, 12, 15};
            Rectangle f8 = {175, 225, 12, 15};
            Rectangle f9 = {194, 224, 15, 16};
            Rectangle f10 = {215, 224, 15, 16};
            Rectangle f11 = {236, 224, 15, 16};
            Rectangle f12 = {257, 224, 15, 16};
            Rectangle f13 = {280, 225, 12, 15};
            Rectangle f14 = {301, 225, 12, 15};
            std::vector<Rectangle> fade_out = {f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14};
        }
        namespace Small_To_Super
        {
            Rectangle s1 = {179, 152, 12, 15};
            Rectangle s2 = {199, 145, 14, 22};
            Rectangle s3 = {220, 137, 14, 30};
            Rectangle s4 = {242, 152, 12, 15};
            Rectangle s5 = {262, 145, 14, 22};
            Rectangle s6 = {283, 137, 14, 30};
            std::vector<Rectangle> small_to_super = {s1, s2, s3, s4, s5, s6};
        }
    }

    namespace Invincible
    {
        namespace Stance
        {
            Rectangle s1 = {7, 292, 12, 15};
            Rectangle s2 = {28, 292, 12, 15};
            Rectangle s3 = {49, 292, 12, 15};
            Rectangle s4 = {70, 292, 12, 15};
            std::vector<Rectangle> stance_ = {s1, s2, s3, s4};
        }
        namespace Jump
        {
            Rectangle j1 = {175, 291, 16, 16};
            Rectangle j2 = {196, 291, 16, 16};
            Rectangle j3 = {217, 291, 16, 16};
            Rectangle j4 = {238, 291, 16, 16};
            std::vector<Rectangle> jump_ = {j1, j2, j3, j4};
        }
        namespace Walk
        {
            Rectangle w1 = {7, 334, 12, 15};
            Rectangle w2 = {28, 334, 12, 15};
            Rectangle w3 = {47, 333, 15, 16};
            Rectangle w4 = {70, 334, 12, 15};
            Rectangle w5 = {91, 334, 12, 15};
            Rectangle w6 = {110, 333, 15, 16};
            Rectangle w7 = {133, 334, 12, 15};
            Rectangle w8 = {154, 334, 12, 15};
            Rectangle w9 = {173, 333, 15, 16};
            Rectangle w10 = {196, 334, 12, 15};
            Rectangle w11 = {217, 334, 12, 15};
            Rectangle w12 = {236, 333, 15, 16};
            Rectangle w13 = {259, 334, 12, 15};
            Rectangle w14 = {280, 334, 12, 15};
            Rectangle w15 = {299, 332, 15, 16};
            std::vector<Rectangle> walk_ = {w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13, w14};
        }
        namespace Climb
        {
            Rectangle c1 = {7, 490, 13, 16};
            Rectangle c2 = {28, 490, 13, 15};
            Rectangle c3 = {49, 490, 13, 16};
            Rectangle c4 = {70, 490, 13, 15};
            Rectangle c5 = {91, 490, 13, 16};
            Rectangle c6 = {112, 490, 13, 15};
            Rectangle c7 = {133, 490, 13, 16};
            Rectangle c8 = {154, 490, 13, 15};
            std::vector<Rectangle> climb_ = {c1, c2, c3, c4, c5, c6, c7, c8};
        }
        namespace Slide
        {
            Rectangle s1 = {364, 448, 14, 16};
            Rectangle s2 = {386, 448, 14, 16};
            Rectangle s3 = {407, 448, 14, 16};
            Rectangle s4 = {428, 448, 14, 16};
            std::vector<Rectangle> slide_ = {s1, s2, s3, s4};
        }
        namespace Enter_Pipe
        {
            Rectangle e1 = {344, 291, 16, 16};
            Rectangle e2 = {365, 291, 16, 16};
            Rectangle e3 = {386, 291, 16, 16};
            Rectangle e4 = {407, 291, 16, 16};
            std::vector<Rectangle> enter_pipe = {e1, e2, e3, e4};
        }
        namespace Small_To_Super
        {
            Rectangle s1 = {7, 417, 12, 15};
            Rectangle s2 = {28, 417, 12, 15};
            Rectangle s3 = {49, 417, 12, 15};
            Rectangle s4 = {69, 410, 14, 22};
            Rectangle s5 = {91, 417, 12, 15};
            Rectangle s6 = {111, 410, 14, 22};
            Rectangle s7 = {133, 417, 12, 15};
            Rectangle s8 = {153, 410, 14, 22};
            Rectangle s9 = {174, 402, 14, 30};
            Rectangle s10 = {196, 417, 12, 15};
            Rectangle s11 = {216, 410, 14, 22};
            Rectangle s12 = {237, 402, 14, 30};
            Rectangle s13 = {259, 417, 12, 15};
            Rectangle s14 = {279, 402, 14, 30};
            Rectangle s15 = {300, 402, 14, 30};
            Rectangle s16 = {321, 402, 14, 30};
            Rectangle s17 = {342, 402, 14, 30};
            std::vector<Rectangle> small_to_super = {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16, s17};
        }
    }

    namespace Super
    {
        namespace Stance
        {
            Rectangle stance = {386, 36, 14, 30};
            std::vector<Rectangle> stance_ = {stance};
        }
        namespace Stance_To_Fire
        {
            Rectangle s1 = {793, 214, 14, 30};
            Rectangle s2 = {814, 214, 14, 30};
            Rectangle s3 = {835, 214, 14, 30};
            Rectangle s4 = {856, 214, 14, 30};
            std::vector<Rectangle> stance_to_fire = {s1, s2, s3, s4};
        }
        namespace Crouch
        {
            Rectangle crouch = {429, 44, 16, 22};
            std::vector<Rectangle> crouch_ = {crouch};
        }
        namespace Crouch_To_Fire
        {
            Rectangle c1 = {1148, 256, 16, 22};
            Rectangle c2 = {1169, 256, 16, 22};
            Rectangle c3 = {1190, 256, 16, 22};
            Rectangle c4 = {1211, 256, 16, 22};
            std::vector<Rectangle> crouch_to_fire = {c1, c2, c3, c4};
        }
        namespace Jump
        {
            Rectangle jump = {478, 35, 16, 30};
            std::vector<Rectangle> jump_ = {jump};
        }
        namespace Jump_To_Fire
        {
            Rectangle j1 = {792, 247, 16, 30};
            Rectangle j2 = {813, 247, 16, 30};
            Rectangle j3 = {834, 247, 16, 30};
            Rectangle j4 = {855, 247, 16, 30};
            std::vector<Rectangle> jump_to_fire = {j1, j2, j3, j4};
        }
        namespace Walk
        {
            Rectangle w1 = {386, 78, 14, 30};
            Rectangle w2 = {406, 78, 16, 29};
            Rectangle w3 = {427, 78, 16, 30};
            std::vector<Rectangle> walk_ = {w1, w2, w3};
        }
        namespace Walk_To_Fire
        {
            Rectangle w1 = {970, 214, 16, 29};
            Rectangle w2 = {991, 214, 16, 29};
            Rectangle w3 = {1012, 214, 16, 29};
            Rectangle w4 = {1033, 214, 16, 29};
            std::vector<Rectangle> walk_to_fire = {w1, w2, w3, w4};
        }
        namespace Slide
        {
            Rectangle slide = {522, 35, 16, 31};
            std::vector<Rectangle> slide_ = {slide};
        }
        namespace Slide_To_Fire
        {
            Rectangle s1 = {970, 247, 16, 31};
            Rectangle s2 = {991, 247, 16, 31};
            Rectangle s3 = {1012, 247, 16, 31};
            Rectangle s4 = {1033, 247, 16, 31};
            std::vector<Rectangle> slide_to_fire = {s1, s2, s3, s4};
        }
        namespace Climb
        {
            Rectangle c1 = {430, 121, 14, 28};
            Rectangle c2 = {451, 121, 14, 26};
            std::vector<Rectangle> climb_ = {c1, c2};
        }
        namespace Enter_Pipe
        {
            Rectangle enter = {515, 121, 16, 30};
            std::vector<Rectangle> enter_pipe = {enter};
        }
        namespace Fade_Out
        {
            Rectangle f1 = {385, 205, 16, 29};
            Rectangle f2 = {406, 205, 16, 30};
            Rectangle f3 = {427, 205, 16, 30};
            Rectangle f4 = {449, 205, 14, 30};
            Rectangle f5 = {470, 205, 14, 30};
            Rectangle f6 = {491, 205, 14, 30};
            Rectangle f7 = {511, 205, 16, 29};
            Rectangle f8 = {532, 205, 16, 29};
            Rectangle f9 = {553, 205, 16, 29};
            Rectangle f10 = {574, 205, 16, 29};
            Rectangle f11 = {595, 205, 16, 30};
            Rectangle f12 = {616, 205, 16, 30};
            Rectangle f13 = {659, 205, 14, 30};
            Rectangle f14 = {680, 205, 14, 30};
            std::vector<Rectangle> fade_out = {f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14};
        }
        namespace Hit
        {
            Rectangle h1 = {616, 132, 14, 30};
            Rectangle h2 = {636, 131, 16, 30};
            Rectangle h3 = {657, 135, 16, 27};
            Rectangle h4 = {678, 146, 16, 16};
            Rectangle h5 = {701, 147, 12, 15};
            std::vector<Rectangle> hit_ = {h1, h2, h3, h4, h5};
        }
    }

    namespace Invincible_Super_And_Fire
    {
        namespace Stance
        {
            Rectangle s1 = {558, 332, 14, 30};
            Rectangle s2 = {579, 332, 14, 30};
            Rectangle s3 = {600, 332, 14, 30};
            Rectangle s4 = {621, 332, 14, 30};
            std::vector<Rectangle> stance_ = {s1, s2, s3, s4};
        }
        namespace Jump
        {
            Rectangle j1 = {727, 331, 16, 30};
            Rectangle j2 = {748, 331, 16, 30};
            Rectangle j3 = {769, 331, 16, 30};
            Rectangle j4 = {790, 331, 16, 30};
            std::vector<Rectangle> jump_ = {j1, j2, j3, j4};
        }
        namespace Crouch
        {
            Rectangle c1 = {727, 388, 16, 22};
            Rectangle c2 = {748, 388, 16, 22};
            Rectangle c3 = {769, 388, 16, 22};
            Rectangle c4 = {790, 388, 16, 22};
            std::vector<Rectangle> crouch_ = {c1, c2, c3, c4};
        }
        namespace Slide
        {
            Rectangle s1 = {557, 479, 16, 31};
            Rectangle s2 = {578, 479, 16, 31};
            Rectangle s3 = {599, 479, 16, 31};
            Rectangle s4 = {620, 479, 16, 31};
            std::vector<Rectangle> slide_ = {s1, s2, s3, s4};
        }
        namespace Climb
        {
            Rectangle c1 = {727, 421, 16, 30};
            Rectangle c2 = {748, 421, 16, 28};
            Rectangle c3 = {769, 421, 16, 30};
            Rectangle c4 = {790, 421, 16, 28};
            Rectangle c5 = {811, 421, 16, 30};
            Rectangle c6 = {832, 421, 16, 28};
            Rectangle c7 = {853, 421, 16, 30};
            Rectangle c8 = {874, 421, 16, 28};
            std::vector<Rectangle> climb_ = {c1, c2, c3, c4, c5, c6, c7, c8};
        }
        namespace Shoot_Fire
        {
            Rectangle s1 = {727, 464, 15, 30};
            Rectangle s2 = {748, 464, 15, 30};
            Rectangle s3 = {769, 464, 15, 30};
            Rectangle s4 = {790, 464, 15, 30};
            std::vector<Rectangle> shoot_fire = {s1, s2, s3, s4};
        }
        namespace Walk
        {
            Rectangle w1 = {557, 374, 15, 30};
            Rectangle w2 = {578, 438, 16, 30};
            Rectangle w3 = {578, 406, 16, 29};
            Rectangle w4 = {600, 374, 14, 30};
            Rectangle w5 = {599, 438, 16, 30};
            Rectangle w6 = {620, 406, 16, 29};
            Rectangle w7 = {621, 374, 14, 30};
            Rectangle w8 = {557, 438, 16, 30};
            Rectangle w9 = {557, 406, 16, 29};
            Rectangle w10 = {579, 374, 14, 30};
            Rectangle w11 = {578, 438, 16, 30};
            Rectangle w12 = {599, 406, 16, 29};
            Rectangle w13 = {600, 374, 14, 30};
            Rectangle w14 = {620, 438, 16, 30};
            Rectangle w15 = {620, 406, 16, 29};
            std::vector<Rectangle> walk_ = {w1, w2, w3, w4, w5, w6, w7, w7, w9, w10, w11, w12, w13, w14, w15};
        }
        namespace Enter_Pipe
        {
            Rectangle e1 = {897, 332, 16, 30};
            Rectangle e2 = {918, 332, 16, 30};
            Rectangle e3 = {939, 332, 16, 30};
            Rectangle e4 = {960, 332, 16, 30};
            std::vector<Rectangle> enter_pipe = {e1, e2, e3, e4};
        }
    }

    namespace Fire
    {
        namespace Stance
        {
            Rectangle stance = {794, 36, 14, 30};
            std::vector<Rectangle> stance_ = {stance};
        }
        namespace Crouch
        {
            Rectangle crouch = {837, 44, 16, 22};
            std::vector<Rectangle> crouch_ = {crouch};
        }
        namespace Jump
        {
            Rectangle jump = {886, 35, 16, 30};
            std::vector<Rectangle> jump_ = {jump};
        }
        namespace Walk
        {
            Rectangle w1 = {794, 78, 14, 30};
            Rectangle w2 = {814, 78, 16, 29};
            Rectangle w3 = {835, 78, 16, 30};
            std::vector<Rectangle> walk_ = {w1, w2, w3};
        }
        namespace Slide
        {
            Rectangle slide = {930, 35, 16, 31};
            std::vector<Rectangle> slide_ = {slide};
        }
        namespace Climb
        {
            Rectangle c1 = {838, 121, 14, 28};
            Rectangle c2 = {859, 121, 14, 26};
            std::vector<Rectangle> climb_ = {c1, c2};
        }
        namespace Shoot
        {
            Rectangle shoot = {921, 78, 15, 30};
            std::vector<Rectangle> shoot_ = {shoot};
        }
        namespace Enter_Pipe
        {
            Rectangle enter = {923, 121, 16, 30};
            std::vector<Rectangle> enter_pipe = {enter};
        }
        namespace Fade_out
        {
            Rectangle f1 = {792, 290, 16, 29};
            Rectangle f2 = {813, 290, 16, 30};
            Rectangle f3 = {834, 290, 16, 30};
            Rectangle f4 = {856, 290, 14, 30};
            Rectangle f5 = {877, 290, 14, 30};
            Rectangle f6 = {898, 290, 14, 30};
            Rectangle f7 = {918, 290, 16, 29};
            Rectangle f8 = {939, 290, 16, 29};
            Rectangle f9 = {960, 290, 16, 29};
            Rectangle f10 = {981, 290, 16, 29};
            Rectangle f11 = {1002, 290, 16, 30};
            Rectangle f12 = {1023, 290, 16, 30};
            Rectangle f13 = {1066, 290, 14, 30};
            Rectangle f14 = {1087, 290, 14, 30};
            std::vector<Rectangle> fade_out = {f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14};
        }
        namespace Hit
        {
            Rectangle h1 = {971, 141, 14, 30};
            Rectangle h2 = {991, 140, 16, 30};
            Rectangle h3 = {1012, 144, 16, 27};
            Rectangle h4 = {1033, 155, 16, 16};
            Rectangle h5 = {1056, 156, 12, 15};
            std::vector<Rectangle> hit_ = {h1, h2, h3, h4, h5};
        }
    }
}

namespace Luigi
{
    SpriteSheet luigi_sprite;

    namespace Small
    {
        namespace Stance
        {
            Rectangle stance = {7, 51, 12, 15};
            std::vector<Rectangle> stance_ = {stance};
        }
        namespace Jump
        {
            Rectangle jump = {49, 50, 16, 16};
            std::vector<Rectangle> jump_ = {jump};
        }
        namespace Die
        {
            Rectangle die = {93, 50, 16, 16};
            std::vector<Rectangle> die_ = {die};
        }
        namespace Walk
        {
            Rectangle w1 = {7, 93, 12, 15};
            Rectangle w2 = {28, 93, 12, 15};
            Rectangle w3 = {47, 92, 15, 16};
            std::vector<Rectangle> walk_ = {w1, w2, w3};
        }
        namespace Slide
        {
            Rectangle slide = {134, 134, 14, 16};
            std::vector<Rectangle> slide_ = {slide};
        }
        namespace Climb
        {
            Rectangle c1 = {6, 176, 13, 16};
            Rectangle c2 = {28, 176, 13, 15};
            std::vector<Rectangle> climb_ = {c1, c2};
        }
        namespace Enter_Pipe
        {
            Rectangle enter = {90, 176, 16, 16};
            std::vector<Rectangle> enter_pipe = {enter};
        }
        namespace Fade_Out
        {
            Rectangle f1 = {5, 224, 15, 16};
            Rectangle f2 = {27, 224, 15, 16};
            Rectangle f3 = {49, 225, 12, 15};
            Rectangle f4 = {70, 225, 12, 15};
            Rectangle f5 = {91, 225, 12, 15};
            Rectangle f6 = {112, 225, 12, 15};
            Rectangle f7 = {133, 225, 12, 15};
            Rectangle f8 = {175, 225, 12, 15};
            Rectangle f9 = {194, 224, 15, 16};
            Rectangle f10 = {215, 224, 15, 16};
            Rectangle f11 = {236, 224, 15, 16};
            Rectangle f12 = {257, 224, 15, 16};
            Rectangle f13 = {280, 225, 12, 15};
            Rectangle f14 = {301, 225, 12, 15};
            std::vector<Rectangle> fade_out = {f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14};
        }
        namespace Small_To_Super
        {
            Rectangle s1 = {179, 152, 12, 15};
            Rectangle s2 = {199, 145, 14, 22};
            Rectangle s3 = {220, 137, 14, 30};
            Rectangle s4 = {242, 152, 12, 15};
            Rectangle s5 = {262, 145, 14, 22};
            Rectangle s6 = {283, 137, 14, 30};
            std::vector<Rectangle> small_to_super = {s1, s2, s3, s4, s5, s6};
        }
    }

    namespace Invincible
    {
        namespace Stance
        {
            Rectangle s1 = {7, 292, 12, 15};
            Rectangle s2 = {28, 292, 12, 15};
            Rectangle s3 = {49, 292, 12, 15};
            Rectangle s4 = {70, 292, 12, 15};
            std::vector<Rectangle> stance_ = {s1, s2, s3, s4};
        }
        namespace Jump
        {
            Rectangle j1 = {175, 291, 16, 16};
            Rectangle j2 = {196, 291, 16, 16};
            Rectangle j3 = {217, 291, 16, 16};
            Rectangle j4 = {238, 291, 16, 16};
            std::vector<Rectangle> jump_ = {j1, j2, j3, j4};
        }
        namespace Walk
        {
            Rectangle w1 = {7, 334, 12, 15};
            Rectangle w2 = {28, 334, 12, 15};
            Rectangle w3 = {47, 333, 15, 16};
            Rectangle w4 = {70, 334, 12, 15};
            Rectangle w5 = {91, 334, 12, 15};
            Rectangle w6 = {110, 333, 15, 16};
            Rectangle w7 = {133, 334, 12, 15};
            Rectangle w8 = {154, 334, 12, 15};
            Rectangle w9 = {173, 333, 15, 16};
            Rectangle w10 = {196, 334, 12, 15};
            Rectangle w11 = {217, 334, 12, 15};
            Rectangle w12 = {236, 333, 15, 16};
            Rectangle w13 = {259, 334, 12, 15};
            Rectangle w14 = {280, 334, 12, 15};
            Rectangle w15 = {299, 332, 15, 16};
            std::vector<Rectangle> walk_ = {w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13, w14};
        }
        namespace Climb
        {
            Rectangle c1 = {7, 490, 13, 16};
            Rectangle c2 = {28, 490, 13, 15};
            Rectangle c3 = {49, 490, 13, 16};
            Rectangle c4 = {70, 490, 13, 15};
            Rectangle c5 = {91, 490, 13, 16};
            Rectangle c6 = {112, 490, 13, 15};
            Rectangle c7 = {133, 490, 13, 16};
            Rectangle c8 = {154, 490, 13, 15};
            std::vector<Rectangle> climb_ = {c1, c2, c3, c4, c5, c6, c7, c8};
        }
        namespace Slide
        {
            Rectangle s1 = {364, 448, 14, 16};
            Rectangle s2 = {386, 448, 14, 16};
            Rectangle s3 = {407, 448, 14, 16};
            Rectangle s4 = {428, 448, 14, 16};
            std::vector<Rectangle> slide_ = {s1, s2, s3, s4};
        }
        namespace Enter_Pipe
        {
            Rectangle e1 = {344, 291, 16, 16};
            Rectangle e2 = {365, 291, 16, 16};
            Rectangle e3 = {386, 291, 16, 16};
            Rectangle e4 = {407, 291, 16, 16};
            std::vector<Rectangle> enter_pipe = {e1, e2, e3, e4};
        }
        namespace Small_To_Super
        {
            Rectangle s1 = {7, 417, 12, 15};
            Rectangle s2 = {28, 417, 12, 15};
            Rectangle s3 = {49, 417, 12, 15};
            Rectangle s4 = {69, 410, 14, 22};
            Rectangle s5 = {91, 417, 12, 15};
            Rectangle s6 = {111, 410, 14, 22};
            Rectangle s7 = {133, 417, 12, 15};
            Rectangle s8 = {153, 410, 14, 22};
            Rectangle s9 = {174, 402, 14, 30};
            Rectangle s10 = {196, 417, 12, 15};
            Rectangle s11 = {216, 410, 14, 22};
            Rectangle s12 = {237, 402, 14, 30};
            Rectangle s13 = {259, 417, 12, 15};
            Rectangle s14 = {279, 402, 14, 30};
            Rectangle s15 = {300, 402, 14, 30};
            Rectangle s16 = {321, 402, 14, 30};
            Rectangle s17 = {342, 402, 14, 30};
            std::vector<Rectangle> small_to_super = {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16, s17};
        }
    }

    namespace Super
    {
        namespace Stance
        {
            Rectangle stance = {386, 36, 14, 30};
            std::vector<Rectangle> stance_ = {stance};
        }
        namespace Stance_To_Fire
        {
            Rectangle s1 = {793, 214, 14, 30};
            Rectangle s2 = {814, 214, 14, 30};
            Rectangle s3 = {835, 214, 14, 30};
            Rectangle s4 = {856, 214, 14, 30};
            //
            std::vector<Rectangle> stance_to_fire = {s1, s2, s3, s4};
        }
        namespace Crouch
        {
            Rectangle crouch = {429, 44, 16, 22};
            std::vector<Rectangle> crouch_ = {crouch};
        }
        namespace Crouch_To_Fire
        {
            Rectangle c1 = {1148, 256, 16, 22};
            Rectangle c2 = {1169, 256, 16, 22};
            Rectangle c3 = {1190, 256, 16, 22};
            Rectangle c4 = {1211, 256, 16, 22};
            //
            std::vector<Rectangle> crouch_to_fire = {c1, c2, c3, c4};
        }
        namespace Jump
        {
            Rectangle jump = {478, 35, 16, 30};
            std::vector<Rectangle> jump_ = {jump};
        }
        namespace Jump_To_Fire
        {
            Rectangle j1 = {792, 247, 16, 30};
            Rectangle j2 = {813, 247, 16, 30};
            Rectangle j3 = {834, 247, 16, 30};
            Rectangle j4 = {855, 247, 16, 30};
            std::vector<Rectangle> jump_to_fire = {j1, j2, j3, j4};
        }
        namespace Walk
        {
            Rectangle w1 = {386, 78, 14, 30};
            Rectangle w2 = {406, 78, 16, 29};
            Rectangle w3 = {427, 78, 16, 30};
            std::vector<Rectangle> walk_ = {w1, w2, w3};
        }
        namespace Walk_To_Fire
        {
            Rectangle w1 = {970, 214, 16, 29};
            Rectangle w2 = {991, 214, 16, 29};
            Rectangle w3 = {1012, 214, 16, 29};
            Rectangle w4 = {1033, 214, 16, 29};
            std::vector<Rectangle> walk_to_fire = {w1, w2, w3, w4};
        }
        namespace Slide
        {
            Rectangle slide = {522, 35, 16, 31};
            std::vector<Rectangle> slide_ = {slide};
        }
        namespace Slide_To_Fire
        {
            Rectangle s1 = {970, 247, 16, 31};
            Rectangle s2 = {991, 247, 16, 31};
            Rectangle s3 = {1012, 247, 16, 31};
            Rectangle s4 = {1033, 247, 16, 31};
            std::vector<Rectangle> slide_to_fire = {s1, s2, s3, s4};
        }
        namespace Climb
        {
            Rectangle c1 = {430, 121, 14, 28};
            Rectangle c2 = {451, 121, 14, 26};
            std::vector<Rectangle> climb_ = {c1, c2};
        }
        namespace Enter_Pipe
        {
            Rectangle enter = {515, 121, 16, 30};
            std::vector<Rectangle> enter_pipe = {enter};
        }
        namespace Fade_Out
        {
            Rectangle f1 = {385, 205, 16, 29};
            Rectangle f2 = {406, 205, 16, 30};
            Rectangle f3 = {427, 205, 16, 30};
            Rectangle f4 = {449, 205, 14, 30};
            Rectangle f5 = {470, 205, 14, 30};
            Rectangle f6 = {491, 205, 14, 30};
            Rectangle f7 = {511, 205, 16, 29};
            Rectangle f8 = {532, 205, 16, 29};
            Rectangle f9 = {553, 205, 16, 29};
            Rectangle f10 = {574, 205, 16, 29};
            Rectangle f11 = {595, 205, 16, 30};
            Rectangle f12 = {616, 205, 16, 30};
            Rectangle f13 = {659, 205, 14, 30};
            Rectangle f14 = {680, 205, 14, 30};
            std::vector<Rectangle> fade_out = {f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14};
        }
        namespace Hit
        {
            Rectangle h1 = {616, 132, 14, 30};
            Rectangle h2 = {636, 131, 16, 30};
            Rectangle h3 = {657, 135, 16, 27};
            Rectangle h4 = {678, 146, 16, 16};
            Rectangle h5 = {701, 147, 12, 15};
            std::vector<Rectangle> hit_ = {h1, h2, h3, h4, h5};
        }
    }

    namespace Invincible_Super_And_Fire
    {
        namespace Stance
        {
            Rectangle s1 = {558, 332, 14, 30};
            Rectangle s2 = {579, 332, 14, 30};
            Rectangle s3 = {600, 332, 14, 30};
            Rectangle s4 = {621, 332, 14, 30};
            std::vector<Rectangle> stance_ = {s1, s2, s3, s4};
        }
        namespace Jump
        {
            Rectangle j1 = {727, 331, 16, 30};
            Rectangle j2 = {748, 331, 16, 30};
            Rectangle j3 = {769, 331, 16, 30};
            Rectangle j4 = {790, 331, 16, 30};
            std::vector<Rectangle> jump_ = {j1, j2, j3, j4};
        }
        namespace Crouch
        {
            Rectangle c1 = {727, 388, 16, 22};
            Rectangle c2 = {748, 388, 16, 22};
            Rectangle c3 = {769, 388, 16, 22};
            Rectangle c4 = {790, 388, 16, 22};
            std::vector<Rectangle> crouch_ = {c1, c2, c3, c4};
        }
        namespace Slide
        {
            Rectangle s1 = {557, 479, 16, 31};
            Rectangle s2 = {578, 479, 16, 31};
            Rectangle s3 = {599, 479, 16, 31};
            Rectangle s4 = {620, 479, 16, 31};
            std::vector<Rectangle> slide_ = {s1, s2, s3, s4};
        }
        namespace Climb
        {
            Rectangle c1 = {727, 421, 16, 30};
            Rectangle c2 = {748, 421, 16, 28};
            Rectangle c3 = {769, 421, 16, 30};
            Rectangle c4 = {790, 421, 16, 28};
            Rectangle c5 = {811, 421, 16, 30};
            Rectangle c6 = {832, 421, 16, 28};
            Rectangle c7 = {853, 421, 16, 30};
            Rectangle c8 = {874, 421, 16, 28};
            std::vector<Rectangle> climb_ = {c1, c2, c3, c4, c5, c6, c7, c8};
        }
        namespace Shoot_Fire
        {
            Rectangle s1 = {727, 464, 15, 30};
            Rectangle s2 = {748, 464, 15, 30};
            Rectangle s3 = {769, 464, 15, 30};
            Rectangle s4 = {790, 464, 15, 30};
            std::vector<Rectangle> shoot_fire = {s1, s2, s3, s4};
        }
        namespace Walk
        {
            Rectangle w1 = {557, 374, 15, 30};
            Rectangle w2 = {578, 438, 16, 30};
            Rectangle w3 = {578, 406, 16, 29};
            Rectangle w4 = {600, 374, 14, 30};
            Rectangle w5 = {599, 438, 16, 30};
            Rectangle w6 = {620, 406, 16, 29};
            Rectangle w7 = {621, 374, 14, 30};
            Rectangle w8 = {557, 438, 16, 30};
            Rectangle w9 = {557, 406, 16, 29};
            Rectangle w10 = {579, 374, 14, 30};
            Rectangle w11 = {578, 438, 16, 30};
            Rectangle w12 = {599, 406, 16, 29};
            Rectangle w13 = {600, 374, 14, 30};
            Rectangle w14 = {620, 438, 16, 30};
            Rectangle w15 = {620, 406, 16, 29};
            std::vector<Rectangle> walk_ = {w1, w2, w3, w4, w5, w6, w7, w7, w9, w10, w11, w12, w13, w14, w15};
        }
        namespace Enter_Pipe
        {
            Rectangle e1 = {897, 332, 16, 30};
            Rectangle e2 = {918, 332, 16, 30};
            Rectangle e3 = {939, 332, 16, 30};
            Rectangle e4 = {960, 332, 16, 30};
            std::vector<Rectangle> enter_pipe = {e1, e2, e3, e4};
        }
    }

    namespace Fire
    {
        namespace Stance
        {
            Rectangle stance = {794, 36, 14, 30};
            std::vector<Rectangle> stance_ = {stance};
        }
        namespace Crouch
        {
            Rectangle crouch = {837, 44, 16, 22};
            std::vector<Rectangle> crouch_ = {crouch};
        }
        namespace Jump
        {
            Rectangle jump = {886, 35, 16, 30};
            std::vector<Rectangle> jump_ = {jump};
        }
        namespace Walk
        {
            Rectangle w1 = {794, 78, 14, 30};
            Rectangle w2 = {814, 78, 16, 29};
            Rectangle w3 = {835, 78, 16, 30};
            std::vector<Rectangle> walk_ = {w1, w2, w3};
        }
        namespace Slide
        {
            Rectangle slide = {930, 35, 16, 31};
            std::vector<Rectangle> slide_ = {slide};
        }
        namespace Climb
        {
            Rectangle c1 = {838, 121, 14, 28};
            Rectangle c2 = {859, 121, 14, 26};
            std::vector<Rectangle> climb_ = {c1, c2};
        }
        namespace Shoot
        {
            Rectangle shoot = {921, 78, 15, 30};
            std::vector<Rectangle> shoot_ = {shoot};
        }
        namespace Enter_Pipe
        {
            Rectangle enter = {923, 121, 16, 30};
            std::vector<Rectangle> enter_pipe = {enter};
        }
        namespace Fade_out
        {
            Rectangle f1 = {792, 290, 16, 29};
            Rectangle f2 = {813, 290, 16, 30};
            Rectangle f3 = {834, 290, 16, 30};
            Rectangle f4 = {856, 290, 14, 30};
            Rectangle f5 = {877, 290, 14, 30};
            Rectangle f6 = {898, 290, 14, 30};
            Rectangle f7 = {918, 290, 16, 29};
            Rectangle f8 = {939, 290, 16, 29};
            Rectangle f9 = {960, 290, 16, 29};
            Rectangle f10 = {981, 290, 16, 29};
            Rectangle f11 = {1002, 290, 16, 30};
            Rectangle f12 = {1023, 290, 16, 30};
            Rectangle f13 = {1066, 290, 14, 30};
            Rectangle f14 = {1087, 290, 14, 30};
            std::vector<Rectangle> fade_out = {f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14};
        }
        namespace Hit
        {
            Rectangle h1 = {971, 141, 14, 30};
            Rectangle h2 = {991, 140, 16, 30};
            Rectangle h3 = {1012, 144, 16, 27};
            Rectangle h4 = {1033, 155, 16, 16};
            Rectangle h5 = {1056, 156, 12, 15};
            std::vector<Rectangle> hit_ = {h1, h2, h3, h4, h5};
        }
    }
}

namespace Item
{
    SpriteSheet item_;

    namespace Mushroom
    {
        Rectangle super_mushroom = {1, 1, 16, 16};
        Rectangle one_up_mushroom = {18, 1, 16, 16};
        Rectangle posion_mushroom = {35, 1, 16, 16};
    }

    namespace Flower
    {
        Rectangle fire_flower = {1, 18, 16, 16};
    }

    namespace Star
    {
        Rectangle invincible_star = {1, 35, 16, 16};
    }

    namespace Coin
    {
        namespace Blinking
        {
            Rectangle b1 = {4, 54, 10, 14};
            Rectangle b2 = {21, 54, 10, 14};
            Rectangle b3 = {38, 54, 10, 14};
            std::vector<Rectangle> blinking_ = {b1, b2, b3};
        }

        namespace Sparkle
        {
            Rectangle s1 = {9, 71, 2, 14};
            Rectangle s2 = {24, 71, 6, 14};
            Rectangle s3 = {39, 71, 10, 14};
            Rectangle s4 = {58, 71, 6, 14};
            Rectangle s5 = {7, 90, 7, 7};
            Rectangle s6 = {24, 86, 15, 16};
            Rectangle s7 = {44, 86, 18, 15};
            Rectangle s8 = {64, 88, 20, 15};
            Rectangle s9 = {86, 93, 18, 11};
            std::vector<Rectangle> sparkle_ = {s1, s2, s3, s4, s5, s6, s7, s8, s9};
        }
    }

    namespace Fire_Ball
    {
        namespace Fly
        {
            Rectangle f1 = {1, 105, 8, 8};
            Rectangle f2 = {10, 105, 8, 8};
            Rectangle f3 = {19, 105, 8, 8};
            Rectangle f4 = {28, 105, 8, 8};
            std::vector<Rectangle> fly_ = {f1, f2, f3, f4};
        }

        namespace Explode
        {
            Rectangle e1 = {5, 118, 8, 8};
            Rectangle e2 = {20, 115, 12, 14};
            Rectangle e3 = {35, 114, 16, 16};
            std::vector<Rectangle> explode_ = {e1, e2, e3};
        }
    }

    namespace Question_Brick
    {
        Rectangle q1 = {1, 131, 16, 16};
        Rectangle q2 = {18, 131, 16, 16};
        Rectangle q3 = {35, 131, 16, 16};
        std::vector<Rectangle> question_ = {q1, q2, q3};
    }

    namespace Brown_Brick
    {
        Rectangle type_1 = {1, 148, 16, 16};
        Rectangle type_2 = {18, 148, 16, 16};
        Rectangle type_3 = {35, 148, 16, 16};
    }

    namespace Blue_Brick
    {
        Rectangle type_1 = {1, 165, 16, 16};
        Rectangle type_2 = {18, 165, 16, 16};
        Rectangle type_3 = {35, 165, 16, 16};
    }

    namespace Gray_Brick
    {
        Rectangle type_1 = {1, 182, 16, 16};
        Rectangle type_2 = {18, 182, 16, 16};
        Rectangle type_3 = {35, 182, 16, 16};
    }
}

namespace font
{
    SpriteSheet font_;

    namespace Number
    {
        Rectangle n0 = {1, 1, 10, 10};
        Rectangle n1 = {11, 1, 8, 10};
        Rectangle n2 = {19, 1, 10, 10};
        Rectangle n3 = {28, 1, 10, 10};
        Rectangle n4 = {37, 1, 10, 10};
        Rectangle n5 = {46, 1, 10, 10};
        Rectangle n6 = {55, 1, 10, 10};
        Rectangle n7 = {64, 1, 10, 10};
        Rectangle n8 = {73, 1, 10, 10};
        Rectangle n9 = {82, 1, 10, 10};
        std::vector<Rectangle> num = {n0, n1, n2, n3, n4, n5, n6, n7, n8, n9};
    }

    namespace Coin
    {
        Rectangle c1 = {91, 1, 7, 10};
        Rectangle c2 = {100, 1, 7, 10};
        Rectangle c3 = {109, 1, 7, 10};
        std::vector<Rectangle> coin = {c1, c2, c3};
    }

    namespace Heart
    {
        Rectangle color = {82, 64, 10, 10};
        Rectangle not_color = {91, 64, 10, 10};
    }

    namespace X
    {
        Rectangle x = {83, 38, 9, 9};
    }

    namespace Hyphen
    {
        Rectangle hyphen = {19, 48, 10, 6};
    }

    namespace Clock
    {
        Rectangle clock = {1, 58, 10, 9};
    }
}

namespace Screen
{
    SpriteSheet screen_;

    Rectangle mario_word = {29, 39, 42, 8};
    Rectangle luigi_word = {30, 284, 40, 8};
    Rectangle world_word = {149, 38, 42, 9};
    Rectangle time_word = {205, 39, 34, 8};
    Rectangle game_over_word = {94, 95, 76, 16};
    Rectangle time_up_word = {362, 127, 55, 16};
    Rectangle arrow_ = {297, 508, 12, 9};
    Rectangle continue_word = {94, 127, 59, 8};
    Rectangle save_and_continue_word = {94, 143, 99, 8};
    Rectangle save_and_quit_word = {94, 159, 68, 8};
}

namespace Enemies
{
    SpriteSheet enemies_;

    namespace Goomba_Brown
    {
        namespace Normal
        {
            Rectangle n1 = {23, 174, 16, 16};
            Rectangle n2 = {61, 174, 16, 16};
            std::vector<Rectangle> normal_ = {n1, n2};
        }

        Rectangle be_stomped = {42, 182, 16, 8};
        Rectangle be_fired = {4, 174, 16, 16};
    }

    namespace Goomba_Blue
    {
        namespace Normal
        {
            Rectangle n1 = {23, 193, 16, 16};
            Rectangle n2 = {61, 193, 16, 16};
            std::vector<Rectangle> normal_ = {n1, n2};
        }

        Rectangle be_stomped = {42, 201, 16, 8};
        Rectangle be_fired = {4, 193, 16, 16};
    }

    namespace Goomba_Gray
    {
        namespace Normal
        {
            Rectangle n1 = {23, 212, 16, 16};
            Rectangle n2 = {61, 212, 16, 16};
            std::vector<Rectangle> normal_ = {n1, n2};
        }

        Rectangle be_stomped = {42, 220, 16, 8};
        Rectangle be_fired = {4, 212, 16, 16};
    }

    namespace Piranha_Plant_Green
    {
        Rectangle p1 = {327, 123, 16, 24};
        Rectangle p2 = {346, 123, 16, 24};
        std::vector<Rectangle> plant_ = {p1, p2};
    }

    namespace Piranha_Plant_Red
    {
        Rectangle p1 = {365, 123, 16, 24};
        Rectangle p2 = {384, 123, 16, 24};
        std::vector<Rectangle> plant_ = {p1, p2};
    }

    namespace Buzzy_Beetle
    {
        namespace Normal
        {
            Rectangle n1 = {175, 187, 16, 15};
            Rectangle n2 = {194, 186, 15, 16};
            std::vector<Rectangle> normal = {n1, n2};
        }

        Rectangle be_stomped = {213, 187, 16, 15};

        namespace Be_Kicked
        {
            Rectangle k1 = {213, 187, 16, 15};
            Rectangle k2 = {232, 187, 16, 15};
            Rectangle k3 = {251, 187, 16, 15};
            Rectangle k4 = {270, 187, 16, 15};
            std::vector<Rectangle> be_kicked = {k1, k2, k3, k4};
        }
    }

    namespace Troopa_Red
    {
        namespace Normal
        {
            Rectangle n1 = {4, 13, 16, 23};
            Rectangle n2 = {23, 12, 16, 24};
            std::vector<Rectangle> normal_ = {n1, n2};
        }

        namespace Be_Kicked
        {
            Rectangle k1 = {61, 22, 16, 14};
            Rectangle k2 = {80, 22, 16, 14};
            Rectangle k3 = {99, 22, 16, 14};
            Rectangle k4 = {118, 22, 16, 14};
            std::vector<Rectangle> be_kicked = {k1, k2, k3, k4};
        }

        Rectangle be_stomped = {42, 22, 16, 14};
        Rectangle be_fired = {99, 49, 16, 14};
    }

    namespace Troopa_Green
    {
        namespace Normal
        {
            Rectangle n1 = {4, 67, 16, 23};
            Rectangle n2 = {23, 66, 16, 24};
            std::vector<Rectangle> normal_ = {n1, n2};
        }

        namespace Be_Kicked
        {
            Rectangle k1 = {61, 76, 16, 14};
            Rectangle k2 = {80, 76, 16, 14};
            Rectangle k3 = {99, 76, 16, 14};
            Rectangle k4 = {118, 76, 16, 14};
            std::vector<Rectangle> be_kicked = {k1, k2, k3, k4};
        }

        Rectangle be_stomped = {42, 76, 16, 14};
        Rectangle be_fired = {99, 103, 16, 14};
    }

    namespace Latiku
    {
        Rectangle fly_ = {194, 123, 16, 24};
        Rectangle throw_ = {213, 131, 16, 16};
        Rectangle fall_ = {175, 123, 16, 24};
    }

    namespace Spiny
    {
        namespace Egg
        {
            Rectangle e1 = {252, 150, 14, 16};
            Rectangle e2 = {233, 150, 14, 16};
            std::vector<Rectangle> egg_ = {e1, e2};
        }

        namespace Normal
        {
            Rectangle n1 = {175, 151, 16, 15};
            Rectangle n2 = {194, 150, 16, 16};
            std::vector<Rectangle> normal_ = {n1, n2};
        }
        Rectangle fall_ = {213, 150, 16, 16};
    }
}