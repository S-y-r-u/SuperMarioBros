#include "UI.h"

UI::UI()
{
    SearchAndSetResourceDir("resources");
}

void UI::Process()
{
    InitWindow(Screen_w, Screen_h, "Mario Game");
    SetTargetFPS(120);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitAudioDevice();

    MenuImages::GetInstance().Load();
    SoundManager::GetInstance().LoadSounds();
    SoundManager::GetInstance().LoadMusic();

    // Bắt đầu với menu music
    SoundManager::GetInstance().PlayMusic("MenuMusic", true);

    Menu *menu = new Menu();
    ChoosingStageState *choosingStage = new ChoosingStageState();
    GameManager *gameManager = new GameManager();
    SettingState *settingMenu = new SettingState();
    ChoosingCharacter *choosingCharacter = new ChoosingCharacter();
    GameOver *gameOver = new GameOver();
    TimeUp *timeUp = new TimeUp();
    ContinueState *continueState = new ContinueState();
    InfoButton *infoButton = new InfoButton();

    Program_state = menuState;
    int previousState = menuState; // Track previous state để quản lý music

    gameManager->Load_Texture();

    while (!WindowShouldClose())
    {
        // Quản lý music khi state thay đổi
        if (Program_state != previousState)
        {
            // Stop current music
            if (Program_state == gameManagerState || previousState == gameManagerState || previousState == gameOverState)
            {
                SoundManager::GetInstance().StopMusic();
                if (Program_state == menuState)
                {
                    SoundManager::GetInstance().PlayMusic("MenuMusic", true);
                }
                else if (Program_state == gameManagerState)
                {
                    SoundManager::GetInstance().PlayMusic("playingMusic", true);
                }
                else if (Program_state == gameOverState)
                {
                    SoundManager::GetInstance().PlayMusic("gameover", true);
                }
            }
            previousState = Program_state;
        }
        SoundManager::GetInstance().Update();
        // Update logic
        if (Program_state == ProgramState::menuState)
        {
            Program_state = menu->Update();
            if (Program_state == ProgramState::gameManagerState)
            {
                {
                    gameManager->SetGameMode(Game_Mode::Play_Through);
                    gameManager->SetDifficulty(Difficulty::Easy);
                }
                // gameManager->SetCharacter(choosingCharacter->GetCharacter());
            }
        }
        else if (Program_state == ProgramState::continueState)
        {
            Program_state = continueState->Update();
            if (Program_state == ProgramState::gameManagerState)
            {
                std::ifstream fin("save.json");
                if (fin.is_open())
                {
                    json j = json::parse(fin);
                    gameManager->from_json(j);
                    fin.close();
                    std::cout << "[DEBUG] Loaded game state from save.json\n";
                }
                else {
                    std::cerr << "[ERROR] Failed to open save.json\n";
                }
            }
        }
        else if (Program_state == ProgramState::choosingStageState)
        {
            Program_state = choosingStage->Update();
            if (Program_state == ProgramState::gameManagerState)
            {
                gameManager->SetGameMode(Game_Mode::Play_Level);
                gameManager->SetDifficulty(choosingStage->GetSelectedDifficulty());
            }
        }
        else if (Program_state == ProgramState::gameManagerState)
        {
            Program_state = gameManager->Update();
            if (Program_state == ProgramState::gameOverState)
                gameOver->SetPlayerInformation(&gameManager->GetPlayerInformation());
            if (Program_state == ProgramState::timeUpState)
                timeUp->SetPlayerInformation(&gameManager->GetPlayerInformation());
        }
        else if (Program_state == ProgramState::settingState)
        {
            Program_state = settingMenu->Update();
        }
        else if (Program_state == ProgramState::choosingCharacterState)
        {
            Program_state = choosingCharacter->Update();
            gameManager->SetPlayerMode(choosingCharacter->GetCharacter());
        }
        else if (Program_state == ProgramState::gameOverState)
        {
            Program_state = gameOver->Update();
        }
        else if (Program_state == ProgramState::timeUpState)
        {
            Program_state = timeUp->Update();
        }
        else if(Program_state == ProgramState :: InfoState){
            Program_state = infoButton->Update();
        }
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (Program_state == ProgramState::menuState || Program_state == ProgramState::continueState)
        {
            menu->Draw();
        }
        else if (Program_state == ProgramState::choosingStageState)
        {
            choosingStage->Draw();
        }
        else if (Program_state == ProgramState::gameManagerState)
        {
            gameManager->Draw();
        }
        else if (Program_state == ProgramState::settingState)
        {
            settingMenu->Draw();
        }
        else if (Program_state == ProgramState::choosingCharacterState)
        {
            choosingCharacter->Draw();
        }
        else if (Program_state == ProgramState::gameOverState)
        {
            gameOver->Draw();
        }
        else if (Program_state == ProgramState::timeUpState)
        {
            timeUp->Draw();
        }
        else if(Program_state == ProgramState::InfoState){
            infoButton->Draw();
        }

        EndDrawing();
        CursorManager::Update_(); // Cập nhật con trỏ mỗi frame
    }

    // Cleanup
    SoundManager::GetInstance().StopMusic();
    gameManager->Unload_Texture();
    SoundManager::GetInstance().UnloadAll();
    MenuImages::GetInstance().Unload();
    delete menu;
    delete choosingStage;
    delete gameManager;
    delete settingMenu;
    delete choosingCharacter;

    CloseAudioDevice();
    CloseWindow();
}