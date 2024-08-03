/*
 * Copyright (c) 2024 inunix3
 *
 * This file is licensed under the MIT License (see LICENSE.md).
 */

#pragma once

typedef enum CollisionSpot {
    COL_NONE,
    COL_TOP,
    COL_MIDDLE,
    COL_BOTTOM,
    COL_RIGHT,
    COL_LEFT,
} CollisionSpot_t;

typedef struct Collision {
    CollisionSpot_t spot;
    float penetration;
} Collision_t;
