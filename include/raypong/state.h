/*
 * Copyright (c) 2024 inunix3
 *
 * This file is licensed under the MIT License (see LICENSE.md).
 */

#pragma once

#include "ball.h"
#include "score.h"
#include "timer.h"

#include <raylib.h>

#include <stdbool.h>

typedef enum Screen {
    SCREEN_MAIN_MENU,
    SCREEN_PAUSE,
    SCREEN_GAME
} Screen_t;

typedef enum Mode {
    MODE_PLAYER_VS_PLAYER,
    MODE_PLAYER_VS_AI
} Mode_t;

typedef struct State {
    Rectangle paddles[2];
    Ball_t ball;
    ScoreLabel_t score_1;
    ScoreLabel_t score_2;

    unsigned player_paddle;
    unsigned ai_paddle;

    Screen_t screen;
    Mode_t mode;
    bool quit;

    Timer_t after_goal_timer;
    bool waiting_after_goal;

    Texture2D main_menu_bg;
} State_t;

State_t state_new(void);
void state_deinit(State_t *s);
void state_reset_game(State_t *s);
void state_update(State_t *s, float dt);
void state_handle_input(State_t *s, float dt);
void state_update_ai(State_t *s, float dt);
void state_render(State_t *s);
void state_handle_ball_collision(State_t *s);
void state_handle_ball_wall_collision(State_t *s, Collision_t c);
