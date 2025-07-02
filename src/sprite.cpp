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
    namespace Invincible_Super
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
        namespace Hit
        {
            Rectangle h1 = {971, 141, 14, 30};
            Rectangle h2 = {991, 139, 16, 30};
            //x6
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
    namespace Invincible_Super
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
        namespace Hit
        {
            Rectangle h1 = {971, 141, 14, 30};
            Rectangle h2 = {991, 139, 16, 30};
            //x6
            Rectangle h3 = {1012, 144, 16, 27};
            Rectangle h4 = {1033, 155, 16, 16};
            //
            Rectangle h5 = {1056, 156, 12, 15};
            std::vector<Rectangle> hit_ = {h1, h2, h3, h4, h5};
        }
    }
}
