//
//  cckr.h
//  cckr
//
//  Author: Cosim
//  Copyright © 2009年 Sestall. All rights reserved.
//

#ifndef cckr_h
#define cckr_h

#define CCKR_NUM    121
#define CCKR_TRAVERSAL(pcckr)       cckr_traversal(pcckr, -1)

typedef unsigned char byte;

typedef struct {
    byte cchm[CCKR_NUM];
    union {
        char xx[7];
    };
} CCKR;

typedef struct {
    byte buff[200];
} CAAC;

int test(int);

int cckr_init_game_board(CCKR *pcckr);

int cckr_print_to_string(CCKR *pcckr, char *buff);
int cckr_print_avaible_to_string(byte *result, char *string, int count);

int cckr_evaluate_board_score(CCKR *pcckr, int side);

int cckr_traversal(CCKR *pcckr, int depth);

#endif /* cckr_h */
