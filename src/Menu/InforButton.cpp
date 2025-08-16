#include "Menu/InfoButton.h"
#include "raylib.h"
#include "sprite.h"
#include <iostream>

InfoButton::InfoButton(): BackButton(80, 80, 40, CircleButton::BACK){
    MenuTexture = &MenuImages::GetInstance().menuTexture;
}

InfoButton::~InfoButton(){

}

void InfoButton::Draw(){
    DrawTexture(*MenuTexture, 0, 0, WHITE);
    BackButton.Draw();

    std::string TitleText = "GROUP 1";
    float font_scale = 9.0f;
    int text_width = (int)(TitleText.size() * 8 * font_scale + 1.0f);
    int titleX = (Screen_w - text_width) / 2;
    Font_Sprite::DrawText(TitleText, titleX, 100, WHITE, font_scale);
    
    std::string InfoText1 = "24125011-Le Chi Hung";
    std::string InfoText2 = "24125057-Tran Dang Le Huy";
    std::string InfoText3 = "24125079-Tran Dinh Quoc Thang";
    std::string InfoText4 = "24125080-Huynh Le Bao Thi";
    Font_Sprite::DrawText(InfoText1, 335, 300, WHITE, 2.5f);
    Font_Sprite::DrawText(InfoText2, 335, 350, WHITE, 2.5f);
    Font_Sprite::DrawText(InfoText3, 335, 400, WHITE, 2.5f);
    Font_Sprite::DrawText(InfoText4, 33, 450, WHITE, 2.5f);
}

int InfoButton::Update(){
    if(BackButton.Update()) return menuState;
    return InfoState;
}
