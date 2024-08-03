/*
 * Copyright (c) 2024 inunix3
 *
 * This file is licensed under the MIT License (see LICENSE.md).
 */

#pragma once

#include <raylib.h>

#define VERSION "1.0"
#define TITLE "raypong v" VERSION

/*
 * Window size and graphics settings
 */

#define SCREEN_WIDTH 750
#define SCREEN_HEIGHT 330
#define MAX_FPS 60

/*
 * Audio settings
 */

#define AUDIO_VOLUME 0.4f

/*
 * Paddle settings
 */

#define PADDLE_WIDTH 7.f
#define PADDLE_HEIGHT 45.f
#define PADDLE_PLAYER_SPEED 400.f
#define PADDLE_AI_SPEED 224.7f
#define PADDLE_PAD 7.f

/*
 * Ball settings
 */

#define BALL_RADIUS 6.f
#define BALL_SPEED 42.f

/*
 * Score texts settings
 */

#define SCORE_FONT_SIZE 80
#define SCORE_Y_PAD 25
#define SCORE_X_PAD 150
#define SCORE_MAX_LEN 3

#define FRAME_THICKNESS 3.f

/*
 * Colors
 */

#define BG_COLOR         (Color) {  23,  24,  25, 255 }
#define PADDLE_COLOR     (Color) { 100, 135, 140, 255 }
#define BALL_COLOR       (Color) { 138, 196, 195, 255 }
#define SCORE_COLOR      (Color) { 100, 135, 140, 255 }
#define FRAME_COLOR      (Color) {  44,  52,  56, 255 }
#define SEPARATOR_COLOR  (Color) {  44,  52,  56, 255 }

/*
 * UI
 */

#define BTN_WIDTH 144
#define BTN_HEIGHT 24
#define BTN_SPACING 26
#define MAIN_MENU_WIDTH 192
#define MAIN_MENU_HEIGHT 195
#define PAUSE_WIDTH 288.f
#define PAUSE_HEIGHT 72.f

/*
 * Indices
 */

#define LEFT_PADDLE 0
#define RIGHT_PADDLE 1

/*
 * Miscellaneous
 */

#define DELAY_AFTER_GOAL 0.7

#define ARRAY_SIZE(_a) (sizeof(_a) / sizeof((_a)[0]))

typedef enum Direction {
    DIR_UP,
    DIR_DOWN,
    DIR_RIGHT,
    DIR_LEFT
} Direction_t;
