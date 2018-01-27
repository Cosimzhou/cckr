//
//  main.c
//  cckr
//
//  Created by cosim on 16/2/10.
//  Copyright © 2016年 sestall. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include "cckr.h"
#include "cckr-tools.h"
#include "cckr-private.h"

void lvtest(int *addr) {
    int axd, k = 0;
    if (addr) {
        printf("%ld, %ld \n", (void*)&addr-(void*)&axd, &axd-&k);
        printf("xxx: %ld \n", (addr - &axd)*sizeof(int));
    } else
        lvtest(&axd);
}
void end(){}



int main(int argc, const char * argv[]) {
    if (argc >= 0) {
        cckr_t cckr;
        cckr_game_board_init(&cckr);
//        cckr_game_board_init_with_command(&cckr, argv[1]);
        cckr_traverse_optimize_param_t ctop = {0};
        cckr_move_t *move = ctop.history.history;
        char text[1024];
        
        time_t t = clock();
        ctop.side = *argv[2]-'0';
        ctop.best = - 0x7fffffff;
        cckr_traversal(&cckr, 3, cckr_traversal_inner, cckr_evaluate_board_score, &ctop);
            
        cckr_get_short_path_string(&cckr, move->orig, move->dest, text);
        printf("%d -> %d, %s.\n", move->orig, move->dest, text);
        printf("(%d,%d) -> (%d,%d), %s.\n", move->orig, move->dest, 1,2, "");
        CCKR_MOVE_T(&cckr, move);
        cckr_print_to_command(&cckr, text);
        printf("%s\n----------------\n", text);
        
        CCKR_UNMOVE_T(&cckr, move);
        cckr_print(&cckr);
        CCKR_MOVE_T(&cckr, move);
        cckr_print(&cckr);
        printf("\nelapsed time: %f second.\n", (clock()-t)/1e6);
        
        return 0;
    }
    
    lvtest(0);
    
    printf("%ld\n", end-lvtest);
    int i = 0;
    unsigned char *sp = (void*)lvtest;
    while (sp != (void*)end) {
        printf("%02X ", *sp++);
        if(++i%16==0)printf("\n");
    }

    lvtest(0);
    
    test(0);
    
    char txt[1024];
    cckr_t cckr;
    cckr_game_board_init(&cckr);
    cckr_print_to_string_with_ruler(&cckr, txt);
    printf("%s", txt);
    return 0;
}
