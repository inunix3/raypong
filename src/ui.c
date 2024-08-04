/*
 * Copyright (c) 2024 inunix3
 *
 * This file is licensed under the MIT License (see LICENSE.md).
 */

#include <raypong/ui.h>

#if __clang__
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wconversion"
# pragma clang diagnostic ignored "-Wsign-conversion"
# pragma clang diagnostic ignored "-Wunused-parameter"
# pragma clang diagnostic ignored "-Wunused-variable"
# pragma clang diagnostic ignored "-Wimplicit-function-declaration"
# pragma clang diagnostic ignored "-Wshadow"
# pragma clang diagnostic ignored "-Wunused-but-set-variable"
# pragma clang diagnostic ignored "-Wimplicit-const-int-float-conversion"
#elif defined(__GNUC__)
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wconversion"
# pragma GCC diagnostic ignored "-Wsign-conversion"
# pragma GCC diagnostic ignored "-Wunused-parameter"
# pragma GCC diagnostic ignored "-Wunused-variable"
# pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
# pragma GCC diagnostic ignored "-Wshadow"
# pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#elif defined(_MSC_VER)
/* TODO: write pragma for MSVC */
#endif

#define RAYGUI_IMPLEMENTATION 1
#include <raygui.h>
#include "style_dark.h"

#if __clang__
# pragma clang diagnostic pop
#elif defined(__GNUC__)
# pragma GCC diagnostic pop
#elif defined(_MSC_VER)
/* TODO: write pragma for MSVC */
#endif

void ui_init(void) {
    GuiLoadStyleDark();
}

void ui_main_menu(State_t *s) {
    GuiPanel(
        (Rectangle) {
            SCREEN_WIDTH / 2.f - MAIN_MENU_WIDTH / 2.f,
            SCREEN_HEIGHT / 2.f - MAIN_MENU_HEIGHT / 2.f,
            MAIN_MENU_WIDTH,
            MAIN_MENU_HEIGHT
        },
        NULL
    );

    const float x = SCREEN_WIDTH / 2.f - BTN_WIDTH / 2.f;
    const float y_origin = SCREEN_HEIGHT / 2.f - MAIN_MENU_HEIGHT / 2.f + BTN_SPACING;
    const float spacing = BTN_HEIGHT + 10.f;

    if (
        GuiButton(
            (Rectangle) {
                x,
                y_origin,
                144.f,
                24.f
            },
            "#149#PLAYER VS PLAYER"
        )
    ) {
        s->mode = MODE_PLAYER_VS_PLAYER;
        s->screen = SCREEN_GAME;
    } else if (
        GuiButton(
            (Rectangle) {
                x,
                y_origin + spacing,
                144.f,
                24.f
            },
            "#206#PLAYER VS AI"
        )
    ) {
        s->player_paddle = LEFT_PADDLE;
        s->ai_paddle = RIGHT_PADDLE;

        s->mode = MODE_PLAYER_VS_AI;
        s->screen = SCREEN_GAME;
    } else if (
        GuiButton(
            (Rectangle) {
                x,
                y_origin + 2.f * spacing,
                144.f,
                24.f
            },
            "#206#AI VS PLAYER"
        )
    ) {
        s->player_paddle = RIGHT_PADDLE;
        s->ai_paddle = LEFT_PADDLE;

        s->mode = MODE_PLAYER_VS_AI;
        s->screen = SCREEN_GAME;
    } else if (
        GuiButton(
            (Rectangle) {
                x,
                y_origin + 3.f * spacing,
                144.f,
                24.f
            },
            "#159#EXIT"
        )
    ) {
        s->quit = true;
    }

    GuiLabel(
        (Rectangle) {
            x,
            y_origin + 4.f * spacing, 144.f, 24.f
        },
        TITLE
    );
}

void ui_pause_screen(void) {
    GuiPanel(
        (Rectangle) {
            SCREEN_WIDTH / 2.f - PAUSE_WIDTH / 2.f,
            SCREEN_HEIGHT / 2.f - PAUSE_HEIGHT / 2.f,
            PAUSE_WIDTH,
            PAUSE_HEIGHT
        },
        NULL
    );

    const float label_x = SCREEN_WIDTH / 2.f - PAUSE_WIDTH / 2.f + 10.f;
    const float y_origin = SCREEN_HEIGHT / 2.f - PAUSE_HEIGHT / 2.f - 5.f;

    GuiLabel(
        (Rectangle) {
            label_x,
            y_origin + 16.f,
            104.f,
            16.f
        },
        "Game is paused."
    );
    GuiLabel(
        (Rectangle) {
            label_x,
            y_origin + 32.f,
            160.f,
            16.f
        },
        "Press SPACE to continue."
    );
    GuiLabel(
        (Rectangle) {
            label_x,
            y_origin + 48.f,
            250.f,
            16.f
        },
        "Press ESCAPE to exit to the main menu."
    );
}
