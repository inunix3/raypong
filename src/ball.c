/*
 * Copyright (c) 2024 inunix3
 *
 * This file is licensed under the MIT License (see LICENSE.md).
 */

#include <raypong/ball.h>
#include <raypong/audio.h>

#include <raymath.h>

#include <assert.h>
#include <stddef.h>

static bool rand_bool(void) {
    return GetRandomValue(0, 1);
}

static void circle_quarter_coords(Vector2 center, float radius, float *l, float *r, float *t, float *b) {
    assert(l != NULL);
    assert(r != NULL);
    assert(t != NULL);
    assert(b != NULL);

    *l = center.x - radius;
    *r = center.x + radius;
    *t = center.y - radius;
    *b = center.y + radius;
}

static void rect_side_coords(Rectangle rect, float *l, float *r, float *t, float *b) {
    assert(l != NULL);
    assert(r != NULL);
    assert(t != NULL);
    assert(b != NULL);

    *l = rect.x;
    *r = rect.x + rect.width;
    *t = rect.y;
    *b = rect.y + rect.height;
}

Ball_t ball_new(void) {
    Ball_t b;

    b.pos = (Vector2) {
        SCREEN_WIDTH / 2.f,
        SCREEN_HEIGHT / 2.f
    };

    bool horizontal_path = rand_bool();

    if (horizontal_path) {
        b.velocity = (Vector2) {
            rand_bool() ? 10.f : -10.f,
            rand_bool() ? 00.f :  00.f
        };
    } else {
        b.velocity = (Vector2) {
            rand_bool() ? 10.f : -10.f,
            rand_bool() ? 06.f : -06.f
        };
    }

    b.velocity = Vector2Scale(b.velocity, BALL_SPEED);

    return b;
}

Collision_t ball_check_wall_collision(Ball_t b) {
    float bl, br, bt, bb;
    circle_quarter_coords(b.pos, BALL_RADIUS, &bl, &br, &bt, &bb);

    Collision_t c = { COL_NONE, 0.f };

    if (bb >= SCREEN_HEIGHT) {
        c.spot = COL_BOTTOM;
        c.penetration = SCREEN_HEIGHT - bb;
    } else if (bt <= 0.f) {
        c.spot = COL_TOP;
        c.penetration = -bt;
    } else if (br > SCREEN_WIDTH) {
        c.spot = COL_RIGHT;
    } else if (bl < 0) {
        c.spot = COL_LEFT;
    }

    return c;
}

Collision_t ball_check_paddle_collision(Ball_t b, Paddle_t p) {
    float bl, br, bt, bb;
    circle_quarter_coords(b.pos, BALL_RADIUS, &bl, &br, &bt, &bb);

    float pl, pr, pt, pb;
    rect_side_coords(p, &pl, &pr, &pt, &pb);

    if (bl >= pr ||
        br <= pl ||
        bt >= pb ||
        bb <= pt) {
        return (Collision_t) { COL_NONE, 0.f };
    }

    Collision_t c;

    if (b.velocity.x < 0) {
        /* Left paddle */

        c.penetration = pr - bl;
    } else if (b.velocity.x > 0) {
        /* Right paddle */

        c.penetration = pl - br;
    }

    float top_range = pb - 2.f * PADDLE_HEIGHT / 3.f;
    float middle_range = pb - PADDLE_HEIGHT / 3.f;

    if (bb > pt && bb < top_range) {
        c.spot = COL_TOP;
    } else if (bb > top_range && bb < middle_range) {
        c.spot = COL_MIDDLE;
    } else {
        c.spot = COL_BOTTOM;
    }

    return c;
}

void ball_collide_paddle(Ball_t *b, Collision_t c) {
    audio_play(SAMPLE_PADDLE_HIT);

    b->pos.x += c.penetration;
    b->velocity.x = -b->velocity.x;

    if (c.spot == COL_TOP) {
        b->velocity.y = -6.f * BALL_SPEED;
    } else if (c.spot == COL_BOTTOM) {
        b->velocity.y = 6.f * BALL_SPEED;
    }
}

void ball_move(Ball_t *b, float dt) {
    b->pos = Vector2Add(b->pos, Vector2Scale(b->velocity, dt));
}
