/*
 * Copyright (c) 2024 inunix3
 *
 * This file is licensed under the MIT License (see LICENSE.md).
 */

#include <raypong/score.h>

#include <stdio.h>

void score_set(ScoreLabel_t *s, unsigned new_value) {
    s->value = new_value;
    snprintf(s->str, SCORE_MAX_LEN + 1, "%u", s->value);
    s->width = MeasureText(s->str, SCORE_FONT_SIZE);
}
