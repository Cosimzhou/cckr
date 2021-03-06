//
//  cckr-common.c
//  cckr
//
//  Author: Cosim
//  Copyright © 2009年 Sestall. All rights reserved.
//

#ifndef __CCKR_CONST_H__
#define __CCKR_CONST_H__


#define cckr_board_char_space   ' '
#define cckr_board_char_null    '_'
#define cckr_board_char_1       'O'
#define cckr_board_char_2       '@'
#define cckr_board_char_3       '*'
#define cckr_board_char_4       '#'
#define cckr_board_char_5       'x'
#define cckr_board_char_6       'm'

#define cckr_table_4x           (*cckr_table_x)
#define cckr_table_4y           (*cckr_table_y)

#define cckr_table_rotate_1     (cckr_table_rotate[1])
#define cckr_table_rotate_2     (cckr_table_rotate[2])
#define cckr_table_rotate_3     (cckr_table_rotate[3])
#define cckr_table_rotate_4     (cckr_table_rotate[4])
#define cckr_table_rotate_5     (cckr_table_rotate[5])

extern const char cckr_board_place_holder_space[];
extern const char cckr_chess_man_char[];
extern const char *cckr_table_x[];
extern const char *cckr_table_y[];
extern const char *cckr_table_rotate[];
extern const char *cckr_table_next_move[];

extern const char *cckr_table_reverse[];
extern const char *cckr_nest_indices[];

#endif /* __CCKR_CONST_H__ */