//
//  cckr-tools.c
//  cckr
//
//  Author: Cosim
//  Copyright © 2009年 Sestall. All rights reserved.
//

#include "cckr-tools.h"
#include "cckr-private.h"
#include <stdio.h>

void table_next_make() {
    printf("const char *cckr_table_next_a = ");
    for (int i = 0; i < CCKR_LEN; ++i) {
        if (i%11 == 0) printf("\"");
        printf("\\%03o", INEXT_A(i));
        if (i%11 == 10) printf("\"\n");
    }
    printf("\";\n");
}

void table_rotate_make() {
    char text[200] = "\"\\000", *sp = text+5;
    printf("const char *cckr_table_rotate_a = \n");
    for (int i = 16; i >= 0; --i) {
        for (int j = 0; j < 17; ++j) {
            int val = cckr_table_reverse[j][i];
            if (val) {
                sp += sprintf(sp, "\\%03o", val);
                if (sp > text+4*11) {
                    printf("%s\"\n",text);
                    sp = text;
                    *sp++ = '"';
                    *sp = 0;
                }
            }
        }
    }
    printf("%s\";\n",text);
    
    printf("const char *cckr_table_rotate_y = \n");
    for (int i = 0; i < 17; ++i) {
        for (int j = 0; j < 17; ++j) {
            int val = cckr_table_reverse[i][j];
            if (val) {
                sp += sprintf(sp, "\\%03o", i+j-7);
                if (sp > text+4*11) {
                    printf("%s\"\n",text);
                    sp = text;
                    *sp++ = '"';
                    *sp = 0;
                }
            }
        }
    }
    printf("%s\";\n",text);
}

void table_rotate_x_make() {
    char text[200] = "\"", *sp = text+1;
    printf("const char *cckr_table_rotate_b = \n");
    for (int i = 0; i < CCKR_LEN; ++i) {
        sp += sprintf(sp, "\\%03o", cckr_table_rotate[3][cckr_table_rotate[0][i]]);
        if (sp > text+4*11) {
            printf("%s\"\n",text);
            sp = text;
            *sp++ = '"';
            *sp = 0;
        }
    }
    printf("%s\";\n",text);
}
void table_ruler_y_make() {
    char text[200] = "\"", *sp = text+1;
    printf("const char *(*cckr_table_y)_5 = \n");
    for (int i = 0; i < CCKR_LEN; ++i) {
        sp += sprintf(sp, "\\%03o", (*cckr_table_y)[cckr_table_rotate[4][i]]);
        if (sp > text+4*11) {
            printf("%s\"\n",text);
            sp = text;
            *sp++ = '"';
            *sp = 0;
        }
    }
    printf("%s\";\n",text);
}

void table_ruler_x_make() {
    char text[200], *sp;
    *text = '"';
    for (int d = 1; d < 6; ++d) {
        printf("    //      direction %d \n", d);
        sp = text+1;
        for (int i = 0; i < CCKR_LEN; ++i) {
            sp += sprintf(sp, "\\%03o", cckr_table_4x[cckr_table_rotate[d][i]]);
            if (sp > text+4*11) {
                printf("%s\"\n",text);
                sp = text+1;
                *sp = 0;
            }
        }
        printf("%s\",\n",text);
    }
}

void table_rotate_check() {
    char buff[2048];
    cckr_t cckr;
    cckr_game_board_init(&cckr);
    cckr_print(&cckr);
    
    
    for (int i = 0; i < CCKR_LEN; ++i)
        CCKR_MANI(&cckr, i) = (*cckr_table_y)[i];
    cckr_print_to_string_4colrow(&cckr, buff);
    printf("%s", buff);
    
    for (int i = 0; i < CCKR_LEN; ++i)
        CCKR_MANI(&cckr, i) = (*cckr_table_y)[cckr_table_rotate[4][i]];
    cckr_print_to_string_4colrow(&cckr, buff);
    printf("%s", buff);
}

void table_ruler_x_check() {
    char buff[2048];
    cckr_t cckr;
    cckr_game_board_init(&cckr);
    cckr_print(&cckr);
    
    for (int d = 0; d < 6; ++d) {
        printf("--------------------\n");
        for (int i = 0; i < CCKR_LEN; ++i)
            CCKR_MANI(&cckr, i) = cckr_table_y[d][i];
        cckr_print_to_string_4colrow(&cckr, buff);
        printf("%s>\n", buff);
        
        for (int i = 0; i < CCKR_LEN; ++i)
            CCKR_MANI(&cckr, i) = cckr_table_x[d][i];
        cckr_print_to_string_4colrow(&cckr, buff);
        printf("%s", buff);
    }
}

void test_path_between_move() {
    cckr_t cckr = {0};

    CCKR_MANI(&cckr, 16) = 1;
//    CCKR_MANI(&cckr, 17) = 1;
    CCKR_MANI(&cckr, 30) = 1;
    CCKR_MANI(&cckr, 28) = 1;
    CCKR_MANI(&cckr, 40) = 1;
    
    cckr_index_t s = 16, e = 18;
    cckr_index_t buffer[100];
    int l = cckr_get_path_between_move(&cckr, s, e, buffer)-1;
        
    CCKR_MOVE(&cckr, s, e);
    CCKR_MANI(&cckr, s)=2;
    for (int j = 0; j < l; ++j) {
        CCKR_MANI(&cckr, buffer[j]) = 2;
    }
        
    cckr_print(&cckr);
        
    CCKR_MANI(&cckr, s)=0;
    for (int j = 0; j < l; ++j) {
        CCKR_MANI(&cckr, buffer[j]) = 0;
    }
}


int test(int ii) {
    char text[100];
    cckr_t cckr;
    cckr_traverse_optimize_param_t ctop={0};
    cckr_move_t *move = ctop.history.history;
    
    cckr_game_board_init(&cckr);
    //    cckr_game_board_recover(&cckr, &csh);

    cckr_print(&cckr);

    ctop.side = 1;
    for (int i = 0; i < 40; ++i) {
        ctop.best = - CCKR_INT_MAX;
        cckr_traversal(&cckr, CCKR_SEARCH_DEPTH, cckr_traversal_inner, cckr_evaluate_board_score, &ctop);

        cckr_get_short_path_string(&cckr, move->orig, move->dest, text);
        CCKR_MOVE(&cckr, move->orig, move->dest);
        cckr_print(&cckr);
        printf("No %d step, move %d to %d, %s.\n"
               "-------------------------\n", i+1, move->orig, move->dest, text);
        
        ctop.side = 5-ctop.side;
    }
    
    
//    for (int i = 0; i < csh.size; ++i) {
//        cckr_get_short_path_string(&cckr, csh.history[i].orig, csh.history[i].dest, text);
//        
//        cckr_index_t buffer[100];
//        int l = cckr_get_path_between_move(&cckr,csh.history[i].orig, csh.history[i].dest, buffer)-1;
//
//        CCKR_MOVE(&cckr, csh.history[i].orig, csh.history[i].dest);
//        CCKR_MANI(&cckr, csh.history[i].orig)=2;
//        for (int j = 0; j < l; ++j) {
//            CCKR_MANI(&cckr, buffer[j]) = 2;
//        }
//        
//        cckr_print(&cckr);
//
//        CCKR_MANI(&cckr, csh.history[i].orig)=0;
//        for (int j = 0; j < l; ++j) {
//            CCKR_MANI(&cckr, buffer[j]) = 0;
//        }
//        
//    }
//    
//    
//    //    cckr_get_short_path_string(&cckr, csh.history[6], csh.history[7], text);
//    
//    //    cckr_print(&cckr);
//    //    cckr_get_path_between_move(&cckr, 52, 93, NULL);
//    
//    cckr_index_t buff[100];
//    int len = cckr_get_path_between_move(&cckr, 16, 81, buff);
//    printf("%d ", 16);
//    for (int i = 0; i < len; ++i) {
//        printf("%d ", buff[i]);
//    }
//    printf("\n");
    
    return 0;
}

int test1(){
    cckr_traverse_optimize_param_t ctop={0};
    cckr_step_history rcsh={0};
    
    cckr_t cckr;
    cckr_game_board_init(&cckr);
    
    cckr_traversal(&cckr, CCKR_SEARCH_DEPTH, cckr_traversal_inner, cckr_evaluate_board_score, &ctop);
    cckr_step_history_append_history(&rcsh, &ctop.history);
    cckr_game_board_recover(&cckr, &rcsh);
    
    ctop.best = 0;
    cckr_traversal(&cckr, CCKR_SEARCH_DEPTH, cckr_traversal_inner, cckr_evaluate_board_score, &ctop);
    cckr_step_history_append_history(&rcsh, &ctop.history);
    cckr_game_board_recover(&cckr, &rcsh);
    
    ctop.best = -CCKR_INT_MAX;
    cckr_traversal(&cckr, CCKR_SEARCH_DEPTH, cckr_traversal_inner, cckr_evaluate_board_score_x, &ctop);
    cckr_step_history_append_history(&rcsh, &ctop.history);
    
    
    cckr_game_board_init(&cckr);
    for (int i = 0; i < rcsh.size; ++i) {
        CCKR_MOVE(&cckr, rcsh.history[i].orig, rcsh.history[i].dest);
        cckr_print(&cckr);
        printf("No %d step, move %d to %d.\n"
               "-------------------------\n", i+1, rcsh.history[i].orig, rcsh.history[i].dest);
    }
    
    return 0;
}


int aitest(){
    cckr_step_history csh = {
        .history = {
            {7, 16},
            {2, 29},
            {6, 40},
            {8, 30},
            {1, 42},
            {42, 52},
            {3, 53},
            {4, 61},
            {5, 43},
            {10, 71},
            {16, 81},
            {52, 93},
            {9, 17},
            {29, 72},
            {17, 105},
            {43, 83},
            {40, 41},
            {71, 114},
            {114, 117},
            {30, 119},
        },
        .size = 20//12
    };
    
    cckr_t cckr;
    cckr_traverse_optimize_param_t ctop={0};
    cckr_game_board_recover(&cckr, &csh);
    
    ctop.best = -CCKR_INT_MAX;
    cckr_traversal(&cckr, CCKR_SEARCH_DEPTH, cckr_traversal_inner, cckr_evaluate_board_score, &ctop);
    cckr_step_history_append_history(&csh, &ctop.history);
    cckr_game_board_recover(&cckr, &csh);
    
    
    cckr_game_board_init(&cckr);
    char text[100];
    for (int i = 0; i < csh.size; ++i) {
        cckr_get_short_path_string(&cckr, csh.history[i].orig, csh.history[i].dest, text);
        CCKR_MOVE(&cckr, csh.history[i].orig, csh.history[i].dest);
        cckr_print(&cckr);
        printf("No %d step, move %d to %d, %s.\n"
               "-------------------------\n", i+1, csh.history[i].orig, csh.history[i].dest, text);
    }
    
    
    
    return 0;
}