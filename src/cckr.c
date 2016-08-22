//
//  cckr.c
//  cckr
//
//  Author: Cosim
//  Copyright © 2009年 Sestall. All rights reserved.
//

#include "cckr.h"
#include <stdio.h>
#include <string.h>

const char *tabley = "\000\000\001\001\002\002\002\003\003\003\003"
                     "\004\004\004\004\004\004\004\004\004\004\004"
                     "\004\004\005\005\005\005\005\005\005\005\005"
                     "\005\005\005\006\006\006\006\006\006\006\006"
                     "\006\006\006\007\007\007\007\007\007\007\007"
                     "\007\007\010\010\010\010\010\010\010\010\010"
                     "\011\011\011\011\011\011\011\011\011\011\012\012"
                     "\012\012\012\012\012\012\012\012\012\013\013"
                     "\013\013\013\013\013\013\013\013\013\013\014"
                     "\014\014\014\014\014\014\014\014\014\014\014"
                     "\014\015\015\015\015\016\016\016\017\017\020";
const char *tablex = "\000\014\013\014\012\013\014\011\012\013\014"
                     "\004\005\006\007\010\011\012\013\014\015\016"
                     "\017\020\004\005\006\007\010\011\012\013\014"
                     "\015\016\017\004\005\006\007\010\011\012\013"
                     "\014\015\016\004\005\006\007\010\011\012\013"
                     "\014\015\004\005\006\007\010\011\012\013\014"
                     "\003\004\005\006\007\010\011\012\013\014\002"
                     "\003\004\005\006\007\010\011\012\013\014\001"
                     "\002\003\004\005\006\007\010\011\012\013\014"
                     "\000\001\002\003\004\005\006\007\010\011\012"
                     "\013\014\004\005\006\007\004\005\006\004\005\004";

const char *rtable[] = {
    "\000\000\000\000\000\000\000\000\000\000\000\000\001\000\000\000\000",     // \000
    "\000\000\000\000\000\000\000\000\000\000\000\002\003\000\000\000\000",     // \001
    "\000\000\000\000\000\000\000\000\000\000\004\005\006\000\000\000\000",     // \002
    "\000\000\000\000\000\000\000\000\000\007\010\011\012\000\000\000\000",     // \003
    "\000\000\000\000\013\014\015\016\017\020\021\022\023\024\025\026\027",     // \004
    "\000\000\000\000\030\031\032\033\034\035\036\037\040\041\042\043\000",     // \005
    "\000\000\000\000\044\045\046\047\050\051\052\053\054\055\056\000\000",     // \006
    "\000\000\000\000\057\060\061\062\063\064\065\066\067\070\000\000\000",     // \007
    "\000\000\000\000\071\072\073\074\075\076\077\100\101\000\000\000\000",     // \010
    "\000\000\000\102\103\104\105\106\107\110\111\112\113\000\000\000\000",     // \011
    "\000\000\114\115\116\117\120\121\122\123\124\125\126\000\000\000\000",     // \012
    "\000\127\130\131\132\133\134\135\136\137\140\141\142\000\000\000\000",     // \013
    "\143\144\145\146\147\150\151\152\153\154\155\156\157\000\000\000\000",     // \014
    "\000\000\000\000\160\161\162\163\000\000\000\000\000\000\000\000\000",     // \015
    "\000\000\000\000\164\165\166\000\000\000\000\000\000\000\000\000\000",     // \016
    "\000\000\000\000\167\170\000\000\000\000\000\000\000\000\000\000\000",     // \017
    "\000\000\000\000\171\000\000\000\000\000\000\000\000\000\000\000\000"      // \020
};

const char *inest[] ={
    "\001\002\003\004\005\006\007\010\011\012",         // \001
    "\013\014\015\016\030\031\032\044\045\057",         // \003
    "\024\025\026\027\041\042\043\055\056\070",         // \004
    "\102\114\115\127\130\131\143\144\145\146",         // \005
    "\113\125\126\140\141\142\154\155\156\157",         // \006
    "\160\161\162\163\164\165\166\167\170\171"          // \002
};

#define CCKR_MAP(pcckr)             (((unsigned char*)pcckr)+6)
#define CCKR_MAN(pcckr,x,y)         (CCKR_MAP(pcckr)[XY2IDX(x, y)])
#define CCKR_MANI(pcckr,i)          (CCKR_MAP(pcckr)[i])

#define CCKR_MAN_NULL(pcckr,x,y)    ((CCKR_MAN(pcckr,x,y)&0x7)==0)
#define CCKR_MANI_NULL(pcckr,i)     ((CCKR_MANI(pcckr,i)&0x7)==0)

#define CCKR_VISIT(pcckr,x,y)       CCKR_MAN(pcckr,x,y)=0x80
#define CCKR_VISITI(pcckr,i)        CCKR_MANI(pcckr,i)=0x80

#define CCKR_UNVISIT(pcckr,x,y)     CCKR_MAN(pcckr,x,y)&=0x7f
#define CCKR_UNVISITI(pcckr,i)      CCKR_MANI(pcckr,i)&=0x7f

#define CCKR_SEARCH_DEPTH           4

#define CCKR_NUM                    121
#define CCKR_LEN                    (CCKR_NUM+1)
#define CCKR_ROW                    17
#define CCKR_RTOP                   (CCKR_ROW-1)

#define CCKR_ISINDEX(i)             (0<i&&i<CCKR_LEN)

#define IDX2X(i)                    (tablex[i])
#define IDX2Y(i)                    (tabley[i])
#define XY2IDX(x,y)                 (rtable[y][x])
///////////////////////////////////////////////////////////
#define INEXT_a(x,y)                ((y<CCKR_RTOP)? XY2IDX(x,y+1): 0)
#define INEXT_a2(x,y)               ((y+1<CCKR_RTOP)? XY2IDX(x,y+2):0)

#define INEXT_b(x,y)                ((x>0 && y<CCKR_RTOP)? XY2IDX(x-1,y+1):0)
#define INEXT_b2(x,y)               ((x>1&&y+1<CCKR_RTOP)? XY2IDX(x-2,y+2):0)

#define INEXT_c(x,y)                ((x>0)? XY2IDX(x-1,y):0)
#define INEXT_c2(x,y)               ((x>1)? XY2IDX(x-2,y):0)

#define INEXT_d(x,y)                ((y>0)? XY2IDX(x,y-1):0)
#define INEXT_d2(x,y)               ((y>1)? XY2IDX(x,y-2):0)

#define INEXT_e(x,y)                ((x<CCKR_RTOP&&y>0)? XY2IDX(x+1,y-1):0)
#define INEXT_e2(x,y)               ((x+1<CCKR_RTOP&&y>1)? XY2IDX(x+2,y-2):0)

#define INEXT_f(x,y)                ((x<CCKR_RTOP)? XY2IDX(x+1,y):0)
#define INEXT_f2(x,y)               ((x+1<CCKR_RTOP)? XY2IDX(x+2,y):0)
////////////////////////////////////////////////////////////
#define DES_I(i)                    int _x=IDX2X(i), _y=IDX2Y(i)
#define INEXT_A(i)                  ({DES_I(i);INEXT_a(_x,_y);})
#define INEXT_B(i)                  ({DES_I(i);INEXT_b(_x,_y);})
#define INEXT_C(i)                  ({DES_I(i);INEXT_c(_x,_y);})
#define INEXT_D(i)                  ({DES_I(i);INEXT_d(_x,_y);})
#define INEXT_E(i)                  ({DES_I(i);INEXT_e(_x,_y);})
#define INEXT_F(i)                  ({DES_I(i);INEXT_f(_x,_y);})

#define INEXT_A2(i)                 ({DES_I(i);INEXT_a2(_x,_y);})
#define INEXT_B2(i)                 ({DES_I(i);INEXT_b2(_x,_y);})
#define INEXT_C2(i)                 ({DES_I(i);INEXT_c2(_x,_y);})
#define INEXT_D2(i)                 ({DES_I(i);INEXT_d2(_x,_y);})
#define INEXT_E2(i)                 ({DES_I(i);INEXT_e2(_x,_y);})
#define INEXT_F2(i)                 ({DES_I(i);INEXT_f2(_x,_y);})
/////////////////////////////////////////////////////////////
#define CCKR_MOVE(pcckr,f,t)        ({CCKR_MANI(pcckr,t)=CCKR_MANI(pcckr,f),CCKR_MANI(pcckr,f)=0;})
#define CCKR_UNMOVE(pcckr,f,t)      CCKR_MOVE(pcckr,t,f)


#define PRINT_CCKR(pcckr)                                                       \
                        do {                                                    \
                            char _buff[1024];                                   \
                            cckr_print_to_string(pcckr, _buff);                 \
                            printf("%s", _buff);                                \
                        } while(0)


#define FOREACH_AVAIABLES_BEGIN(pcckr, side, ch, dch, action)                   \
                        byte _avaibles[1024];                                   \
                        int _bcnt = cckr_get_avaible_for_side(pcckr,            \
                                                              side,             \
                                                              _avaibles);       \
                        for(int _i = 0; _i < _bcnt;)                            \
                        {                                                       \
                            byte ch = _avaibles[_i++];                          \
                            int _acnt = _avaibles[_i++];                        \
                            action;                                             \
                            for (int _j = 0; _j < _acnt; ++_j, ++_i)            \
                            {                                                   \
                                byte dch = _avaibles[_i]


#define FOREACH_AVAIABLES_END(pcckr, side, ch, dch, action)                     \
                            }                                                   \
                            action;                                             \
                        }

int g_eval;
byte g_buff[1024];
byte *g_buffer = g_buff+1000;

int cckr_init_game_board(CCKR *pcckr) {
    memset(pcckr, 0, sizeof(CCKR));
    for (int i = 0; i<10; ++i) {
        CCKR_MANI(pcckr, inest[0][i])=1;
        CCKR_MANI(pcckr, inest[5][i])=2;
    }
    return 0;
}

int search_way_for_hopping(CCKR *pcckr, int index, byte *buff) {
#define search_direction(c)                                                     \
    if (0!=(ncc=INEXT_##c##2(_x,_y)) && 0==CCKR_MANI(pcckr, ncc)                \
        && 0!=(nc=INEXT_##c(_x,_y)) && !CCKR_MANI_NULL(pcckr, nc)) {            \
        sum += search_way_for_hopping(pcckr, ncc, buff+sum);                    \
    }

    int nc, ncc, sum=0;
    CCKR_VISITI(pcckr, index);
    buff[sum++] = index;
    DES_I(index);
    search_direction(a);
    search_direction(b);
    search_direction(c);
    search_direction(d);
    search_direction(e);
    search_direction(f);
    return sum;
#undef search_direction
}

int cckr_get_available_pit_for_index(CCKR *pcckr, int index, byte *buff) {
#define search_direction(c)                                                     \
    if (0 != (nc = INEXT_##c(_x,_y))) {                                         \
        if (CCKR_MANI_NULL(pcckr, nc)) {                                        \
            buff[top++] = nc;                                                   \
        } else if (0!=(ncc=INEXT_##c##2(_x,_y)) && 0==CCKR_MANI(pcckr, ncc)) {  \
            top += search_way_for_hopping(pcckr, ncc, buff+top);                \
        }                                                                       \
    }
    
    if (!CCKR_ISINDEX(index) || CCKR_MANI_NULL(pcckr, index))
        return 0;
    
    int top = 0, nc, ncc;
    DES_I(index);
    search_direction(a);
    search_direction(b);
    search_direction(c);
    search_direction(d);
    search_direction(e);
    search_direction(f);
    for (nc = 0; nc < top; ++nc) {
        CCKR_UNVISITI(pcckr, buff[nc]);
    }
    return top;
#undef search_direction
}

int cckr_get_avaible_for_side(CCKR *pcckr, byte side, byte *buff) {
    int rest = 10;
    byte *buffer = buff;
    for (int i = 1; i < CCKR_LEN; ++i) {
        if (CCKR_MANI(pcckr, i)==side) {
            *buff++ = i;
            *buff = cckr_get_available_pit_for_index(pcckr, i, buff+1);
            buff += *buff? *buff+1: -1;
            if(--rest == 0) break;
        }
    }
    return (int)(buff-buffer);
}

int cckr_print_to_string(CCKR *pcckr, char *buff) {
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

int cckr_print_avaible_to_string(byte *result, char *string, int count) {
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

int cckr_traversal(CCKR *pcckr, int depth) {
    if (++depth > CCKR_SEARCH_DEPTH) {
        return cckr_evaluate_board_score(pcckr, 1);
    }

    byte sch = 0, ech = 0;
    FOREACH_AVAIABLES_BEGIN(pcckr, 1, ch, dch, );
    {
        CCKR_MOVE(pcckr, ch, dch);
        int val = cckr_traversal(pcckr, depth);
        
        if (g_eval < val) {
            g_eval = val, sch = ch, ech = dch;
            
            g_buffer[depth*2] = sch;
            g_buffer[depth*2+1] = ech;
            
            if (CCKR_SEARCH_DEPTH == depth) {
                cckr_print_to_string(pcckr, (char*)g_buff);
                // xx
            }
        }
        
        CCKR_UNMOVE(pcckr, ch, dch);
    }
    FOREACH_AVAIABLES_END(pcckr, 1, ch, dch, );

    if (!depth) {
        printf("from: %d=>%d\n", sch, ech);
    }
    
    return g_eval;
}

int cckr_evaluate_board_score(CCKR *pcckr, int side) {
    int y, oy, ly, sum = 0;
    FOREACH_AVAIABLES_BEGIN(pcckr, 1, ch, dch, {oy = IDX2Y(ch); y = 0;});
    {
        ly = IDX2Y(dch);
        if (y < ly) y = ly;
    }
    FOREACH_AVAIABLES_END(pcckr, 1, ch, dch, {sum += (y-oy)*100;});
    
    return sum;
}

int cckr_rotate_side_to_master(CCKR *pcckr, int side) {
    
    return 0;
}

int test(int ii) {
    CCKR cckr;
    cckr_init_game_board(&cckr);
    
    printf("v====>:\n");
    
    g_eval = 0;
    printf("%d\n", CCKR_TRAVERSAL(&cckr));
    printf("%s", g_buff);
    
    for(int i = 0; i <CCKR_SEARCH_DEPTH*2; i+=2) {
        printf("move %d to %d.\n", g_buffer[i], g_buffer[i+1]);
    }
    
    return 0;
}