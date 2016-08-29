//
//  cckr-common.c
//  cckr
//
//  Author: Cosim
//  Copyright © 2009年 Sestall. All rights reserved.
//
#include "cckr.h"
#ifndef __CCKR_COMMON_H__
#define __CCKR_COMMON_H__

typedef unsigned char byte;
typedef byte cckr_index_t;
typedef byte cckr_chessman_t;

typedef struct {
    cckr_index_t orig;
    cckr_index_t dest;
} cckr_move_t;

typedef struct {
    cckr_move_t move;
    short step;
} cckr_path_node_t;

typedef struct {
    cckr_chessman_t cchm[CCKR_LEN];
    union {
        char xx[6];
    };
} cckr_t;

//typedef struct {
//    cckr_index_t buff[200];
//} CAAC;

typedef int (*cckr_evaluate_func_t)(cckr_t *, int);
typedef int (*cckr_traversal_inner_func_t)(void*);

typedef struct {
    cckr_t *pcckr;
    int max_depth;
    int depth;
    int val;
    int side;
    void *param;
    cckr_traversal_inner_func_t func;
    cckr_evaluate_func_t endfunc;
    cckr_index_t stack[128];
} cckr_traverse_param_t;

typedef struct {
    cckr_move_t history[1024];
    int size;
    //    int capacity;
} cckr_step_history;


typedef struct {
    int best;
    cckr_step_history history;
    cckr_index_t step[16*2];
    int side;
} cckr_traverse_optimize_param_t;



//void cckr_step_history_init(cckr_step_history*);
//void cckr_step_history_clean(cckr_step_history*);


int cckr_game_board_init(cckr_t *pcckr);
int cckr_game_board_recover(cckr_t *pcckr, cckr_step_history *history);


int cckr_print(cckr_t *pcckr);
int cckr_print_to_string_kernel(cckr_t *pcckr, const char *patt, char *buff);
int cckr_print_to_string(cckr_t *pcckr, char *buff);
int cckr_print_to_string_4colrow(cckr_t *pcckr, char *buff);
int cckr_print_avaible_to_string(cckr_index_t *result, char *string, int count);

int cckr_get_avaible_count_for_side(cckr_t *pcckr, cckr_index_t side);
int cckr_get_avaible_for_side(cckr_t *pcckr, cckr_index_t side, cckr_index_t *buff);
int cckr_get_path_between_move(cckr_t *pcckr, cckr_index_t s, cckr_index_t e, cckr_index_t *path);
int cckr_get_short_path_string(cckr_t *pcckr, cckr_index_t s, cckr_index_t e, char *buff);

int cckr_evaluate_board_score(cckr_t *pcckr, int side);

int cckr_traversal(cckr_t *pcckr, int depth, cckr_traversal_inner_func_t func, cckr_evaluate_func_t evalfunc, void *param);

int cckr_traversal_inner(void *ptr);


void cckr_step_history_copy(cckr_step_history *dest, cckr_index_t *src, int size);
void cckr_step_history_copy_history(cckr_step_history *dest, cckr_step_history *src);
void cckr_step_history_append(cckr_step_history *dest, cckr_index_t *step, int size);
void cckr_step_history_append_history(cckr_step_history *dest, cckr_step_history *src);

#endif /* __CCKR_COMMON_H__ */