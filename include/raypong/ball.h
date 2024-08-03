/*
 * Copyright (c) 2024 inunix3
 *
 * This file is licensed under the MIT License (see LICENSE.md).
 */

#pragma once

#include "collision.h"
#include "paddle.h"

#include <raylib.h>

typedef struct Ball {
    Vector2 pos;
    Vector2 velocity;
} Ball_t;

Ball_t ball_new(void);
Collision_t ball_check_wall_collision(Ball_t b);
Collision_t ball_check_paddle_collision(Ball_t b, Paddle_t p);
void ball_collide_paddle(Ball_t *b, Collision_t c);
void ball_move(Ball_t *b, float dt);
