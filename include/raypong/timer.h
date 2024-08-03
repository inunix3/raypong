/*
 * Copyright (c) 2024 inunix3
 *
 * This file is licensed under the MIT License (see LICENSE.md).
 */

#pragma once

#include <raylib.h>

typedef struct Timer {
    double start_time;
    double life_time; /* in seconds */
} Timer_t;

Timer_t timer_new(void);
void timer_start(Timer_t *t, double life_time);
double timer_elapsed(Timer_t t);
bool timer_done(Timer_t t);
