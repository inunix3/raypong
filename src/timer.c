/*
 * Copyright (c) 2024 inunix3
 *
 * This file is licensed under the MIT License (see LICENSE.md).
 */

#include <raypong/timer.h>

Timer_t timer_new(void) {
    return (Timer_t) { 0, 0 };
}

void timer_start(Timer_t *t, double life_time) {
    t->start_time = GetTime();
    t->life_time = life_time;
}

double timer_elapsed(Timer_t t) {
    return GetTime() - t.start_time;
}

bool timer_done(Timer_t t) {
    return timer_elapsed(t) >= t.life_time;
}
