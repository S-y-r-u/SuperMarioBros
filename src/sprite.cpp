#include "../include/sprite.h"

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
            Rectangle stance = {6, 50, 14, 17};
            std::vector<Rectangle> stance_ = {stance};
        }
        namespace Jump
        {
            Rectangle jump = {48, 49, 18, 18};
            std::vector<Rectangle> jump_ = {jump};
        }
        namespace Die
        {
            Rectangle die = {93, 49, 16, 18};
            std::vector<Rectangle> die_ = {die};
        }
        namespace Walk
        {
            Rectangle w1 = {6, 92, 14, 16};
            Rectangle w2 = {27, 92, 14, 16};
            Rectangle w3 = {47, 92, 15, 16};
            std::vector<Rectangle> walk_ = {w1, w2, w3};
        }
        namespace Slide
        {
            Rectangle slide = {134, 133, 15, 18};
            std::vector<Rectangle> slide_ = {slide};
        }
        namespace Climb
        {
            Rectangle c1 = {5, 175, 15, 18};
            Rectangle c2 = {27, 175, 15, 17};
            std::vector<Rectangle> climb_ = {c1, c2};
        }
        namespace Enter_Pipe
        {
            Rectangle enter = {515, 121, 16, 30};
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
            // x3
            Rectangle s1 = {179, 151, 12, 16};
            Rectangle s2 = {199, 145, 16, 22};
            //
            Rectangle s3 = {220, 137, 14, 30};
            Rectangle s4 = {241, 151, 14, 17};
            Rectangle s5 = {261, 144, 16, 24};
            Rectangle s6 = {283, 137, 14, 30};
            std::vector<Rectangle> small_to_super = {s1, s2, s3, s4, s5, s6};
        }
    }

    namespace Invincible
    {
        namespace Stance
        {
            Rectangle s1 = {7, 291, 13, 16};
            Rectangle s2 = {28, 291, 13, 16};
            Rectangle s3 = {49, 291, 13, 16};
            Rectangle s4 = {70, 291, 13, 16};
            std::vector<Rectangle> stance_ = {s1, s2, s3, s4};
        }
        namespace Jump
        {
            Rectangle j1 = {175, 290, 17, 18};
            Rectangle j2 = {195, 290, 17, 18};
            Rectangle j3 = {216, 290, 17, 18};
            Rectangle j4 = {237, 290, 17, 18};
            std::vector<Rectangle> jump_ = {j1, j2, j3, j4};
        }
        namespace Walk
        {
            Rectangle w1 = {6, 334, 14, 15};
            Rectangle w2 = {27, 334, 14, 15};
            Rectangle w3 = {46, 333, 16, 17};
            Rectangle w4 = {70, 333, 13, 17};
            Rectangle w5 = {91, 333, 13, 17};
            Rectangle w6 = {110, 332, 15, 18};
            Rectangle w7 = {132, 333, 14, 16};
            Rectangle w8 = {153, 333, 14, 17};
            Rectangle w9 = {172, 332, 17, 18};
            Rectangle w10 = {196, 334, 12, 15};
            Rectangle w11 = {236, 333, 16, 17};
            Rectangle w12 = {258, 333, 14, 17};
            std::vector<Rectangle> walk_ = {w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12};
        }
        namespace Climb
        {
            Rectangle c1 = {6, 489, 15, 18};
            Rectangle c2 = {27, 489, 15, 17};
            Rectangle c3 = {48, 489, 15, 18};
            Rectangle c4 = {69, 489, 15, 17};
            Rectangle c5 = {90, 489, 15, 18};
            Rectangle c6 = {111, 489, 15, 17};
            Rectangle c7 = {132, 489, 15, 18};
            Rectangle c8 = {153, 489, 15, 17};
            std::vector<Rectangle> climb_ = {c1, c2, c3, c4, c5, c6, c7, c8};
        }
        namespace Slide
        {
            Rectangle s1 = {364, 447, 15, 18};
            Rectangle s2 = {386, 447, 15, 18};
            Rectangle s3 = {407, 447, 15, 18};
            Rectangle s4 = {428, 447, 15, 18};
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
            Rectangle s1 = {6, 416, 14, 17};
            Rectangle s2 = {27, 416, 14, 17};
            Rectangle s3 = {48, 416, 14, 17};
            Rectangle s4 = {68, 409, 15, 24};
            Rectangle s5 = {90, 416, 14, 17};
            Rectangle s6 = {110, 409, 15, 24};
            Rectangle s7 = {132, 416, 14, 17};
            Rectangle s8 = {153, 409, 15, 24};
            Rectangle s9 = {173, 401, 16, 32};
            Rectangle s10 = {195, 416, 14, 17};
            Rectangle s11 = {215, 409, 15, 24};
            Rectangle s12 = {236, 401, 16, 32};
            Rectangle s13 = {259, 416, 12, 16};
            // x2
            Rectangle s14 = {278, 401, 16, 31};
            Rectangle s15 = {299, 401, 16, 31};
            Rectangle s16 = {320, 401, 16, 31};
            Rectangle s17 = {341, 401, 16, 31};
            //
            std::vector<Rectangle> small_to_super = {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16, s17};
        }
    }

    namespace Super
    {
        namespace Stance
        {
            Rectangle stance = {385, 35, 16, 32};
            std::vector<Rectangle> stance_ = {stance};
        }
        namespace Stance_To_Fire
        {
            // x3
            Rectangle s1 = {792, 212, 16, 32};
            Rectangle s2 = {814, 212, 16, 32};
            Rectangle s3 = {834, 212, 16, 32};
            Rectangle s4 = {855, 212, 16, 32};
            //
            std::vector<Rectangle> stance_to_fire = {s1, s2, s3, s4};
        }
        namespace Crouch
        {
            Rectangle crouch = {428, 43, 18, 24};
            std::vector<Rectangle> crouch_ = {crouch};
        }
        namespace Crouch_To_Fire
        {
            // x3
            Rectangle c1 = {1147, 255, 18, 24};
            Rectangle c2 = {1168, 255, 18, 24};
            Rectangle c3 = {1189, 255, 18, 24};
            Rectangle c4 = {1210, 255, 18, 24};
            //
            std::vector<Rectangle> crouch_to_fire = {c1, c2, c3, c4};
        }
        namespace Jump
        {
            Rectangle jump = {478, 34, 17, 31};
            std::vector<Rectangle> jump_ = {jump};
        }
        namespace Jump_To_Fire
        {
            // x3
            Rectangle j1 = {791, 246, 18, 32};
            Rectangle j2 = {812, 246, 18, 32};
            Rectangle j3 = {833, 246, 18, 32};
            Rectangle j4 = {854, 246, 18, 32};
            //
            std::vector<Rectangle> jump_to_fire = {j1, j2, j3, j4};
        }
        namespace Walk
        {
            Rectangle w1 = {386, 77, 15, 32};
            Rectangle w2 = {405, 77, 18, 31};
            Rectangle w3 = {426, 77, 18, 31};
            std::vector<Rectangle> walk_ = {w1, w2, w3};
        }
        namespace Walk_To_Fire
        {
            // x3
            Rectangle w1 = {969, 213, 18, 31};
            Rectangle w2 = {990, 213, 18, 31};
            Rectangle w3 = {1011, 213, 18, 31};
            Rectangle w4 = {1032, 213, 18, 31};
            //
            std::vector<Rectangle> walk_to_fire = {w1, w2, w3, w4};
        }
        namespace Slide
        {
            Rectangle slide = {521, 34, 18, 33};
            std::vector<Rectangle> slide_ = {slide};
        }
        namespace Slide_To_Fire
        {
            // x3
            Rectangle s1 = {969, 247, 18, 31};
            Rectangle s2 = {990, 247, 18, 31};
            Rectangle s3 = {1011, 247, 18, 31};
            Rectangle s4 = {1032, 247, 18, 31};
            //
            std::vector<Rectangle> slide_to_fire = {s1, s2, s3, s4};
        }
        namespace Climb
        {
            Rectangle c1 = {429, 120, 16, 30};
            Rectangle c2 = {450, 120, 16, 28};
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
            Rectangle h1 = {615, 131, 15, 32};
            Rectangle h2 = {636, 131, 16, 30};
            // x6
            Rectangle h3 = {657, 135, 16, 27};
            Rectangle h4 = {678, 146, 16, 16};
            //
            Rectangle h5 = {701, 147, 12, 15};
            std::vector<Rectangle> hit_ = {h1, h2, h3, h4, h5};
        }
    }

    namespace Invincible_Super_And_Fire
    {
        namespace Stance
        {
            Rectangle s1 = {557, 331, 16, 32};
            Rectangle s2 = {579, 331, 16, 32};
            Rectangle s3 = {599, 331, 16, 32};
            Rectangle s4 = {620, 331, 16, 32};
            std::vector<Rectangle> stance_ = {s1, s2, s3, s4};
        }
        namespace Jump
        {
            Rectangle j1 = {727, 330, 17, 32};
            Rectangle j2 = {747, 330, 17, 32};
            Rectangle j3 = {768, 330, 17, 32};
            Rectangle j4 = {789, 330, 17, 32};
            std::vector<Rectangle> jump_ = {j1, j2, j3, j4};
        }
        namespace Crouch
        {
            Rectangle c1 = {726, 387, 18, 24};
            Rectangle c2 = {747, 387, 18, 24};
            Rectangle c3 = {768, 387, 18, 24};
            Rectangle c4 = {789, 387, 18, 24};
            std::vector<Rectangle> crouch_ = {c1, c2, c3, c4};
        }
        namespace Slide
        {
            Rectangle s1 = {557, 479, 16, 32};
            Rectangle s2 = {578, 479, 16, 32};
            Rectangle s3 = {599, 479, 16, 32};
            Rectangle s4 = {619, 479, 16, 32};
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
            Rectangle s1 = {727, 463, 15, 32};
            Rectangle s2 = {748, 463, 15, 32};
            Rectangle s3 = {769, 463, 15, 32};
            Rectangle s4 = {790, 463, 15, 32};
            std::vector<Rectangle> shoot_fire = {s1, s2, s3, s4};
        }
        namespace Walk
        {
            Rectangle w1 = {557, 373, 16, 32};
            Rectangle w2 = {578, 437, 16, 32};
            Rectangle w3 = {598, 405, 18, 31};
            Rectangle w4 = {620, 373, 15, 31};
            Rectangle w5 = {557, 438, 16, 31};
            Rectangle w6 = {578, 406, 18, 31};
            Rectangle w7 = {599, 373, 16, 32};
            Rectangle w8 = {620, 437, 16, 32};
            Rectangle w9 = {557, 406, 16, 29};
            Rectangle w10 = {578, 373, 16, 32};
            Rectangle w11 = {599, 437, 16, 32};
            Rectangle w12 = {620, 405, 16, 31};
            std::vector<Rectangle> walk_ = {w1, w2, w3, w4, w5, w6, w7, w7, w9, w10, w11, w12};
        }
        namespace Enter_Pipe
        {
            Rectangle e1 = {897, 332, 16, 3};
            Rectangle e2 = {918, 332, 16, 3};
            Rectangle e3 = {939, 332, 16, 3};
            Rectangle e4 = {960, 332, 16, 3};
            std::vector<Rectangle> enter_pipe = {e1, e2, e3, e4};
        }
    }

    namespace Fire
    {
        namespace Stance
        {
            Rectangle stance = {793, 35, 16, 32};
            std::vector<Rectangle> stance_ = {stance};
        }
        namespace Crouch
        {
            Rectangle crouch = {836, 43, 18, 24};
            std::vector<Rectangle> crouch_ = {crouch};
        }
        namespace Jump
        {
            Rectangle jump = {886, 34, 17, 31};
            std::vector<Rectangle> jump_ = {jump};
        }
        namespace Walk
        {
            Rectangle w1 = {794, 77, 15, 32};
            Rectangle w2 = {814, 77, 18, 31};
            Rectangle w3 = {835, 77, 18, 31};
            std::vector<Rectangle> walk_ = {w1, w2, w3};
        }
        namespace Slide
        {
            Rectangle slide = {930, 34, 18, 33};
            std::vector<Rectangle> slide_ = {slide};
        }
        namespace Climb
        {
            Rectangle c1 = {838, 120, 16, 30};
            Rectangle c2 = {859, 120, 16, 28};
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
            Rectangle h2 = {991, 139, 16, 30};
            // x6
            Rectangle h3 = {1012, 144, 16, 27};
            Rectangle h4 = {1033, 155, 16, 16};
            //
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
            Rectangle stance = {6, 50, 14, 17};
            std::vector<Rectangle> stance_ = {stance};
        }
        namespace Jump
        {
            Rectangle jump = {48, 49, 18, 18};
            std::vector<Rectangle> jump_ = {jump};
        }
        namespace Die
        {
            Rectangle die = {93, 49, 16, 18};
            std::vector<Rectangle> die_ = {die};
        }
        namespace Walk
        {
            Rectangle w1 = {6, 92, 14, 16};
            Rectangle w2 = {27, 92, 14, 16};
            Rectangle w3 = {47, 92, 15, 16};
            std::vector<Rectangle> walk_ = {w1, w2, w3};
        }
        namespace Slide
        {
            Rectangle slide = {134, 133, 15, 18};
            std::vector<Rectangle> slide_ = {slide};
        }
        namespace Enter_Pipe
        {
            Rectangle enter = {515, 121, 16, 30};
            std::vector<Rectangle> enter_pipe = {enter};
        }
        namespace Climb
        {
            Rectangle c1 = {5, 175, 15, 18};
            Rectangle c2 = {27, 175, 15, 17};
            std::vector<Rectangle> climb_ = {c1, c2};
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
            // x3
            Rectangle s1 = {179, 151, 12, 16};
            Rectangle s2 = {199, 145, 16, 22};
            //
            Rectangle s3 = {220, 137, 14, 30};
            Rectangle s4 = {241, 151, 14, 17};
            Rectangle s5 = {261, 144, 16, 24};
            Rectangle s6 = {283, 137, 14, 30};
            std::vector<Rectangle> small_to_super = {s1, s2, s3, s4, s5, s6};
        }
    }

    namespace Invincible
    {
        namespace Stance
        {
            Rectangle s1 = {7, 291, 13, 16};
            Rectangle s2 = {28, 291, 13, 16};
            Rectangle s3 = {49, 291, 13, 16};
            Rectangle s4 = {70, 291, 13, 16};
            std::vector<Rectangle> stance_ = {s1, s2, s3, s4};
        }
        namespace Jump
        {
            Rectangle j1 = {175, 290, 17, 18};
            Rectangle j2 = {195, 290, 17, 18};
            Rectangle j3 = {216, 290, 17, 18};
            Rectangle j4 = {237, 290, 17, 18};
            std::vector<Rectangle> jump_ = {j1, j2, j3, j4};
        }
        namespace Walk
        {
            Rectangle w1 = {6, 334, 14, 15};
            Rectangle w2 = {27, 334, 14, 15};
            Rectangle w3 = {46, 333, 16, 17};
            Rectangle w4 = {70, 333, 13, 17};
            Rectangle w5 = {91, 333, 13, 17};
            Rectangle w6 = {110, 332, 15, 18};
            Rectangle w7 = {132, 333, 14, 16};
            Rectangle w8 = {153, 333, 14, 17};
            Rectangle w9 = {172, 332, 17, 18};
            Rectangle w10 = {196, 334, 12, 15};
            Rectangle w11 = {236, 333, 16, 17};
            Rectangle w12 = {258, 333, 14, 17};
            std::vector<Rectangle> walk_ = {w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12};
        }
        namespace Climb
        {
            Rectangle c1 = {6, 489, 15, 18};
            Rectangle c2 = {27, 489, 15, 17};
            Rectangle c3 = {48, 489, 15, 18};
            Rectangle c4 = {69, 489, 15, 17};
            Rectangle c5 = {90, 489, 15, 18};
            Rectangle c6 = {111, 489, 15, 17};
            Rectangle c7 = {132, 489, 15, 18};
            Rectangle c8 = {153, 489, 15, 17};
            std::vector<Rectangle> climb_ = {c1, c2, c3, c4, c5, c6, c7, c8};
        }
        namespace Slide
        {
            Rectangle s1 = {364, 447, 15, 18};
            Rectangle s2 = {386, 447, 15, 18};
            Rectangle s3 = {407, 447, 15, 18};
            Rectangle s4 = {428, 447, 15, 18};
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
            Rectangle s1 = {6, 416, 14, 17};
            Rectangle s2 = {27, 416, 14, 17};
            Rectangle s3 = {48, 416, 14, 17};
            Rectangle s4 = {68, 409, 15, 24};
            Rectangle s5 = {90, 416, 14, 17};
            Rectangle s6 = {110, 409, 15, 24};
            Rectangle s7 = {132, 416, 14, 17};
            Rectangle s8 = {153, 409, 15, 24};
            Rectangle s9 = {173, 401, 16, 32};
            Rectangle s10 = {195, 416, 14, 17};
            Rectangle s11 = {215, 409, 15, 24};
            Rectangle s12 = {236, 401, 16, 32};
            Rectangle s13 = {259, 416, 12, 16};
            // x2
            Rectangle s14 = {278, 401, 16, 31};
            Rectangle s15 = {299, 401, 16, 31};
            Rectangle s16 = {320, 401, 16, 31};
            Rectangle s17 = {341, 401, 16, 31};
            //
            std::vector<Rectangle> small_to_super = {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16, s17};
        }
    }

    namespace Super
    {
        namespace Stance
        {
            Rectangle stance = {385, 35, 16, 32};
            std::vector<Rectangle> stance_ = {stance};
        }
        namespace Stance_To_Fire
        {
            // x3
            Rectangle s1 = {792, 212, 16, 32};
            Rectangle s2 = {814, 212, 16, 32};
            Rectangle s3 = {834, 212, 16, 32};
            Rectangle s4 = {855, 212, 16, 32};
            //
            std::vector<Rectangle> stance_to_fire = {s1, s2, s3, s4};
        }
        namespace Crouch
        {
            Rectangle crouch = {428, 43, 18, 24};
            std::vector<Rectangle> crouch_ = {crouch};
        }
        namespace Crouch_To_Fire
        {
            // x3
            Rectangle c1 = {1147, 255, 18, 24};
            Rectangle c2 = {1168, 255, 18, 24};
            Rectangle c3 = {1189, 255, 18, 24};
            Rectangle c4 = {1210, 255, 18, 24};
            //
            std::vector<Rectangle> crouch_to_fire = {c1, c2, c3, c4};
        }
        namespace Jump
        {
            Rectangle jump = {478, 34, 17, 31};
            std::vector<Rectangle> jump_ = {jump};
        }
        namespace Jump_To_Fire
        {
            // x3
            Rectangle j1 = {791, 246, 18, 32};
            Rectangle j2 = {812, 246, 18, 32};
            Rectangle j3 = {833, 246, 18, 32};
            Rectangle j4 = {854, 246, 18, 32};
            //
            std::vector<Rectangle> jump_to_fire = {j1, j2, j3, j4};
        }
        namespace Walk
        {
            Rectangle w1 = {386, 77, 15, 32};
            Rectangle w2 = {405, 77, 18, 31};
            Rectangle w3 = {426, 77, 18, 31};
            std::vector<Rectangle> walk_ = {w1, w2, w3};
        }
        namespace Walk_To_Fire
        {
            // x3
            Rectangle w1 = {969, 213, 18, 31};
            Rectangle w2 = {990, 213, 18, 31};
            Rectangle w3 = {1011, 213, 18, 31};
            Rectangle w4 = {1032, 213, 18, 31};
            //
            std::vector<Rectangle> walk_to_fire = {w1, w2, w3, w4};
        }
        namespace Slide
        {
            Rectangle slide = {521, 34, 18, 33};
            std::vector<Rectangle> slide_ = {slide};
        }
        namespace Slide_To_Fire
        {
            // x3
            Rectangle s1 = {969, 247, 18, 31};
            Rectangle s2 = {990, 247, 18, 31};
            Rectangle s3 = {1011, 247, 18, 31};
            Rectangle s4 = {1032, 247, 18, 31};
            //
            std::vector<Rectangle> slide_to_fire = {s1, s2, s3, s4};
        }
        namespace Climb
        {
            Rectangle c1 = {429, 120, 16, 30};
            Rectangle c2 = {450, 120, 16, 28};
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
            Rectangle h1 = {615, 131, 15, 32};
            Rectangle h2 = {636, 131, 16, 30};
            // x6
            Rectangle h3 = {657, 135, 16, 27};
            Rectangle h4 = {678, 146, 16, 16};
            //
            Rectangle h5 = {701, 147, 12, 15};
            std::vector<Rectangle> hit_ = {h1, h2, h3, h4, h5};
        }
    }

    namespace Invincible_Super_And_Fire
    {
        namespace Stance
        {
            Rectangle s1 = {557, 331, 16, 32};
            Rectangle s2 = {579, 331, 16, 32};
            Rectangle s3 = {599, 331, 16, 32};
            Rectangle s4 = {620, 331, 16, 32};
            std::vector<Rectangle> stance_ = {s1, s2, s3, s4};
        }
        namespace Jump
        {
            Rectangle j1 = {727, 330, 17, 32};
            Rectangle j2 = {747, 330, 17, 32};
            Rectangle j3 = {768, 330, 17, 32};
            Rectangle j4 = {789, 330, 17, 32};
            std::vector<Rectangle> jump_ = {j1, j2, j3, j4};
        }
        namespace Crouch
        {
            Rectangle c1 = {726, 387, 18, 24};
            Rectangle c2 = {747, 387, 18, 24};
            Rectangle c3 = {768, 387, 18, 24};
            Rectangle c4 = {789, 387, 18, 24};
            std::vector<Rectangle> crouch_ = {c1, c2, c3, c4};
        }
        namespace Slide
        {
            Rectangle s1 = {557, 479, 16, 32};
            Rectangle s2 = {578, 479, 16, 32};
            Rectangle s3 = {599, 479, 16, 32};
            Rectangle s4 = {619, 479, 16, 32};
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
            Rectangle s1 = {727, 463, 15, 32};
            Rectangle s2 = {748, 463, 15, 32};
            Rectangle s3 = {769, 463, 15, 32};
            Rectangle s4 = {790, 463, 15, 32};
            std::vector<Rectangle> shoot_fire = {s1, s2, s3, s4};
        }
        namespace Walk
        {
            Rectangle w1 = {557, 373, 16, 32};
            Rectangle w2 = {578, 437, 16, 32};
            Rectangle w3 = {598, 405, 18, 31};
            Rectangle w4 = {620, 373, 15, 31};
            Rectangle w5 = {557, 438, 16, 31};
            Rectangle w6 = {578, 406, 18, 31};
            Rectangle w7 = {599, 373, 16, 32};
            Rectangle w8 = {620, 437, 16, 32};
            Rectangle w9 = {557, 406, 16, 29};
            Rectangle w10 = {578, 373, 16, 32};
            Rectangle w11 = {599, 437, 16, 32};
            Rectangle w12 = {620, 405, 16, 31};
            std::vector<Rectangle> walk_ = {w1, w2, w3, w4, w5, w6, w7, w7, w9, w10, w11, w12};
        }
        namespace Enter_Pipe
        {
            Rectangle e1 = {897, 332, 16, 3};
            Rectangle e2 = {918, 332, 16, 3};
            Rectangle e3 = {939, 332, 16, 3};
            Rectangle e4 = {960, 332, 16, 3};
            std::vector<Rectangle> enter_pipe = {e1, e2, e3, e4};
        }
    }

    namespace Fire
    {
        namespace Stance
        {
            Rectangle stance = {793, 35, 16, 32};
            std::vector<Rectangle> stance_ = {stance};
        }
        namespace Crouch
        {
            Rectangle crouch = {836, 43, 18, 24};
            std::vector<Rectangle> crouch_ = {crouch};
        }
        namespace Jump
        {
            Rectangle jump = {886, 34, 17, 31};
            std::vector<Rectangle> jump_ = {jump};
        }
        namespace Walk
        {
            Rectangle w1 = {794, 77, 15, 32};
            Rectangle w2 = {814, 77, 18, 31};
            Rectangle w3 = {835, 77, 18, 31};
            std::vector<Rectangle> walk_ = {w1, w2, w3};
        }
        namespace Slide
        {
            Rectangle slide = {930, 34, 18, 33};
            std::vector<Rectangle> slide_ = {slide};
        }
        namespace Climb
        {
            Rectangle c1 = {838, 120, 16, 30};
            Rectangle c2 = {859, 120, 16, 28};
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
            Rectangle h2 = {991, 139, 16, 30};
            // x6
            Rectangle h3 = {1012, 144, 16, 27};
            Rectangle h4 = {1033, 155, 16, 16};
            //
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

namespace Font
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