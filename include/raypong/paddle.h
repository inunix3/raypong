/*
 * Copyright (c) 2024 inunix3
 *
 * This file is licensed under the MIT License (see LICENSE.md).
 */

#pragma once

#include "defs.h"

#include <raylib.h>

typedef Rectangle Paddle_t;

void paddle_move(Paddle_t *p, Direction_t dir, float speed, float dt);
