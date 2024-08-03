/*
 * Copyright (c) 2024 inunix3
 *
 * This file is licensed under the MIT License (see LICENSE.md).
 */

#include <raypong/paddle.h>
#include <raypong/defs.h>

#include <raymath.h>

void paddle_move(Paddle_t *p, Direction_t dir, float speed, float dt) {
    float step = dir == DIR_DOWN ? 1.f : -1.f;

    p->y += step * speed * dt;
    p->y = Clamp(p->y, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);
}
