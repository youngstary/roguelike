#include "Gui.h"
#include "Components.h"
#include <raylib.h>

#ifndef RAYGUI_IMPLEMENTATION
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#endif

Gui::Gui(State state) {
    ChangeLayout(state);
    GuiLoadStyleDefault();
}

void Gui::ChangeLayout(State state) {
    const float screenWidth = GetScreenWidth();
    const float screenHeight = GetScreenHeight();
    const float buttonWidth = 120.0f;
    const float buttonHeight = 24.0f;
    const float spacing = 24.0f;

    switch (state) {
    case PAUSE: {
        const float groupWidth = 168.0f;
        const float groupHeight = 168.0f;
        Vector2 anchor = {screenWidth / 2.0f - groupWidth / 2.0f,
                          screenHeight / 2.0f - groupHeight / 2.0f};
        layoutRecs[0] = Rectangle{anchor.x, anchor.y, groupWidth, groupHeight};
        layoutRecs[1] = Rectangle{anchor.x + spacing, anchor.y,
                                  buttonWidth + spacing, buttonHeight};
        layoutRecs[2] = Rectangle{anchor.x + spacing, anchor.y,
                                  buttonWidth + spacing * 2, buttonHeight};
        layoutRecs[3] = Rectangle{anchor.x + spacing, anchor.y,
                                  buttonWidth + spacing * 3, buttonHeight};
        static_assert(3 < NUM_RECS, "NUM_RECS too small");
        break;
    }
    default:
        break;
    }
}

State Gui::Draw(State state) {
    const int screenWidth = GetScreenWidth();
    const int screenHeigth = GetScreenHeight();

    State newState = state;

    DrawFPS(10, 10); // Show current FPS

    TraceLog(LOG_INFO, "Drawing GUI: %d", state);

    switch (state) {
    case PLAYING:
        break;
    case PAUSE:
        DrawRectangle(0, 0, screenWidth, screenHeigth,
                      {0, 0, 0, static_cast<unsigned char>(255 * 0.5f)});
        GuiGroupBox(layoutRecs[0], "PAUSE");
        if (GuiButton(layoutRecs[1], "RESUME")) {
            newState = PLAYING;
        }
        if (GuiButton(layoutRecs[2], "SETTINGS")) {
            /*newState = SETTINGS;*/
        }
        if (GuiButton(layoutRecs[3], "RETURN TO MENU")) {
            newState = MAIN_MENU;
        }
        break;
    case MAIN_MENU:
        break;
    default:
        TraceLog(LOG_WARNING, "Case not handled: %d", state);
        break;
    }

    return newState;
}
