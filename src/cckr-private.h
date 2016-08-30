//  cckr.h
//  cckr
//
//  Author: Cosim
//  Copyright © 2009年 Sestall. All rights reserved.
//

#ifndef __CCKR_PRIVATE_H__
#define __CCKR_PRIVATE_H__

#define CCKR_INT_MAX                ((int)(~(unsigned int)0 / 2))

#define CCKR_SEARCH_DEPTH           3

#define CCKR_NUM                    121
#define CCKR_LEN                    (CCKR_NUM+1)
#define CCKR_ROW                    17
#define CCKR_RTOP                   (CCKR_ROW-1)

#define CCKR_MAP(pcckr)             (((unsigned char*)pcckr))
#define CCKR_MAN(pcckr,x,y)         (CCKR_MAP(pcckr)[XY2IDX(x, y)])
#define CCKR_MANI(pcckr,i)          (CCKR_MAP(pcckr)[i])

#define CCKR_MAN_NULL(pcckr,x,y)    ((CCKR_MAN(pcckr,x,y)&0x7)==0)
#define CCKR_MANI_NULL(pcckr,i)     ((CCKR_MANI(pcckr,i)&0x7)==0)

#define CCKR_VISIT(pcckr,x,y)       CCKR_MAN(pcckr,x,y)|=0x80
#define CCKR_VISITI(pcckr,i)        CCKR_MANI(pcckr,i)|=0x80

#define CCKR_UNVISIT(pcckr,x,y)     CCKR_MAN(pcckr,x,y)&=0x7f
#define CCKR_UNVISITI(pcckr,i)      CCKR_MANI(pcckr,i)&=0x7f

#define CCKR_ISINDEX(i)             (0<i&&i<CCKR_LEN)

#define IDX2X(i)                    (cckr_table_4x[i])
#define IDX2Y(i)                    (cckr_table_4y[i])
#define XY2IDX(x,y)                 (cckr_table_reverse[y][x])
///////////////////////////////////////////////////////////
#define DES_I(i)                    int _x=IDX2X(i), _y=IDX2Y(i)

#define CCKR_NEXT_TABLE
#ifdef CCKR_NEXT_TABLE
#   define _NEXT_a                      (cckr_table_next_move[0])
#   define _NEXT_b                      (cckr_table_next_move[1])
#   define _NEXT_c                      (cckr_table_next_move[2])
#   define _NEXT_d                      (cckr_table_next_move[3])
#   define _NEXT_e                      (cckr_table_next_move[4])
#   define _NEXT_f                      (cckr_table_next_move[5])

#   define _NEXT(i,d)                   (_NEXT_##d[(i)])
#   define INEXT_A(i)                   _NEXT(i,a)
#   define INEXT_B(i)                   _NEXT(i,b)
#   define INEXT_C(i)                   _NEXT(i,c)
#   define INEXT_D(i)                   _NEXT(i,d)
#   define INEXT_E(i)                   _NEXT(i,e)
#   define INEXT_F(i)                   _NEXT(i,f)

#   define INEXT_A2(i)                  _NEXT(_NEXT(i,a),a)
#   define INEXT_B2(i)                  _NEXT(_NEXT(i,b),b)
#   define INEXT_C2(i)                  _NEXT(_NEXT(i,c),c)
#   define INEXT_D2(i)                  _NEXT(_NEXT(i,d),d)
#   define INEXT_E2(i)                  _NEXT(_NEXT(i,e),e)
#   define INEXT_F2(i)                  _NEXT(_NEXT(i,f),f)

#   define INEXT_a                      INEXT_A
#   define INEXT_a2                     INEXT_A2

#   define INEXT_b                      INEXT_B
#   define INEXT_b2                     INEXT_B2

#   define INEXT_c                      INEXT_C
#   define INEXT_c2                     INEXT_C2

#   define INEXT_d                      INEXT_D
#   define INEXT_d2                     INEXT_D2

#   define INEXT_e                      INEXT_E
#   define INEXT_e2                     INEXT_E2

#   define INEXT_f                      INEXT_F
#   define INEXT_f2                     INEXT_F2

#else//CCKR_NEXT_TABLE
#   define INEXT_A(i)                   ({DES_I(i);INEXT_a(_x,_y);})
#   define INEXT_B(i)                   ({DES_I(i);INEXT_b(_x,_y);})
#   define INEXT_C(i)                   ({DES_I(i);INEXT_c(_x,_y);})
#   define INEXT_D(i)                   ({DES_I(i);INEXT_d(_x,_y);})
#   define INEXT_E(i)                   ({DES_I(i);INEXT_e(_x,_y);})
#   define INEXT_F(i)                   ({DES_I(i);INEXT_f(_x,_y);})

#   define INEXT_A2(i)                  ({DES_I(i);INEXT_a2(_x,_y);})
#   define INEXT_B2(i)                  ({DES_I(i);INEXT_b2(_x,_y);})
#   define INEXT_C2(i)                  ({DES_I(i);INEXT_c2(_x,_y);})
#   define INEXT_D2(i)                  ({DES_I(i);INEXT_d2(_x,_y);})
#   define INEXT_E2(i)                  ({DES_I(i);INEXT_e2(_x,_y);})
#   define INEXT_F2(i)                  ({DES_I(i);INEXT_f2(_x,_y);})

#   define INEXT_a(x,y)                 ((y<CCKR_RTOP)? XY2IDX(x,y+1): 0)
#   define INEXT_a2(x,y)                ((y+1<CCKR_RTOP)? XY2IDX(x,y+2):0)

#   define INEXT_b(x,y)                 ((x>0 && y<CCKR_RTOP)? XY2IDX(x-1,y+1):0)
#   define INEXT_b2(x,y)                ((x>1&&y+1<CCKR_RTOP)? XY2IDX(x-2,y+2):0)

#   define INEXT_c(x,y)                 ((x>0)? XY2IDX(x-1,y):0)
#   define INEXT_c2(x,y)                ((x>1)? XY2IDX(x-2,y):0)

#   define INEXT_d(x,y)                 ((y>0)? XY2IDX(x,y-1):0)
#   define INEXT_d2(x,y)                ((y>1)? XY2IDX(x,y-2):0)

#   define INEXT_e(x,y)                 ((x<CCKR_RTOP&&y>0)? XY2IDX(x+1,y-1):0)
#   define INEXT_e2(x,y)                ((x+1<CCKR_RTOP&&y>1)? XY2IDX(x+2,y-2):0)

#   define INEXT_f(x,y)                 ((x<CCKR_RTOP)? XY2IDX(x+1,y):0)
#   define INEXT_f2(x,y)                ((x+1<CCKR_RTOP)? XY2IDX(x+2,y):0)
#endif//CCKR_NEXT_TABLE
/////////////////////////////////////////////////////////////
#define CCKR_MOVE(pcckr,f,t)        ({                                          \
                                        CCKR_MANI(pcckr,t)=CCKR_MANI(pcckr,f);  \
                                        CCKR_MANI(pcckr,f)=0;                   \
                                    })
#define CCKR_MOVE_T(pcckr,m)        CCKR_MOVE(pcckr,(m)->orig,(m)->dest)
#define CCKR_UNMOVE(pcckr,f,t)      CCKR_MOVE(pcckr,t,f)
#define CCKR_UNMOVE_T(pcckr,m)      CCKR_MOVE(pcckr,(m)->dest,(m)->orig)

#define STRING_APPEND(str,...)                                                  \
                        str += sprintf(str, __VA_ARGS__)


#define FOREACH_AVAIABLES_BEGIN(pcckr, side, ch, dch, action)                   \
                        cckr_index_t _avaibles[1024];                           \
                        int _bcnt = cckr_get_avaible_for_side(pcckr,            \
                                                              side,             \
                                                              _avaibles);       \
                        for(int _i = 0; _i < _bcnt;) {                          \
                            cckr_index_t ch = _avaibles[_i++];                  \
                            int _acnt = _avaibles[_i++];                        \
                            action;                                             \
                            for (int _j = 0; _j < _acnt; ++_j, ++_i) {          \
                                cckr_index_t dch = _avaibles[_i]


#define FOREACH_AVAIABLES_END(pcckr, side, ch, dch, action)                     \
                            }                                                   \
                            action;                                             \
                        }

#define FOREACH_PIT_IN_BOARD(i)                                                 \
                    for (i = 1; i < CCKR_LEN; ++i)

#endif /* __CCKR_PRIVATE_H__ */