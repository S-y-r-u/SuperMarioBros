#include "Outro.h"
#include "raylib.h"

// Shader code nhúng trực tiếp
static const char *circleMaskFS = R"(
#version 330
in vec2 fragTexCoord;
out vec4 finalColor;

uniform sampler2D texture0;
uniform vec2 resolution; 
uniform vec2 center;     
uniform float radius;    

void main()
{
    vec2 uv_px = fragTexCoord * resolution;
    float dist = distance(uv_px, center);

    vec4 col = texture(texture0, fragTexCoord);
    if (dist > radius) col.a = 0.0;

    finalColor = col;
}
)";

Outro::Outro(Player_Mode mode)
    : animation(nullptr),
      radius(0.0f),
      player_mode(mode)
{
    shader_ = LoadShaderFromMemory(nullptr, circleMaskFS);
    uResolution_ = GetShaderLocation(shader_, "resolution");
    uCenter_ = GetShaderLocation(shader_, "center");
    uRadius_ = GetShaderLocation(shader_, "radius");
    if (mode == Player_Mode::MARIO_PLAYER)
        animation = Animation(&Outro_Animation::outro_, Outro_Animation::Mario::outro_mario, 0.5f);
    else if (mode == Player_Mode::LUIGI_PLAYER)
        animation = Animation(&Outro_Animation::outro_, Outro_Animation::Luigi::outro_luigi, 0.5f);
}

Outro::~Outro()
{
    UnloadShader(shader_);
}

void Outro::Run()
{
    float dt = GetFrameTime();

    // Nếu chưa tới frame cuối => lớn dần
    if (animation.Get_Frame_Index() < animation.Get_Frame_Count() - 1)
    {
        if (radius < Max_Radius)
        {
            radius += 100.0f * dt;
            if (radius > Max_Radius)
                radius = Max_Radius;
        }
    }
    else if (animation.Get_Frame_Index() == animation.Get_Frame_Count() - 1)
    {
        animation.Set_Rec(animation.Get_Current_Rec());
        // Frame cuối => thu nhỏ dần
        if (radius > 0.0f)
        {
            radius -= 100.0f * dt;
            if (radius < 0.0f)
                radius = 0.0f;
        }
    }

    animation.Update(dt);
}

void Outro::Draw()
{
    Rectangle src = animation.Get_Current_Rec();
    SpriteSheet &sprite = animation.Get_Sprite();

    // Lấy kích thước sau khi scale
    float drawW = src.width * scale_screen;
    float drawH = src.height * scale_screen;

    // Tâm màn hình
    float centerX = GetScreenWidth() / 2.0f;
    float centerY = GetScreenHeight() / 2.0f;

    // Tính vị trí để texture nằm giữa màn hình
    Vector2 pos = {centerX - drawW / 2.0f, centerY - drawH / 2.0f};

    // Tâm hình tròn (trong pixel, relative với ảnh đã scale)
    Vector2 center_px = {drawW / 2.0f, drawH / 2.0f};

    // Set uniform cho shader
    float res[2] = {drawW, drawH};
    float center[2] = {center_px.x, center_px.y};
    SetShaderValue(shader_, uResolution_, res, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader_, uCenter_, center, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader_, uRadius_, &radius, SHADER_UNIFORM_FLOAT);

    BeginShaderMode(shader_);
    // Vẽ texture đã scale, ở giữa màn hình
    DrawTexturePro(
        sprite.sprite,         // texture gốc
        src,                          // vùng lấy từ sprite sheet
        {pos.x, pos.y, drawW, drawH}, // vùng đích sau khi scale
        {0, 0},                       // origin (không xoay, nên để 0)
        0.0f,                         // rotation
        WHITE);
    EndShaderMode();
}

bool Outro::Change_State()
{
    return (animation.Get_Frame_Index() == animation.Get_Frame_Count() - 1) && (radius <= 0.0f);
}
