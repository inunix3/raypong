/*
 * Copyright (c) 2024 inunix3
 *
 * This file is licensed under the MIT License (see LICENSE.md).
 */

#include <raypong/state.h>
#include <raypong/defs.h>
#include <raypong/audio.h>
#include <raypong/score.h>
#include <raypong/ui.h>
#include <embed/raypong.h>

static void draw_frame(void) {
    DrawRectangleLinesEx(
        (Rectangle) {
            0.f,
            0.f,
            SCREEN_WIDTH,
            SCREEN_HEIGHT
        },
        FRAME_THICKNESS,
        FRAME_COLOR
    );
}

static void draw_separator_line(void) {
    DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, SEPARATOR_COLOR);
}

static void draw_scores(const State_t *s) {
    DrawText(
        s->score_1.str,
        SCREEN_WIDTH / 4 - s->score_1.width / 2,
        SCORE_Y_PAD,
        SCORE_FONT_SIZE,
        SCORE_COLOR
    );

    DrawText(
        s->score_2.str,
        3 * SCREEN_WIDTH / 4 - s->score_2.width / 2,
        SCORE_Y_PAD,
        SCORE_FONT_SIZE,
        SCORE_COLOR
    );
}

State_t state_new(void) {
    State_t s = { 0 };

    state_reset_game(&s);

    s.screen = SCREEN_MAIN_MENU;
    s.quit = false;
    s.after_goal_timer = timer_new();

    Image main_menu_bg_raw = LoadImageFromMemory(".png", ef_main_menu_bg, ARRAY_SIZE(ef_main_menu_bg));
    s.main_menu_bg = LoadTextureFromImage(main_menu_bg_raw);

    UnloadImage(main_menu_bg_raw);

    return s;
}

void state_deinit(State_t *s) {
    UnloadTexture(s->main_menu_bg);
}

void state_reset_game(State_t *s) {
    for (int i = 0; i < 2; ++i) {
        Rectangle *p = &s->paddles[i];

        p->width = PADDLE_WIDTH;
        p->height = PADDLE_HEIGHT;
        p->y = SCREEN_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f;
    }

    s->paddles[LEFT_PADDLE].x = PADDLE_PAD;
    s->paddles[RIGHT_PADDLE].x = SCREEN_WIDTH - (PADDLE_PAD + PADDLE_WIDTH);

    s->ball = ball_new();

    score_set(&s->score_1, 0);
    score_set(&s->score_2, 0);
}

void state_update(State_t *s, float dt) {
    state_handle_input(s, dt);

    if (s->screen == SCREEN_GAME) {
        if (s->mode == MODE_PLAYER_VS_AI && !s->waiting_after_goal) {
            state_update_ai(s, dt);
        }

        if (!s->waiting_after_goal) {
            ball_move(&s->ball, dt);
            state_handle_ball_collision(s);
        }

        if (s->waiting_after_goal && timer_done(s->after_goal_timer)) {
            s->waiting_after_goal = false;
            s->ball = ball_new();
        }
    }
}

void state_handle_input(State_t *s, float dt) {
    switch (s->screen) {
    case SCREEN_MAIN_MENU:
        return;
    case SCREEN_PAUSE:
        if (IsKeyPressed(KEY_ESCAPE)) {
            s->screen = SCREEN_MAIN_MENU;

            state_reset_game(s);
        }

        if (IsKeyPressed(KEY_SPACE)) s->screen = SCREEN_GAME;

        return;
    case SCREEN_GAME:
        if (IsKeyPressed(KEY_ESCAPE)) {
            s->screen = SCREEN_MAIN_MENU;

            state_reset_game(s);
        }

        if (IsKeyPressed(KEY_P)) s->screen = SCREEN_PAUSE;

        break;
    }

    if (s->waiting_after_goal) return;

    switch (s->mode) {
    case MODE_PLAYER_VS_PLAYER: {
        Rectangle *lp = &s->paddles[LEFT_PADDLE];

        if (IsKeyDown(KEY_W)) {
            paddle_move(lp, DIR_UP, dt, PADDLE_PLAYER_SPEED);
        } else if (IsKeyDown(KEY_S)) {
            paddle_move(lp, DIR_DOWN, dt, PADDLE_PLAYER_SPEED);
        }

        Rectangle *rp = &s->paddles[RIGHT_PADDLE];

        if (IsKeyDown(KEY_UP)) {
            paddle_move(rp, DIR_UP, dt, PADDLE_PLAYER_SPEED);
        } else if (IsKeyDown(KEY_DOWN)) {
            paddle_move(rp, DIR_DOWN, dt, PADDLE_PLAYER_SPEED);
        }

        break;
    } case MODE_PLAYER_VS_AI: {
        Rectangle *p = &s->paddles[s->player_paddle];

        if (s->player_paddle == LEFT_PADDLE && IsKeyDown(KEY_W)) {
            paddle_move(p, DIR_UP, dt, PADDLE_PLAYER_SPEED);
        } else if (s->player_paddle == LEFT_PADDLE && IsKeyDown(KEY_S)) {
            paddle_move(p, DIR_DOWN, dt, PADDLE_PLAYER_SPEED);
        }

        if (s->player_paddle == RIGHT_PADDLE && IsKeyDown(KEY_UP)) {
            paddle_move(p, DIR_UP, dt, PADDLE_PLAYER_SPEED);
        } else if (s->player_paddle == RIGHT_PADDLE && IsKeyDown(KEY_DOWN)) {
            paddle_move(p, DIR_DOWN, dt, PADDLE_PLAYER_SPEED);
        }
    } }
}

void state_update_ai(State_t *s, float dt) {
    Rectangle *p = &s->paddles[s->ai_paddle];

    if (p->y + PADDLE_HEIGHT / 2.f > s->ball.pos.y) {
        paddle_move(p, DIR_UP, dt, PADDLE_AI_SPEED);
    } else if (p->y + PADDLE_HEIGHT / 2.f < s->ball.pos.y) {
        paddle_move(p, DIR_DOWN, dt, PADDLE_AI_SPEED);
    }
}

void state_render(State_t *s) {
    BeginDrawing();

    ClearBackground(BG_COLOR);

    if (s->screen != SCREEN_MAIN_MENU) {
        draw_frame();
        draw_separator_line();

        DrawRectangleRec(s->paddles[LEFT_PADDLE], PADDLE_COLOR);
        DrawRectangleRec(s->paddles[RIGHT_PADDLE], PADDLE_COLOR);

        draw_scores(s);

        DrawCircleV(s->ball.pos, BALL_RADIUS, BALL_COLOR);
    }

    switch (s->screen) {
    case SCREEN_MAIN_MENU:
        DrawTexture(s->main_menu_bg, 0, 0, WHITE);
        ui_main_menu(s);

        break;
    case SCREEN_PAUSE:
        ui_pause_screen();

        break;
    default:
        break;
    }

    EndDrawing();
}

void state_handle_ball_collision(State_t *s) {
    Ball_t *b = &s->ball;

    Collision_t wall_collision = ball_check_wall_collision(*b);

    if (wall_collision.spot != COL_NONE) {
        state_handle_ball_wall_collision(s, wall_collision);
    }

    Collision_t lp_collision = ball_check_paddle_collision(*b, s->paddles[LEFT_PADDLE]);

    if (lp_collision.spot != COL_NONE) {
        ball_collide_paddle(b, lp_collision);
    }

    Collision_t rp_collision = ball_check_paddle_collision(*b, s->paddles[RIGHT_PADDLE]);

    if (rp_collision.spot != COL_NONE) {
        ball_collide_paddle(b, rp_collision);
    }
}

void state_handle_ball_wall_collision(State_t *s, Collision_t c) {
    Ball_t *b = &s->ball;

    switch (c.spot) {
    case COL_TOP:
    case COL_BOTTOM:
        audio_play(SAMPLE_WALL_HIT);

        b->pos.y += c.penetration;
        b->velocity.y = -b->velocity.y;

        break;
    case COL_RIGHT:
    case COL_LEFT:
        audio_play(SAMPLE_GOAL);

        timer_start(&s->after_goal_timer, DELAY_AFTER_GOAL);
        s->waiting_after_goal = true;

        if (c.spot == COL_RIGHT) {
            score_set(&s->score_1, s->score_1.value + 1);
        } else {
            score_set(&s->score_2, s->score_2.value + 1);
        }

        break;
    default:
        break;
    }
}
