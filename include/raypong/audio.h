/*
 * Copyright (c) 2024 inunix3
 *
 * This file is licensed under the MIT License (see LICENSE.md).
 */

#pragma once

typedef enum SampleId {
    SAMPLE_WALL_HIT,
    SAMPLE_PADDLE_HIT,
    SAMPLE_GOAL
} SampleId_t;

void audio_init(void);
void audio_deinit(void);
void audio_play(SampleId_t id);
