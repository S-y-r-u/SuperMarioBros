#include "Sprite.h"

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

namespace Mario_Sprite
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
        namespace Pose
        {
            Rectangle p1 = {134, 92, 14, 16};
            Rectangle p2 = {153, 92, 16, 16};
            std::vector<Rectangle> pose = {p1, p2};
        }
        namespace Small_To_Super
        {
            Rectangle s1 = {179, 152, 12, 15};
            Rectangle s2 = {199, 145, 14, 22};
            Rectangle s3 = {179, 152, 12, 15};
            Rectangle s4 = {199, 145, 14, 22};
            Rectangle s5 = {179, 152, 12, 15};
            Rectangle s6 = {199, 145, 14, 22};
            Rectangle s7 = {220, 137, 14, 30};
            Rectangle s8 = {242, 152, 12, 15};
            Rectangle s9 = {262, 145, 14, 22};
            Rectangle s10 = {283, 137, 14, 30};
            std::vector<Rectangle> small_to_super = {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10};
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
        namespace Pose
        {
            Rectangle p1 = {344, 490, 14, 16};
            Rectangle p2 = {365, 490, 14, 16};
            Rectangle p3 = {386, 490, 14, 16};
            Rectangle p4 = {407, 490, 14, 16};
            Rectangle p5 = {426, 490, 16, 16};
            Rectangle p6 = {447, 490, 16, 16};
            Rectangle p7 = {468, 490, 16, 16};
            Rectangle p8 = {489, 490, 16, 16};
            std::vector<Rectangle> pose = {p1, p2, p3, p4, p5, p6, p7};
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
            Rectangle s5 = {793, 214, 14, 30};
            Rectangle s6 = {814, 214, 14, 30};
            Rectangle s7 = {835, 214, 14, 30};
            Rectangle s8 = {856, 214, 14, 30};
            Rectangle s9 = {793, 214, 14, 30};
            Rectangle s10 = {814, 214, 14, 30};
            Rectangle s11 = {835, 214, 14, 30};
            Rectangle s12 = {856, 214, 14, 30};
            std::vector<Rectangle> stance_to_fire = {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12};
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
            Rectangle c5 = {1148, 256, 16, 22};
            Rectangle c6 = {1169, 256, 16, 22};
            Rectangle c7 = {1190, 256, 16, 22};
            Rectangle c8 = {1211, 256, 16, 22};
            Rectangle c9 = {1148, 256, 16, 22};
            Rectangle c10 = {1169, 256, 16, 22};
            Rectangle c11 = {1190, 256, 16, 22};
            Rectangle c12 = {1211, 256, 16, 22};
            std::vector<Rectangle> crouch_to_fire = {c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12};
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
            Rectangle j5 = {792, 247, 16, 30};
            Rectangle j6 = {813, 247, 16, 30};
            Rectangle j7 = {834, 247, 16, 30};
            Rectangle j8 = {855, 247, 16, 30};
            Rectangle j9 = {792, 247, 16, 30};
            Rectangle j10 = {813, 247, 16, 30};
            Rectangle j11 = {834, 247, 16, 30};
            Rectangle j12 = {855, 247, 16, 30};
            std::vector<Rectangle> jump_to_fire = {j1, j2, j3, j4, j5, j6, j7, j8, j9, j10, j11, j12};
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
            Rectangle w5 = {970, 214, 16, 29};
            Rectangle w6 = {991, 214, 16, 29};
            Rectangle w7 = {1012, 214, 16, 29};
            Rectangle w8 = {1033, 214, 16, 29};
            Rectangle w9 = {970, 214, 16, 29};
            Rectangle w10 = {991, 214, 16, 29};
            Rectangle w11 = {1012, 214, 16, 29};
            Rectangle w12 = {1033, 214, 16, 29};
            std::vector<Rectangle> walk_to_fire = {w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12};
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
            Rectangle s5 = {970, 247, 16, 31};
            Rectangle s6 = {991, 247, 16, 31};
            Rectangle s7 = {1012, 247, 16, 31};
            Rectangle s8 = {1033, 247, 16, 31};
            Rectangle s9 = {970, 247, 16, 31};
            Rectangle s10 = {991, 247, 16, 31};
            Rectangle s11 = {1012, 247, 16, 31};
            Rectangle s12 = {1033, 247, 16, 31};
            std::vector<Rectangle> slide_to_fire = {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12};
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
        namespace Pose
        {
            Rectangle p1 = {385, 121, 16, 30};
            Rectangle p2 = {406, 121, 16, 29};
            std::vector<Rectangle> pose = {p1, p2};
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
            Rectangle h5 = {657, 135, 16, 27};
            Rectangle h6 = {678, 146, 16, 16};
            Rectangle h7 = {657, 135, 16, 27};
            Rectangle h8 = {678, 146, 16, 16};
            Rectangle h9 = {657, 135, 16, 27};
            Rectangle h10 = {678, 146, 16, 16};
            Rectangle h11 = {657, 135, 16, 27};
            Rectangle h12 = {678, 146, 16, 16};
            Rectangle h13 = {701, 147, 12, 15};
            std::vector<Rectangle> hit_ = {h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11, h12, h13};
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
        namespace Pose
        {

            Rectangle p1 = {897, 380, 16, 30};
            Rectangle p2 = {918, 380, 16, 30};
            Rectangle p3 = {939, 380, 16, 30};
            Rectangle p4 = {960, 380, 16, 30};
            Rectangle p5 = {981, 380, 16, 29};
            Rectangle p6 = {1002, 380, 16, 30};
            Rectangle p7 = {1023, 380, 16, 30};
            Rectangle p8 = {1044, 380, 16, 30};
            std::vector<Rectangle> pose = {p1, p2, p3, p4, p5, p6, p7, p8};
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
        namespace Fade_Out
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
            Rectangle h5 = {1012, 144, 16, 27};
            Rectangle h6 = {1033, 155, 16, 16};
            Rectangle h7 = {1012, 144, 16, 27};
            Rectangle h8 = {1033, 155, 16, 16};
            Rectangle h9 = {1012, 144, 16, 27};
            Rectangle h10 = {1033, 155, 16, 16};
            Rectangle h11 = {1012, 144, 16, 27};
            Rectangle h12 = {1033, 155, 16, 16};
            Rectangle h13 = {1056, 156, 12, 15};
            std::vector<Rectangle> hit_ = {h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11, h12, h13};
        }
        namespace Pose
        {
            Rectangle p1 = {793, 121, 16, 30};
            Rectangle p2 = {814, 121, 16, 29};
            std::vector<Rectangle> pose = {p1, p2};
        }
    }
}

namespace Luigi_Sprite
{
    SpriteSheet luigi_sprite;

    namespace Small
    {
        namespace Stance
        {
            Rectangle stance = {8, 52, 11, 15};
            std::vector<Rectangle> stance_ = {stance};
        }
        namespace Jump
        {
            Rectangle jump = {49, 51, 16, 16};
            std::vector<Rectangle> jump_ = {jump};
        }
        namespace Die
        {
            Rectangle die = {93, 51, 16, 16};
            std::vector<Rectangle> die_ = {die};
        }
        namespace Walk
        {
            Rectangle w1 = {8, 95, 11, 15};
            Rectangle w2 = {28, 95, 12, 15};
            Rectangle w3 = {48, 94, 14, 16};
            std::vector<Rectangle> walk_ = {w1, w2, w3};
        }
        namespace Slide
        {
            Rectangle slide = {134, 137, 13, 16};
            std::vector<Rectangle> slide_ = {slide};
        }
        namespace Climb
        {
            Rectangle c1 = {7, 180, 12, 16};
            Rectangle c2 = {28, 180, 12, 15};
            std::vector<Rectangle> climb_ = {c1, c2};
        }
        namespace Enter_Pipe
        {
            Rectangle enter = {91, 180, 15, 16};
            std::vector<Rectangle> enter_pipe = {enter};
        }
        namespace Fade_Out
        {
            Rectangle f1 = {7, 230, 12, 15};
            Rectangle f2 = {27, 229, 14, 16};
            Rectangle f3 = {48, 229, 14, 16};
            Rectangle f4 = {71, 230, 11, 15};
            Rectangle f5 = {92, 230, 11, 15};
            Rectangle f6 = {113, 230, 11, 15};
            Rectangle f7 = {133, 230, 12, 15};
            Rectangle f8 = {175, 230, 12, 15};
            Rectangle f9 = {196, 230, 12, 15};
            Rectangle f10 = {216, 229, 14, 16};
            Rectangle f11 = {237, 229, 14, 16};
            Rectangle f12 = {258, 229, 14, 16};
            Rectangle f13 = {281, 230, 11, 15};
            Rectangle f14 = {302, 230, 11, 15};
            std::vector<Rectangle> fade_out = {f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14};
        }
        namespace Small_To_Super
        {
            Rectangle s1 = {180, 155, 11, 15};
            Rectangle s2 = {199, 148, 14, 25};
            Rectangle s3 = {180, 155, 11, 15};
            Rectangle s4 = {199, 148, 14, 25};
            Rectangle s5 = {180, 155, 11, 15};
            Rectangle s6 = {199, 148, 14, 25};
            Rectangle s7 = {220, 139, 14, 31};
            Rectangle s8 = {243, 155, 11, 15};
            Rectangle s9 = {262, 148, 14, 22};
            Rectangle s10 = {284, 139, 14, 31};
            std::vector<Rectangle> small_to_super = {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10};
        }
        namespace Pose
        {
            Rectangle p1 = {134, 94, 14, 16};
            Rectangle p2 = {154, 94, 15, 16};
            std::vector<Rectangle> pose = {p1, p2};

        }
    }

    namespace Invincible
    {
        namespace Stance
        {
            Rectangle s1 = {8, 298, 11, 15};
            Rectangle s2 = {29, 298, 11, 15};
            Rectangle s3 = {50, 298, 11, 15};
            Rectangle s4 = {71, 298, 11, 15};
            std::vector<Rectangle> stance_ = {s1, s2, s3, s4};
        }
        namespace Jump
        {
            Rectangle j1 = {175, 297, 16, 16};
            Rectangle j2 = {196, 297, 16, 16};
            Rectangle j3 = {217, 297, 16, 16};
            Rectangle j4 = {238, 297, 16, 16};
            std::vector<Rectangle> jump_ = {j1, j2, j3, j4};
        }
        namespace Walk
        {
            Rectangle w1 = {7, 341, 11, 15};
            Rectangle w2 = {28, 341, 12, 15};
            Rectangle w3 = {48, 340, 14, 16};
            Rectangle w4 = {71, 341, 11, 15};
            Rectangle w5 = {91, 341, 12, 15};
            Rectangle w6 = {111, 340, 14, 16};
            Rectangle w7 = {134, 341, 11, 15};
            Rectangle w8 = {154, 341, 12, 15};
            Rectangle w9 = {174, 340, 14, 16};
            Rectangle w10 = {197, 341, 11, 15};
            Rectangle w11 = {217, 341, 11, 15};
            Rectangle w12 = {237, 340, 14, 16};
            Rectangle w13 = {260, 341, 11, 15};
            Rectangle w14 = {280, 341, 12, 15};
            Rectangle w15 = {300, 340, 14, 16};
            std::vector<Rectangle> walk_ = {w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13, w14};
        }
        namespace Climb
        {
            Rectangle c1 = {7, 501, 12, 16};
            Rectangle c2 = {28, 501, 12, 15};
            Rectangle c3 = {49, 501, 12, 16};
            Rectangle c4 = {70, 501, 12, 15};
            Rectangle c5 = {91, 501, 12, 16};
            Rectangle c6 = {112, 501, 12, 15};
            Rectangle c7 = {133, 501, 12, 16};
            Rectangle c8 = {154, 501, 12, 15};
            std::vector<Rectangle> climb_ = {c1, c2, c3, c4, c5, c6, c7, c8};
        }
        namespace Slide
        {
            Rectangle s1 = {323, 458, 13, 16};
            Rectangle s2 = {344, 458, 13, 16};
            Rectangle s3 = {365, 458, 13, 16};
            Rectangle s4 = {386, 458, 13, 16};
            std::vector<Rectangle> slide_ = {s1, s2, s3, s4};
        }
        namespace Enter_Pipe
        {
            Rectangle e1 = {345, 297, 15, 16};
            Rectangle e2 = {366, 297, 15, 16};
            Rectangle e3 = {387, 297, 15, 16};
            Rectangle e4 = {408, 291, 16, 16};
            std::vector<Rectangle> enter_pipe = {e1, e2, e3, e4};
        }
        namespace Small_To_Super
        {
            Rectangle s1 = {8, 426, 11, 15};
            Rectangle s2 = {29, 426, 11, 15};
            Rectangle s3 = {50, 426, 11, 15};
            Rectangle s4 = {69, 419, 14, 22};
            Rectangle s5 = {92, 426, 11, 15};
            Rectangle s6 = {111, 419, 14, 22};
            Rectangle s7 = {134, 426, 11, 15};
            Rectangle s8 = {153, 419, 14, 22};
            Rectangle s9 = {174, 410, 14, 31};
            Rectangle s10 = {197, 426, 11, 15};
            Rectangle s11 = {216, 419, 14, 22};
            Rectangle s12 = {237, 410, 14, 31};
            Rectangle s13 = {258, 426, 11, 15};
            Rectangle s14 = {279, 410, 14, 31};
            Rectangle s15 = {300, 410, 14, 31};
            std::vector<Rectangle> small_to_super = {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15};
        }
        namespace Pose
        {
            Rectangle p1 = {344, 501, 14, 16};
            Rectangle p2 = {365, 501, 15, 16};
            Rectangle p3 = {386, 501, 15, 16};
            Rectangle p4 = {407, 501, 15, 16};
            Rectangle p5 = {427, 501, 15, 16};
            Rectangle p6 = {448, 501, 15, 16};
            Rectangle p7 = {469, 501, 15, 16};
            Rectangle p8 = {490, 501, 15, 16};
            std::vector<Rectangle> pose = {p1, p2, p3, p4, p5, p6, p7, p8};
        }
    }

    namespace Super
    {
        namespace Stance
        {
            Rectangle stance = {386, 36, 14, 31};
            std::vector<Rectangle> stance_ = {stance};
        }
        namespace Stance_To_Fire
        {
            Rectangle s1 = {772, 217, 14, 31};
            Rectangle s2 = {793, 217, 14, 31};
            Rectangle s3 = {814, 217, 14, 31};
            Rectangle s4 = {835, 217, 14, 31};
            Rectangle s5 = {772, 217, 14, 31};
            Rectangle s6 = {793, 217, 14, 31};
            Rectangle s7 = {793, 217, 14, 31};
            Rectangle s8 = {835, 217, 14, 31};
            Rectangle s9 = {772, 217, 14, 31};
            Rectangle s10 = {793, 217, 14, 31};
            Rectangle s11 = {793, 217, 14, 31};
            Rectangle s12 = {835, 217, 14, 31};
            std::vector<Rectangle> stance_to_fire = {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12};
        }
        namespace Crouch
        {
            Rectangle crouch = {429, 44, 15, 23};
            std::vector<Rectangle> crouch_ = {crouch};
        }
        namespace Crouch_To_Fire
        {
            Rectangle c1 = {1127, 260, 15, 23};
            Rectangle c2 = {1148, 260, 15, 23};
            Rectangle c3 = {1169, 260, 15, 23};
            Rectangle c4 = {1190, 260, 15, 23};
            Rectangle c5 = {1127, 260, 15, 23};
            Rectangle c6 = {1148, 260, 15, 23};
            Rectangle c7 = {1169, 260, 15, 23};
            Rectangle c8 = {1190, 260, 15, 23};
            Rectangle c9 = {1127, 260, 15, 23};
            Rectangle c10 = {1148, 260, 15, 23};
            Rectangle c11 = {1169, 260, 15, 23};
            Rectangle c12 = {1190, 260, 15, 23};
            std::vector<Rectangle> crouch_to_fire = {c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12};
        }
        namespace Jump
        {
            Rectangle jump = {478, 36, 16, 30};
            std::vector<Rectangle> jump_ = {jump};
        }
        namespace Jump_To_Fire
        {
            Rectangle j1 = {771, 252, 16, 30};
            Rectangle j2 = {792, 252, 16, 30};
            Rectangle j3 = {813, 252, 16, 30};
            Rectangle j4 = {834, 252, 16, 30};
            Rectangle j5 = {771, 252, 16, 30};
            Rectangle j6 = {792, 252, 16, 30};
            Rectangle j7 = {813, 252, 16, 30};
            Rectangle j8 = {834, 252, 16, 30};
            Rectangle j9 = {771, 252, 16, 30};
            Rectangle j10 = {792, 252, 16, 30};
            Rectangle j11 = {813, 252, 16, 30};
            Rectangle j12 = {834, 252, 16, 30};
            std::vector<Rectangle> jump_to_fire = {j1, j2, j3, j4, j5, j6, j7, j8, j9, j10, j11, j12};
        }
        namespace Walk
        {
            Rectangle w1 = {385, 79, 15, 31};
            Rectangle w2 = {406, 79, 16, 31};
            Rectangle w3 = {427, 79, 16, 31};
            std::vector<Rectangle> walk_ = {w1, w2, w3};
        }
        namespace Walk_To_Fire
        {
            Rectangle w1 = {949, 217, 16, 30};
            Rectangle w2 = {970, 217, 16, 30};
            Rectangle w3 = {991, 217, 16, 30};
            Rectangle w4 = {1012, 217, 16, 30};
            Rectangle w5 = {949, 217, 16, 30};
            Rectangle w6 = {970, 217, 16, 30};
            Rectangle w7 = {991, 217, 16, 30};
            Rectangle w8 = {1012, 217, 16, 30};
            Rectangle w9 = {949, 217, 16, 30};
            Rectangle w10 = {970, 217, 16, 30};
            Rectangle w11 = {991, 217, 16, 30};
            Rectangle w12 = {1012, 217, 16, 30};
            std::vector<Rectangle> walk_to_fire = {w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12};
        }
        namespace Slide
        {
            Rectangle slide = {522, 35, 16, 32};
            std::vector<Rectangle> slide_ = {slide};
        }
        namespace Slide_To_Fire
        {
            Rectangle s1 = {949, 251, 16, 32};
            Rectangle s2 = {970, 251, 16, 32};
            Rectangle s3 = {991, 251, 16, 32};
            Rectangle s4 = {1012, 251, 16, 32};
            Rectangle s5 = {949, 251, 16, 32};
            Rectangle s6 = {970, 251, 16, 32};
            Rectangle s7 = {991, 251, 16, 32};
            Rectangle s8 = {1012, 251, 16, 32};
            Rectangle s9 = {949, 251, 16, 32};
            Rectangle s10 = {970, 251, 16, 32};
            Rectangle s11 = {991, 251, 16, 32};
            Rectangle s12 = {1012, 251, 16, 32};
            std::vector<Rectangle> slide_to_fire = {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12};
        }
        namespace Climb
        {
            Rectangle c1 = {430, 122, 14, 29};
            Rectangle c2 = {451, 122, 14, 27};
            std::vector<Rectangle> climb_ = {c1, c2};
        }
        namespace Enter_Pipe
        {
            Rectangle enter = {515, 122, 16, 31};
            std::vector<Rectangle> enter_pipe = {enter};
        }
        namespace Fade_Out
        {
            Rectangle f1 = {385, 208, 16, 30};
            Rectangle f2 = {406, 208, 16, 31};
            Rectangle f3 = {427, 208, 16, 31};
            Rectangle f4 = {449, 208, 14, 31};
            Rectangle f5 = {471, 208, 14, 31};
            Rectangle f6 = {492, 208, 14, 31};
            Rectangle f7 = {511, 208, 16, 30};
            Rectangle f8 = {532, 208, 16, 30};
            Rectangle f9 = {553, 208, 16, 30};
            Rectangle f10 = {574, 208, 16, 30};
            Rectangle f11 = {595, 208, 16, 31};
            Rectangle f12 = {616, 208, 16, 31};
            Rectangle f13 = {660, 208, 14, 31};
            Rectangle f14 = {681, 208, 14, 31};
            std::vector<Rectangle> fade_out = {f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14};
        }
        namespace Hit
        {
            Rectangle h1 = {617, 133, 14, 31};
            Rectangle h2 = {637, 133, 16, 30};
            Rectangle h3 = {658, 133, 16, 29};
            Rectangle h4 = {679, 148, 16, 16};
            Rectangle h5 = {658, 133, 16, 29};
            Rectangle h6 = {679, 148, 16, 16};
            Rectangle h7 = {658, 133, 16, 29};
            Rectangle h8 = {679, 148, 16, 16};
            Rectangle h9 = {658, 133, 16, 29};
            Rectangle h10 = {679, 148, 16, 16};
            Rectangle h11 = {658, 133, 16, 29};
            Rectangle h12 = {679, 148, 16, 16};
            Rectangle h13 = {701, 147, 12, 15};
            std::vector<Rectangle> hit_ = {h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11, h12, h13};
        }
        namespace Pose
        {
            Rectangle p1 = {385, 122, 16, 31};
            Rectangle p2 = {406, 122, 16, 30};
            std::vector<Rectangle> pose = {p1, p2};
        }
    }

    namespace Invincible_Super_And_Fire
    {
        namespace Stance
        {
            Rectangle s1 = {539, 338, 14, 31};
            Rectangle s2 = {560, 338, 14, 31};
            Rectangle s3 = {581, 338, 14, 31};
            Rectangle s4 = {602, 338, 14, 31};
            std::vector<Rectangle> stance_ = {s1, s2, s3, s4};
        }
        namespace Jump
        {
            Rectangle j1 = {708, 338, 16, 30};
            Rectangle j2 = {729, 338, 16, 30};
            Rectangle j3 = {750, 338, 16, 30};
            Rectangle j4 = {771, 338, 16, 30};
            std::vector<Rectangle> jump_ = {j1, j2, j3, j4};
        }
        namespace Crouch
        {
            Rectangle c1 = {708, 395, 15, 23};
            Rectangle c2 = {729, 395, 15, 23};
            Rectangle c3 = {750, 395, 15, 23};
            Rectangle c4 = {771, 395, 15, 23};
            std::vector<Rectangle> crouch_ = {c1, c2, c3, c4};
        }
        namespace Slide
        {
            Rectangle s1 = {538, 489, 16, 32};
            Rectangle s2 = {559, 489, 16, 32};
            Rectangle s3 = {580, 489, 16, 32};
            Rectangle s4 = {601, 489, 16, 32};
            std::vector<Rectangle> slide_ = {s1, s2, s3, s4};
        }
        namespace Climb
        {
            Rectangle c1 = {709, 430, 14, 29};
            Rectangle c2 = {730, 430, 14, 27};
            Rectangle c3 = {751, 430, 14, 29};
            Rectangle c4 = {772, 430, 14, 27};
            Rectangle c5 = {793, 430, 14, 29};
            Rectangle c6 = {814, 430, 14, 27};
            Rectangle c7 = {835, 430, 14, 29};
            Rectangle c8 = {856, 430, 14, 27};
            std::vector<Rectangle> climb_ = {c1, c2, c3, c4, c5, c6, c7, c8};
        }
        namespace Shoot_Fire
        {
            Rectangle s1 = {708, 473, 15, 31};
            Rectangle s2 = {729, 473, 15, 31};
            Rectangle s3 = {750, 473, 15, 31};
            Rectangle s4 = {771, 473, 15, 31};
            std::vector<Rectangle> shoot_fire = {s1, s2, s3, s4};
        }
        namespace Walk
        {
            Rectangle w1 = {539, 381, 14, 31};
            Rectangle w2 = {538, 447, 16, 31};
            Rectangle w3 = {559, 414, 16, 30};
            Rectangle w4 = {581, 381, 14, 31};
            Rectangle w5 = {559, 447, 16, 31};
            Rectangle w6 = {601, 414, 16, 30};
            Rectangle w7 = {621, 374, 14, 30};
            Rectangle w8 = {538, 447, 16, 31};
            Rectangle w9 = {538, 414, 16, 30};
            Rectangle w10 = {560, 381, 14, 31};
            Rectangle w11 = {538, 447, 16, 31};
            Rectangle w12 = {580, 414, 16, 30};
            Rectangle w13 = {581, 381, 14, 31};
            Rectangle w14 = {601, 447, 16, 31};
            Rectangle w15 = {601, 414, 16, 30};
            std::vector<Rectangle> walk_ = {w1, w2, w3, w4, w5, w6, w7, w7, w9, w10, w11, w12, w13, w14, w15};
        }
        namespace Enter_Pipe
        {
            Rectangle e1 = {878, 338, 16, 31};
            Rectangle e2 = {899, 332, 16, 30};
            Rectangle e3 = {920, 332, 16, 30};
            Rectangle e4 = {941, 332, 16, 30};
            std::vector<Rectangle> enter_pipe = {e1, e2, e3, e4};
        }
        namespace Pose
        {
            Rectangle p1 = {878, 387, 16, 31};
            Rectangle p2 = {899, 387, 16, 31};
            Rectangle p3 = {920, 387, 16, 31};
            Rectangle p4 = {941, 387, 16, 31};
            Rectangle p5 = {962, 387, 16, 30};
            Rectangle p6 = {983, 387, 16, 30};
            Rectangle p7 = {1004, 387, 16, 30};
            Rectangle p8 = {1025, 387, 16, 30};
            std::vector<Rectangle> pose = {p1, p2, p3, p4, p5, p6, p7, p8};
        }
    }

    namespace Fire
    {
        namespace Stance
        {
            Rectangle stance = {772, 36, 14, 31};
            std::vector<Rectangle> stance_ = {stance};
        }
        namespace Crouch
        {
            Rectangle crouch = {815, 44, 15, 23};
            std::vector<Rectangle> crouch_ = {crouch};
        }
        namespace Jump
        {
            Rectangle jump = {864, 36, 16, 30};
            std::vector<Rectangle> jump_ = {jump};
        }
        namespace Walk
        {
            Rectangle w1 = {772, 79, 14, 31};
            Rectangle w2 = {813, 79, 16, 31};
            Rectangle w3 = {792, 79, 16, 30};
            std::vector<Rectangle> walk_ = {w1, w2, w3};
        }
        namespace Slide
        {
            Rectangle slide = {908, 35, 16, 32};
            std::vector<Rectangle> slide_ = {slide};
        }
        namespace Climb
        {
            Rectangle c1 = {816, 122, 14, 29};
            Rectangle c2 = {837, 122, 14, 27};
            std::vector<Rectangle> climb_ = {c1, c2};
        }
        namespace Shoot
        {
            Rectangle shoot = {899, 79, 15, 31};
            std::vector<Rectangle> shoot_ = {shoot};
        }
        namespace Enter_Pipe
        {
            Rectangle enter = {901, 122, 16, 31};
            std::vector<Rectangle> enter_pipe = {enter};
        }
        namespace Fade_Out
        {
            Rectangle f1 = {771, 295, 16, 30};
            Rectangle f2 = {792, 295, 16, 31};
            Rectangle f3 = {813, 295, 16, 31};
            Rectangle f4 = {835, 295, 14, 31};
            Rectangle f5 = {857, 295, 14, 31};
            Rectangle f6 = {878, 295, 14, 31};
            Rectangle f7 = {897, 295, 16, 30};
            Rectangle f8 = {918, 295, 16, 30};
            Rectangle f9 = {939, 295, 16, 30};
            Rectangle f10 = {960, 295, 16, 30};
            Rectangle f11 = {981, 295, 16, 31};
            Rectangle f12 = {1002, 295, 16, 31};
            Rectangle f13 = {1046, 295, 14, 31};
            Rectangle f14 = {1067, 295, 14, 31};
            std::vector<Rectangle> fade_out = {f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14};
        }
        namespace Hit
        {
            Rectangle h1 = {950, 142, 14, 31};
            Rectangle h2 = {970, 142, 16, 30};
            Rectangle h3 = {991, 142, 16, 29};
            Rectangle h4 = {1012, 157, 16, 16};
            Rectangle h5 = {991, 142, 16, 29};
            Rectangle h6 = {1012, 157, 16, 16};
            Rectangle h7 = {991, 142, 16, 29};
            Rectangle h8 = {1012, 157, 16, 16};
            Rectangle h9 = {991, 142, 16, 29};
            Rectangle h10 = {1012, 157, 16, 16};
            Rectangle h11 = {991, 142, 16, 29};
            Rectangle h12 = {1012, 157, 16, 16};
            Rectangle h13 = {1036, 158, 11, 15};
            std::vector<Rectangle> hit_ = {h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11, h12, h13};
        }
        namespace Pose
        {
            Rectangle p1 = {771, 122, 16, 31};
            Rectangle p2 = {792, 122, 16, 30};
            std::vector<Rectangle> pose = {p1, p2};
        }
    }
}

namespace Item_Sprite
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

        namespace Hidden
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
            std::vector<Rectangle> hidden_ = {s1, s2, s3, s4, s5, s6, s7, s8, s9};
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
        Rectangle break_ = {52, 148, 8, 8};
    }

    namespace Blue_Brick
    {
        Rectangle type_1 = {1, 165, 16, 16};
        Rectangle type_2 = {18, 165, 16, 16};
        Rectangle type_3 = {35, 165, 16, 16};
        Rectangle break_ = {52, 165, 8, 8};
    }

    namespace Gray_Brick
    {
        Rectangle type_1 = {1, 182, 16, 16};
        Rectangle type_2 = {18, 182, 16, 16};
        Rectangle type_3 = {35, 182, 16, 16};
        Rectangle break_ = {52, 182, 8, 8};
    }
}

namespace Font_Sprite
{
    SpriteSheet font_;

    namespace Number
    {
        Rectangle n0 = {2, 2, 8, 8};
        Rectangle n1 = {11, 2, 8, 8};
        Rectangle n2 = {20, 2, 8, 8};
        Rectangle n3 = {29, 2, 8, 8};
        Rectangle n4 = {38, 2, 8, 8};
        Rectangle n5 = {47, 2, 8, 8};
        Rectangle n6 = {56, 2, 8, 8};
        Rectangle n7 = {65, 2, 8, 8};
        Rectangle n8 = {74, 2, 8, 8};
        Rectangle n9 = {83, 2, 8, 8};
        std::vector<Rectangle> num = {n0, n1, n2, n3, n4, n5, n6, n7, n8, n9};
    }

    namespace Character
    {
        Rectangle A = {2, 11, 8, 8};
        Rectangle B = {11, 11, 8, 8};
        Rectangle C = {20, 11, 8, 8};
        Rectangle D = {29, 11, 8, 8};
        Rectangle E = {38, 11, 8, 8};
        Rectangle F = {47, 11, 8, 8};
        Rectangle G = {56, 11, 8, 8};
        Rectangle H = {65, 11, 8, 8};
        Rectangle I = {74, 11, 8, 8};
        Rectangle J = {83, 11, 8, 8};
        Rectangle K = {92, 11, 8, 8};
        Rectangle L = {101, 11, 8, 8};
        Rectangle M = {110, 11, 8, 8};
        Rectangle N = {2, 20, 8, 8};
        Rectangle O = {11, 20, 8, 8};
        Rectangle P = {20, 20, 8, 8};
        Rectangle Q = {29, 20, 8, 8};
        Rectangle R = {38, 20, 8, 8};
        Rectangle S = {47, 20, 8, 8};
        Rectangle T = {56, 20, 8, 8};
        Rectangle U = {65, 20, 8, 8};
        Rectangle V = {74, 20, 8, 8};
        Rectangle W = {83, 20, 8, 8};
        Rectangle X = {92, 20, 8, 8};
        Rectangle Y = {101, 20, 8, 8};
        Rectangle Z = {110, 20, 8, 8};
        std::vector<Rectangle> character = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
    }

    void DrawText(std::string s, float x, float y, Color color, float scale)
    {
        for (char c : s)
        {
            if (c == ' ')
            {
                x += 8 * scale + 1.0f; // Adding a small space for space character
                continue;
            }
            Rectangle source;
            if (c >= '0' && c <= '9')
                source = Number::num[c - '0'];
            else if (c >= 'A' && c <= 'Z')
                source = Character::character[c - 'A'];
            else if (c == '%')
                source = Percent::percent;
            else if (c == '-')
                source = Hyphen::hyphen;
            else
                source = Character::character[c - 'a'];
            Rectangle dest = {x, y, source.width * scale, source.height * scale};
            DrawTexturePro(font_.sprite, source, dest, {0.0f, 0.0f}, 0.0f, color);
            x += source.width * scale + 1.0f; // Adding a small space between characters
        }
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

    namespace Percent
    {
        Rectangle percent = {38, 48, 7, 7};
    }
}

namespace Screen_Sprite
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

namespace Enemies_Sprite
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
        Rectangle be_fired_or_hit = {4, 174, 16, 16};
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
        Rectangle be_fired_or_hit = {4, 193, 16, 16};
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
        Rectangle be_fired_or_hit = {4, 212, 16, 16};
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
        Rectangle be_fired_or_hit = {99, 49, 16, 14};
    }

    namespace Troopa_Green
    {
        namespace Normal
        {
            Rectangle n1 = {4, 67, 16, 23};
            Rectangle n2 = {23, 66, 16, 24};
            std::vector<Rectangle> normal_ = {n1, n2};
        }

        namespace Shell_Idle
        {
            Rectangle k1 = {61, 76, 16, 14};
            Rectangle k2 = {42, 76, 16, 14};
            std::vector<Rectangle> shell_idle = {k1, k2};
        }

        namespace Shell_Moving
        {
            Rectangle k1 = {80, 76, 16, 14};
            Rectangle k2 = {99, 76, 16, 14};
            Rectangle k3 = {118, 76, 16, 14};
            std::vector<Rectangle> shell_moving = {k1, k2, k3};
        }

        namespace Flying
        {
            Rectangle f1 = {4, 94, 16, 23};
            Rectangle f2 = {23, 93, 16, 24};
            std::vector<Rectangle> flying_ = {f1, f2};
        }
        Rectangle be_dying = {99, 103, 16, 14};
    }

    namespace Latiku
    {
        Rectangle fly_ = {194, 123, 16, 24};
        Rectangle throw_ = {213, 131, 16, 16};
        Rectangle be_fired = {175, 123, 16, 24};
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
        Rectangle be_fired_or_hit = {213, 150, 16, 16};
    }
    namespace Podoboo
    {
        Rectangle p1 = {289, 186, 14, 16};
        std::vector<Rectangle> normal_ = {p1};
    }
    namespace Cheep_Cheep
    {
        namespace normal_
        {
            Rectangle n1 = {99, 174, 16, 16};
            Rectangle n2 = {118, 174, 16, 16};
            std::vector<Rectangle> normal_ = {n1, n2};
        }
        namespace dying_
        {
            Rectangle d1 = {99, 212, 16, 16};
            std::vector<Rectangle> dying_ = {d1};
        }
    }
}

namespace BomberBill_Sprite
{
    SpriteSheet bomber_bill_;
    Rectangle n1 = {8, 82, 25, 15};
    Rectangle n2 = {38, 82, 25, 17};
    Rectangle n3 = {70, 79, 25, 21};
    Rectangle n4 = {99, 80, 26, 17};
    Rectangle n5 = {129, 82, 24, 15};
    Rectangle n6 = {158, 82, 25, 15};
    Rectangle n7 = {185, 80, 24, 19};
    Rectangle n8 = {216, 82, 25, 15};
    std::vector<Rectangle> bomber_bill_normal = {n1, n2, n3, n4, n5, n6, n7, n8};
}

namespace Bowser_Sprite
{
    SpriteSheet bowser_;
    namespace normal_
    {
        Rectangle n1 = {49, 21, 34, 41};
        std::vector<Rectangle> normal_ = {n1};
    }
    namespace fire_
    {
        Rectangle f1 = {50, 68, 35, 41};
        Rectangle f2 = {88, 68, 35, 41};
        std::vector<Rectangle> fire_ = {f1, f2};
    }
    namespace dying_
    {
        Rectangle d1 = {125, 21, 33, 41};
        std::vector<Rectangle> dying_ = {d1};
    }

    namespace fire_laser_
    {
        Rectangle f1 = {6, 38, 24, 13};
        std::vector<Rectangle> fire_laser_ = {f1};
    }
}
namespace Win_Animation
{
    SpriteSheet win_animation_;
    namespace flag_castle_2_side
    {
        Rectangle f1 = {1, 341, 14, 16};
        Rectangle f2 = {18, 341, 15, 16};
        Rectangle f3 = {1, 358, 14, 16};
        std::vector<Rectangle> flag_castle_2_side_ = {f1, f2, f3};
    }
    namespace flag_castle_top
    {
        Rectangle f1 = {1, 189, 13, 16};
        Rectangle f2 = {18, 189, 14, 16};
        Rectangle f3 = {35, 189, 14, 16};
        Rectangle f4 = {52, 189, 15, 16};
        std::vector<Rectangle> flag_castle_top_ = {f1, f2, f3, f4};
    }
    namespace flag_pole
    {
        Rectangle f1 = {1, 172, 16, 16};
        Rectangle f2 = {18, 172, 14, 16};
        Rectangle f3 = {35, 172, 11, 16};
        std::vector<Rectangle> flag_pole_ = {f1, f2, f3};
    }
}

namespace Intro
{
    SpriteSheet intro_;
    Rectangle mario = {4, 272, 14, 14};
    Rectangle luigi = {20, 270, 15, 16};
}

namespace Outro_Animation
{
    SpriteSheet outro_;
    namespace Mario
    {
        Rectangle o1 = {43, 32, 88, 75};
        Rectangle o2 = {163, 30, 88, 75};
        Rectangle o3 = {292, 31, 88, 74};
        Rectangle o4 = {423, 32, 87, 74};
        Rectangle o5 = {546, 32, 87, 74};
        Rectangle o6 = {693, 31, 85, 74};
        Rectangle o7 = {693, 31, 85, 74};
        std::vector<Rectangle> outro_mario = {o1, o2, o3, o4, o5, o6, o7};
    }
    namespace Luigi
    {
        Rectangle o1 = {44, 144, 85, 77};
        Rectangle o2 = {162, 142, 84, 77};
        Rectangle o3 = {292, 143, 87, 77};
        Rectangle o4 = {421, 142, 85, 77};
        Rectangle o5 = {549, 144, 84, 77};
        Rectangle o6 = {698, 142, 85, 77};
        Rectangle o7 = {698, 142, 85, 77};
        std::vector<Rectangle> outro_luigi = {o1, o2, o3, o4, o5, o6, o7};
    }
}

namespace SavePrince
{
    SpriteSheet save_prince_;
    namespace Kidnap
    {
        Rectangle k1 = {2, 4, 24, 29};
        Rectangle k2 = {28, 4, 22, 29};
        Rectangle k3 = {52, 11, 24, 22};
        Rectangle k4 = {2, 4, 24, 29};
        Rectangle k5 = {28, 4, 22, 29};
        Rectangle k6 = {52, 11, 24, 22};
        Rectangle k7 = {2, 4, 24, 29};
        Rectangle k8 = {28, 4, 22, 29};
        Rectangle k9 = {52, 11, 24, 22};
        Rectangle k10 = {104, 9, 24, 24};
        Rectangle k11 = {78, 17, 24, 16};
        Rectangle k12 = {130, 22, 24, 10};
        std::vector<Rectangle> kidnap_ = {k1, k2, k3, k4, k5, k6, k7, k8, k9, k10, k11, k12};
    }
    namespace Prince
    {
        Rectangle p1 = {186, 70, 16, 27};
        Rectangle p2 = {272, 73, 14, 24};
        Rectangle p3 = {114, 65, 15, 32};
        Rectangle p4 = {132, 65, 16, 32};
        Rectangle p5 = {150, 66, 16, 31};
        Rectangle p6 = {132, 65, 16, 32};
        std::vector<Rectangle> prince_ = {p1, p2, p3, p4, p5, p6};
    }
}

namespace Platform
{
    Rectangle vertical_ = {83, 206, 24, 8};
}