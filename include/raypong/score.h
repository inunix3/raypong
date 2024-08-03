/*
 * Copyright (c) 2024 inunix3
 *
 * This file is licensed under the MIT License (see LICENSE.md).
 */

#pragma once

#include "defs.h"

typedef struct ScoreLabel {
    unsigned value;
    char str[SCORE_MAX_LEN + 1];
    int width;
} ScoreLabel_t;

void score_set(ScoreLabel_t *s, unsigned new_value);
