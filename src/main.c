/*
 * Copyright (c) 2024 inunix3
 *
 * This file is licensed under the MIT License (see LICENSE.md).
 */

#include <raypong/audio.h>
#include <raypong/state.h>
#include <raypong/ui.h>

#include <raylib.h>

#include <time.h>

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);

    SetRandomSeed((unsigned int) time(NULL));
    SetExitKey(KEY_NULL);
    SetTargetFPS(MAX_FPS);

    audio_init();

    ui_init();

    State_t s = state_new();

    while (!s.quit) {
        if (WindowShouldClose()) {
            s.quit = true;
        }

        float dt = GetFrameTime();

        state_update(&s, dt);
        state_render(&s);
    }

    state_deinit(&s);
    audio_deinit();
    CloseWindow();

    return 0;
}
