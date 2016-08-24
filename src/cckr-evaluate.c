//
//  cckr-evaluate.c
//  cckr
//
//  Author: Cosim
//  Copyright © 2009年 Sestall. All rights reserved.
//

#include "cckr-evaluate.h"
#include "cckr-private.h"

const cckr_evaluate_func_t cckr_evaluater_array[] = {
    cckr_evaluate_none,
    cckr_evaluate_naive,
    cckr_evaluate_simple,
    cckr_evaluate_upper
};

int cckr_evaluate_none(cckr_t *pcckr, int side) {
    return 100;
}

int cckr_evaluate_naive(cckr_t *pcckr, int side) {
    return  cckr_get_avaible_count_for_side(pcckr, side)*10;
}

int cckr_evaluate_simple(cckr_t *pcckr, int side) {
    int y, oy, ly = 0, sum = 0;
    FOREACH_AVAIABLES_BEGIN(pcckr, 1, ch, dch, {oy = IDX2Y(ch); y = 0;});
    {
        ly = IDX2Y(dch);
//        if (y < ly) y = ly;
    }
    FOREACH_AVAIABLES_END(pcckr, 1, ch, dch, {sum += ly*100;});
    
    return sum;
}

int cckr_evaluate_upper(cckr_t *pcckr, int side) {
    int y, ly = 10, sum = 0;
    for (int i = 0; i < CCKR_LEN; ++i) {
        if (CCKR_MANI(pcckr, i) == side) {
            y = 20-cckr_table_y[side-1][i];
            sum += y*y*10;
            if(--ly==0)break;
        }
    }
    
    return -sum;
}