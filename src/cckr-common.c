//
//  cckr-common.c
//  cckr
//
//  Author: Cosim
//  Copyright © 2009年 Sestall. All rights reserved.
//

#include "cckr-common.h"
#include "cckr-private.h"
#include <stdio.h>
#include <string.h>


#pragma mark - basic rule implementation

static int cckr_search_way_for_hopping(cckr_t *pcckr, int index, cckr_index_t *buff);


int cckr_game_board_init(cckr_t *pcckr) {
    memset(pcckr, 0, sizeof(cckr_t));
    for (int i = 0; i<10; ++i) {
        CCKR_MANI(pcckr, cckr_nest_indices[0][i]) = 1;
//        CCKR_MANI(pcckr, cckr_nest_indices[5][i]) = 2;
    }
    return 0;
}

int cckr_game_board_recover(cckr_t *pcckr, cckr_step_history *history) {
    cckr_game_board_init(pcckr);
    for (int i = 0; i < history->size; ++i) {
        CCKR_MOVE(pcckr, history->history[i].orig, history->history[i].dest);
    }
    return 0;
}

inline void
cckr_step_history_append(cckr_step_history *dest, cckr_index_t *step, int size) {
    memcpy(dest->history+dest->size, step, size);
    dest->size += size/2;
}

inline void
cckr_step_history_append_history(cckr_step_history *dest, cckr_step_history *src) {
    memcpy(dest->history+dest->size, src->history, src->size<<1);
    dest->size += src->size;
}

inline void
cckr_step_history_copy(cckr_step_history *dest, cckr_index_t *src, int size) {
    memcpy(dest->history, src, size);
    dest->size = size/2;
}

inline void
cckr_step_history_copy_history(cckr_step_history *dest, cckr_step_history *src) {
    memcpy(dest->history, src->history, src->size<<1);
    dest->size = src->size;
}


int cckr_search_way_for_hopping(cckr_t *pcckr, int index, cckr_index_t *buff) {
    int nc, ncc, sum=0;
    CCKR_VISITI(pcckr, index);
    buff[sum++] = index;
    
#ifdef CCKR_NEXT_TABLE
#   define search_direction(c)                                                  \
    if (0!=(ncc=INEXT_##c##2(index)) && 0==CCKR_MANI(pcckr, ncc)                \
        && 0!=(nc=INEXT_##c(index)) && !CCKR_MANI_NULL(pcckr, nc)) {            \
        sum += cckr_search_way_for_hopping(pcckr, ncc, buff+sum);               \
    }
#else //CCKR_NEXT_TABLE
#   define search_direction(c)                                                  \
    if (0!=(ncc=INEXT_##c##2(_x,_y)) && 0==CCKR_MANI(pcckr, ncc)                \
        && 0!=(nc=INEXT_##c(_x,_y)) && !CCKR_MANI_NULL(pcckr, nc)) {            \
        sum += cckr_search_way_for_hopping(pcckr, ncc, buff+sum);               \
    }
    DES_I(index);
#endif //CCKR_NEXT_TABLE
    search_direction(a);
    search_direction(b);
    search_direction(c);
    search_direction(d);
    search_direction(e);
    search_direction(f);

#undef search_direction
    return sum;
}

int cckr_get_available_pit_for_index(cckr_t *pcckr, int index, cckr_index_t *buff) {
    if (!CCKR_ISINDEX(index) || CCKR_MANI_NULL(pcckr, index))
        return 0;
    
    int top = 0, nc, ncc;
#ifdef CCKR_NEXT_TABLE
#   define search_direction(c)                                                  \
    if (0 != (nc = INEXT_##c(index))) {                                         \
        if (CCKR_MANI_NULL(pcckr, nc)) {                                        \
            buff[top++] = nc;                                                   \
        } else if (0!=(ncc=INEXT_##c##2(index)) && 0==CCKR_MANI(pcckr, ncc)) {  \
            top += cckr_search_way_for_hopping(pcckr, ncc, buff+top);           \
        }                                                                       \
    }
#else// CCKR_NEXT_TABLE
#   define search_direction(c)                                                  \
    if (0 != (nc = INEXT_##c(_x,_y))) {                                         \
        if (CCKR_MANI_NULL(pcckr, nc)) {                                        \
            buff[top++] = nc;                                                   \
        } else if (0!=(ncc=INEXT_##c##2(_x,_y)) && 0==CCKR_MANI(pcckr, ncc)) {  \
            top += cckr_search_way_for_hopping(pcckr, ncc, buff+top);           \
        }                                                                       \
    }
    
    DES_I(index);
#endif // CCKR_NEXT_TABLE
    search_direction(a);
    search_direction(b);
    search_direction(c);
    search_direction(d);
    search_direction(e);
    search_direction(f);
#undef search_direction
    for (nc = 0; nc < top; ++nc) {
        CCKR_UNVISITI(pcckr, buff[nc]);
    }
    return top;
}

int cckr_get_avaible_for_side(cckr_t *pcckr, cckr_index_t side, cckr_index_t *buff) {
    int rest = 10;
    cckr_index_t *buffer = buff;
    for (int i = 1; i < CCKR_LEN; ++i) {
        if (CCKR_MANI(pcckr, i) == side) {
            *buff++ = i;
            *buff = cckr_get_available_pit_for_index(pcckr, i, buff+1);
            buff += *buff? *buff+1: -1;
            if(--rest == 0) break;
        }
    }
    return (int)(buff-buffer);
}

inline int cckr_get_avaible_count_for_side(cckr_t *pcckr, cckr_index_t side) {
    cckr_index_t buff[1024];
    return cckr_get_avaible_for_side(pcckr, side, buff);
}

int cckr_push_short_path_stack(cckr_path_node_t *pcpn, cckr_index_t *mid, cckr_index_t os)
{
    cckr_index_t src= pcpn->move.orig, *smid = mid;
    
    while (os != pcpn->move.orig) {
        *mid++ = pcpn->move.dest;
        
        while (pcpn->move.dest != src) --pcpn;
        src = pcpn->move.orig;
    }
    *mid++ = pcpn->move.dest;
    
    return (int)(mid-smid);
}

int cckr_get_path_between_move(cckr_t *pcckr, cckr_index_t s, cckr_index_t e, cckr_index_t *path) {
    if (pcckr == NULL || CCKR_MANI(pcckr, s) == 0 || CCKR_MANI(pcckr, e) != 0)
        return 0;

    int nc, ncc, len = CCKR_INT_MAX;
    cckr_index_t *spath = path, mid[120];
    cckr_path_node_t buffer[512], *sp = buffer, *ssp = buffer;
    
#ifdef CCKR_NEXT_TABLE
#   define search_direction(c)                                                  \
    if (0 != (nc = INEXT_##c(s))) {                                             \
        if (nc == e) {                                                          \
            *path = e;                                                          \
            return 1;                                                           \
        } else if (0 != (ncc=INEXT_##c##2(s)) && !CCKR_MANI_NULL(pcckr, nc)     \
                    && CCKR_MANI(pcckr, ncc)==0) {                              \
            if (ncc == e) {                                                     \
                *path = e;                                                      \
                return 1;                                                       \
            }                                                                   \
            sp->move.orig = s; sp->move.dest=ncc;(sp++)->step = 1;              \
        }                                                                       \
    }
    
#   define try_skip_direction(w, c)                                             \
    if (0 != (nc = INEXT_##c##2((w))) && !CCKR_MANI_NULL(pcckr, INEXT_##c((w))) \
        && CCKR_MANI(pcckr, nc) == 0)                                           \
        sp->move.orig=(w), sp->move.dest = nc, (sp++)->step = ssp->step+1
    
    
#else// CCKR_NEXT_TABLE
#   define search_direction(c)                                                  \
    if (0 != (nc = INEXT_##c(_x,_y))) {                                         \
        if (CCKR_MANI_NULL(pcckr, nc)) {                                        \
            buff[top++] = nc;                                                   \
        } else if (0!=(ncc=INEXT_##c##2(_x,_y)) && 0==CCKR_MANI(pcckr, ncc)) {  \
            if (ncc == e)\
            top += cckr_search_way_for_hopping(pcckr, ncc, buff+top);           \
        }                                                                       \
    }
    
    DES_I(s);
#endif // CCKR_NEXT_TABLE
    search_direction(a);
    search_direction(b);
    search_direction(c);
    search_direction(d);
    search_direction(e);
    search_direction(f);
#undef search_direction
    
    while (ssp != sp) {
        if (CCKR_MANI(pcckr, ssp->move.dest) == 0) {
            CCKR_VISITI(pcckr, ssp->move.dest);
            ncc = ssp->move.dest;
            try_skip_direction(ncc, a);
            try_skip_direction(ncc, b);
            try_skip_direction(ncc, c);
            try_skip_direction(ncc, d);
            try_skip_direction(ncc, e);
            try_skip_direction(ncc, f);
        }

        if (ssp->move.dest == e) {
            int a = cckr_push_short_path_stack(ssp, mid, s);
            if (len > a) {
                len = a;
                path = spath;
                while (a--) *path++ = mid[a];
                *path++ = e;
            }
        }
        ++ssp;
    }

    for (ssp = buffer; ssp != sp; ++ssp) {
        CCKR_UNVISITI(pcckr, ssp->move.dest);
        CCKR_UNVISITI(pcckr, ssp->move.orig);
    }
    
    return (len < CCKR_INT_MAX)? len: 0;
}

int cckr_get_short_path_string(cckr_t *pcckr, cckr_index_t s, cckr_index_t e, char *buff){
    cckr_index_t buffer[100];
    int i, len = cckr_get_path_between_move(pcckr, s, e, buffer);
    *buff = 0;
    buff += sprintf(buff, "%d", s);
    for (i = 0; i < len; ++i) {
        buff += sprintf(buff, "->%d", buffer[i]);
    }
    return len;
}

#pragma mark - simple print functions

int cckr_print(cckr_t *pcckr) {
    char buff[1024];
    cckr_print_to_string(pcckr, buff);
    printf("\n%s", buff);
    return 0;
}

int cckr_print_to_string(cckr_t *pcckr, char *buff) {
    const char *cchmanchr="_O@*#xm";
    const char *space = "    ";//' '*5
    int i, j, idx, enter;
    for (i = 0; i < CCKR_ROW; ++i) {
        if (i < 4) buff += sprintf(buff, "%s", space+i);
        for (j = enter = 0; j < CCKR_ROW; ++j) {
            if (9<=i && i<=12 && j==0) j += i-8;
            idx = XY2IDX(j, 16-i);
            if (idx) {
                enter = 1;
                *buff++ = cchmanchr[CCKR_MANI(pcckr, idx)];
            } else if (enter) {
                --buff;
                break;
            } else
                *buff++= ' ';

            if (j>=i-4 || (9<=i && i<=12 && enter))
                *buff++ = ' ';
        }
        *buff++ = '\n';
    }
    *buff = 0;
    return 0;
}

int cckr_print_to_string_4colrow(cckr_t *pcckr, char *buff) {
    const char *space = "    ";//' '*5
    int i, j, idx, enter;
    for (i = 0; i < CCKR_ROW; ++i) {
        if (i < 4) buff += sprintf(buff, "%s", space+i);
        for (j = enter = 0; j < CCKR_ROW; ++j) {
            if (9<=i && i<=12 && j==0) j += i-8;
            idx = XY2IDX(j, 16-i);
            if (idx) {
                enter = 1;
                idx = CCKR_MANI(pcckr, idx);
                *buff++ = idx<10? '0'+idx: 'A'+idx-10;
            } else if (enter) {
                --buff;
                break;
            } else
                *buff++= ' ';
            
            if (j>=i-4 || (9<=i && i<=12 && enter))
                *buff++ = ' ';
        }
        *buff++ = '\n';
    }
    *buff = 0;
    return 0;
}

int cckr_print_avaible_to_string(cckr_index_t *result, char *string, int count) {
    for (int i = 0, num; i < count;) {
        string += sprintf(string, "%d:(", result[i++]);
        num = result[i++];
        while (num--) {
            string += sprintf(string, "%d", result[i++]);
            if (num) *string++ = ' ';
        }
        string += sprintf(string, ") ");
    }
    return 0;
}


#pragma mark - traversal functions

int cckr_traversal_inner(void *ptr) {
    cckr_traverse_param_t *pctp = ptr;
    cckr_traverse_optimize_param_t *pctop = pctp->param;
    
    int old = pctop->best, depth = pctp->depth, val = pctp->val;

    if (depth == CCKR_SEARCH_DEPTH && pctop->best < val) {
        pctop->best = pctp->val;
    }
    
    if (old < pctop->best) {
        if (pctop->best <= pctp->val) {
            pctop->best = pctp->val;
        }
        cckr_step_history_copy(&pctop->history, pctp->stack, depth*2+2);
    }
    
    return 0;
}

int cckr_traversal_each_level(cckr_traverse_param_t *pctp) {
    if (pctp->depth == CCKR_SEARCH_DEPTH)
        return pctp->endfunc(pctp->pcckr, 1);
    
    int idx = ++pctp->depth;
    idx <<= 1;
    pctp->val = -CCKR_INT_MAX;
    FOREACH_AVAIABLES_BEGIN(pctp->pcckr, 1, ch, dch, );
    {
        CCKR_MOVE(pctp->pcckr, ch, dch);
        
        pctp->stack[idx] = ch;
        pctp->stack[idx+1] = dch;
        pctp->val = cckr_traversal_each_level(pctp);
        pctp->func(pctp);
        
        CCKR_UNMOVE(pctp->pcckr, ch, dch);
    }
    FOREACH_AVAIABLES_END(pctp->pcckr, 1, ch, dch, );
    
    --pctp->depth;
    return pctp->val;
}

int cckr_traversal(cckr_t *pcckr, int depth, cckr_traversal_inner_func_t func, cckr_evaluate_func_t evalfunc, void *param) {
    if (func == NULL)
        return 0;

    cckr_traverse_param_t ctp = {
        .pcckr = pcckr,
        .depth = -1,
        .max_depth = depth,
        .param = param,
        .func = func,
        .endfunc = evalfunc
    };
    
    if (depth > sizeof(ctp.stack)/2)
        ctp.max_depth = sizeof(ctp.stack)/2;
    
    return cckr_traversal_each_level(&ctp);
}

#pragma mark - evaluate entry point

int cckr_evaluate_board_score(cckr_t *pcckr, int side) {
    return cckr_evaluater_array[CCKR_EVALUATE_UPPER](pcckr, side);
}

int cckr_evaluate_board_score_x(cckr_t *pcckr, int side) {
    return cckr_evaluater_array[CCKR_EVALUATE_NAIVE](pcckr, side);
}

#pragma mark -

int cckr_rotate_side_to_master(cckr_t *pcckr, int side) {
    return 0;
}

//void cckr_step_history_init(cckr_step_history *pcsh) {
//    if (pcsh == NULL || pcsh->history || pcsh->capacity) return;
//    
//    pcsh->history = (cckr_index_t*)malloc(1024);
//    pcsh->size = 0;
//    pcsh->capacity = 1024;
//}
//
//void cckr_step_history_clean(cckr_step_history *pcsh) {
//    if (NULL == pcsh) return;
//    pcsh->history;
//}