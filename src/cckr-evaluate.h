//
//  cckr-evaluate.h
//  cckr
//
//  Author: Cosim
//  Copyright © 2009年 Sestall. All rights reserved.
//

#include "cckr.h"
#ifndef __CCKR_EVALUATE_H__
#define __CCKR_EVALUATE_H__

typedef enum {
    CCKR_EVALUATE_NONE,
    CCKR_EVALUATE_NAIVE,
    CCKR_EVALUATE_SIMPLE,
    CCKR_EVALUATE_UPPER,
} cckr_evaluate_func_id_t;


int cckr_evaluate_none(cckr_t *pcckr, int side);
int cckr_evaluate_naive(cckr_t *pcckr, int side);
int cckr_evaluate_simple(cckr_t *pcckr, int side);
int cckr_evaluate_upper(cckr_t *pcckr, int side);
int cckr_evaluate_x(cckr_t *pcckr, int side);

extern const cckr_evaluate_func_t cckr_evaluater_array[];


int cckr_evaluate_board_score(cckr_t *pcckr, int side);
int cckr_evaluate_board_score_x(cckr_t *pcckr, int side);

#endif /* __CCKR_EVALUATE_H__ */