//
//  cckr-common.c
//  cckr
//
//  Author: Cosim
//  Copyright © 2009年 Sestall. All rights reserved.
//

#include "cckr-const.h"
const char cckr_board_place_holder_space[] = {cckr_board_char_space,
    cckr_board_char_space,
    cckr_board_char_space,
    cckr_board_char_space,
    0
};

const char cckr_chess_man_char[] = {cckr_board_char_null,
    cckr_board_char_1,
    cckr_board_char_2,
    cckr_board_char_3,
    cckr_board_char_4,
    cckr_board_char_5,
    cckr_board_char_6,
    cckr_board_char_space
};

const char *cckr_table_x[] ={
    //      direction 0
    "\000\014\013\014\012\013\014\011\012\013\014"
    "\004\005\006\007\010\011\012\013\014\015\016"
    "\017\020\004\005\006\007\010\011\012\013\014"
    "\015\016\017\004\005\006\007\010\011\012\013"
    "\014\015\016\004\005\006\007\010\011\012\013"
    "\014\015\004\005\006\007\010\011\012\013\014"
    "\003\004\005\006\007\010\011\012\013\014\002"
    "\003\004\005\006\007\010\011\012\013\014\001"
    "\002\003\004\005\006\007\010\011\012\013\014"
    "\000\001\002\003\004\005\006\007\010\011\012"
    "\013\014\004\005\006\007\004\005\006\004\005"
    "\004",
    //      direction 1
    "\000\020\017\017\016\016\016\015\015\015\015"
    "\014\014\014\014\014\014\014\014\014\014\014"
    "\014\014\013\013\013\013\013\013\013\013\013"
    "\013\013\013\012\012\012\012\012\012\012\012"
    "\012\012\012\011\011\011\011\011\011\011\011"
    "\011\011\010\010\010\010\010\010\010\010\010"
    "\007\007\007\007\007\007\007\007\007\007\006"
    "\006\006\006\006\006\006\006\006\006\006\005"
    "\005\005\005\005\005\005\005\005\005\005\005"
    "\004\004\004\004\004\004\004\004\004\004\004"
    "\004\004\003\003\003\003\002\002\002\001\001"
    "\000",
    //      direction 2
    "\000\014\014\013\014\013\012\014\013\012\011"
    "\020\017\016\015\014\013\012\011\010\007\006"
    "\005\004\017\016\015\014\013\012\011\010\007"
    "\006\005\004\016\015\014\013\012\011\010\007"
    "\006\005\004\015\014\013\012\011\010\007\006"
    "\005\004\014\013\012\011\010\007\006\005\004"
    "\014\013\012\011\010\007\006\005\004\003\014"
    "\013\012\011\010\007\006\005\004\003\002\014"
    "\013\012\011\010\007\006\005\004\003\002\001"
    "\014\013\012\011\010\007\006\005\004\003\002"
    "\001\000\007\006\005\004\006\005\004\005\004"
    "\004",
    //      direction 3
    "\000\004\005\004\006\005\004\007\006\005\004"
    "\014\013\012\011\010\007\006\005\004\003\002"
    "\001\000\014\013\012\011\010\007\006\005\004"
    "\003\002\001\014\013\012\011\010\007\006\005"
    "\004\003\002\014\013\012\011\010\007\006\005"
    "\004\003\014\013\012\011\010\007\006\005\004"
    "\015\014\013\012\011\010\007\006\005\004\016"
    "\015\014\013\012\011\010\007\006\005\004\017"
    "\016\015\014\013\012\011\010\007\006\005\004"
    "\020\017\016\015\014\013\012\011\010\007\006"
    "\005\004\014\013\012\011\014\013\012\014\013"
    "\014",
    //      direction 4
    "\000\000\001\001\002\002\002\003\003\003\003"
    "\004\004\004\004\004\004\004\004\004\004\004"
    "\004\004\005\005\005\005\005\005\005\005\005"
    "\005\005\005\006\006\006\006\006\006\006\006"
    "\006\006\006\007\007\007\007\007\007\007\007"
    "\007\007\010\010\010\010\010\010\010\010\010"
    "\011\011\011\011\011\011\011\011\011\011\012"
    "\012\012\012\012\012\012\012\012\012\012\013"
    "\013\013\013\013\013\013\013\013\013\013\013"
    "\014\014\014\014\014\014\014\014\014\014\014"
    "\014\014\015\015\015\015\016\016\016\017\017"
    "\020",
    //      direction 5
    "\000\004\004\005\004\005\006\004\005\006\007"
    "\000\001\002\003\004\005\006\007\010\011\012"
    "\013\014\001\002\003\004\005\006\007\010\011"
    "\012\013\014\002\003\004\005\006\007\010\011"
    "\012\013\014\003\004\005\006\007\010\011\012"
    "\013\014\004\005\006\007\010\011\012\013\014"
    "\004\005\006\007\010\011\012\013\014\015\004"
    "\005\006\007\010\011\012\013\014\015\016\004"
    "\005\006\007\010\011\012\013\014\015\016\017"
    "\004\005\006\007\010\011\012\013\014\015\016"
    "\017\020\011\012\013\014\012\013\014\013\014"
    "\014"
};

const char *cckr_table_y[] = {
    //      direction 0
    "\000\000\001\001\002\002\002\003\003\003\003"
    "\004\004\004\004\004\004\004\004\004\004\004"
    "\004\004\005\005\005\005\005\005\005\005\005"
    "\005\005\005\006\006\006\006\006\006\006\006"
    "\006\006\006\007\007\007\007\007\007\007\007"
    "\007\007\010\010\010\010\010\010\010\010\010"
    "\011\011\011\011\011\011\011\011\011\011\012\012"
    "\012\012\012\012\012\012\012\012\012\013\013"
    "\013\013\013\013\013\013\013\013\013\013\014"
    "\014\014\014\014\014\014\014\014\014\014\014"
    "\014\015\015\015\015\016\016\016\017\017\020",
    //      direction 1
    "\000\004\004\005\004\005\006\004\005\006\007"
    "\000\001\002\003\004\005\006\007\010\011\012"
    "\013\014\001\002\003\004\005\006\007\010\011"
    "\012\013\014\002\003\004\005\006\007\010\011"
    "\012\013\014\003\004\005\006\007\010\011\012"
    "\013\014\004\005\006\007\010\011\012\013\014"
    "\004\005\006\007\010\011\012\013\014\015\004"
    "\005\006\007\010\011\012\013\014\015\016\004"
    "\005\006\007\010\011\012\013\014\015\016\017"
    "\004\005\006\007\010\011\012\013\014\015\016"
    "\017\020\011\012\013\014\012\013\014\013\014"
    "\014",
    //      direction 2
    "\000\014\013\014\012\013\014\011\012\013\014"
    "\004\005\006\007\010\011\012\013\014\015\016"
    "\017\020\004\005\006\007\010\011\012\013\014"
    "\015\016\017\004\005\006\007\010\011\012\013"
    "\014\015\016\004\005\006\007\010\011\012\013"
    "\014\015\004\005\006\007\010\011\012\013\014"
    "\003\004\005\006\007\010\011\012\013\014\002"
    "\003\004\005\006\007\010\011\012\013\014\001"
    "\002\003\004\005\006\007\010\011\012\013\014"
    "\000\001\002\003\004\005\006\007\010\011\012"
    "\013\014\004\005\006\007\004\005\006\004\005"
    "\004",//;
    //      direction 3
    "\000\020\017\017\016\016\016\015\015\015\015"
    "\014\014\014\014\014\014\014\014\014\014\014"
    "\014\014\013\013\013\013\013\013\013\013\013"
    "\013\013\013\012\012\012\012\012\012\012\012"
    "\012\012\012\011\011\011\011\011\011\011\011"
    "\011\011\010\010\010\010\010\010\010\010\010"
    "\007\007\007\007\007\007\007\007\007\007\006"
    "\006\006\006\006\006\006\006\006\006\006\005"
    "\005\005\005\005\005\005\005\005\005\005\005"
    "\004\004\004\004\004\004\004\004\004\004\004"
    "\004\004\003\003\003\003\002\002\002\001\001"
    "\000",//;
    //      direction 4
    "\000\014\014\013\014\013\012\014\013\012\011"
    "\020\017\016\015\014\013\012\011\010\007\006"
    "\005\004\017\016\015\014\013\012\011\010\007"
    "\006\005\004\016\015\014\013\012\011\010\007"
    "\006\005\004\015\014\013\012\011\010\007\006"
    "\005\004\014\013\012\011\010\007\006\005\004"
    "\014\013\012\011\010\007\006\005\004\003\014"
    "\013\012\011\010\007\006\005\004\003\002\014"
    "\013\012\011\010\007\006\005\004\003\002\001"
    "\014\013\012\011\010\007\006\005\004\003\002"
    "\001\000\007\006\005\004\006\005\004\005\004"
    "\004",//;
    //      direction 5
    "\000\004\005\004\006\005\004\007\006\005\004"
    "\014\013\012\011\010\007\006\005\004\003\002"
    "\001\000\014\013\012\011\010\007\006\005\004"
    "\003\002\001\014\013\012\011\010\007\006\005"
    "\004\003\002\014\013\012\011\010\007\006\005"
    "\004\003\014\013\012\011\010\007\006\005\004"
    "\015\014\013\012\011\010\007\006\005\004\016"
    "\015\014\013\012\011\010\007\006\005\004\017"
    "\016\015\014\013\012\011\010\007\006\005\004"
    "\020\017\016\015\014\013\012\011\010\007\006"
    "\005\004\014\013\012\011\014\013\012\014\013"
    "\014"
};

const char *cckr_table_next_move[] ={
    //      direction 0
    "\000\003\005\006\010\011\012\020\021\022\023"
    "\030\031\032\033\034\035\036\037\040\041\042"
    "\043\000\044\045\046\047\050\051\052\053\054"
    "\055\056\000\057\060\061\062\063\064\065\066"
    "\067\070\000\071\072\073\074\075\076\077\100"
    "\101\000\103\104\105\106\107\110\111\112\113"
    "\115\116\117\120\121\122\123\124\125\126\130"
    "\131\132\133\134\135\136\137\140\141\142\144"
    "\145\146\147\150\151\152\153\154\155\156\157"
    "\000\000\000\000\160\161\162\163\000\000\000"
    "\000\000\164\165\166\000\167\170\000\171\000\000",
    //      direction 1
    "\000\002\004\005\007\010\011\017\020\021\022"
    "\000\030\031\032\033\034\035\036\037\040\041"
    "\042\043\000\044\045\046\047\050\051\052\053"
    "\054\055\056\000\057\060\061\062\063\064\065"
    "\066\067\070\000\071\072\073\074\075\076\077"
    "\100\101\102\103\104\105\106\107\110\111\112"
    "\114\115\116\117\120\121\122\123\124\125\127"
    "\130\131\132\133\134\135\136\137\140\141\143"
    "\144\145\146\147\150\151\152\153\154\155\156"
    "\000\000\000\000\000\160\161\162\163\000\000"
    "\000\000\000\164\165\166\000\167\170\000\171\000",
    //      direction 2
    "\000\000\000\002\000\004\005\000\007\010\011"
    "\000\013\014\015\016\017\020\021\022\023\024"
    "\025\026\000\030\031\032\033\034\035\036\037"
    "\040\041\042\000\044\045\046\047\050\051\052"
    "\053\054\055\000\057\060\061\062\063\064\065"
    "\066\067\000\071\072\073\074\075\076\077\100"
    "\000\102\103\104\105\106\107\110\111\112\000"
    "\114\115\116\117\120\121\122\123\124\125\000"
    "\127\130\131\132\133\134\135\136\137\140\141"
    "\000\143\144\145\146\147\150\151\152\153\154"
    "\155\156\000\160\161\162\000\164\165\000\167\000",
    //      direction 3
    "\000\000\000\001\000\002\003\000\004\005\006"
    "\000\000\000\000\000\007\010\011\012\000\000"
    "\000\000\013\014\015\016\017\020\021\022\023"
    "\024\025\026\030\031\032\033\034\035\036\037"
    "\040\041\042\044\045\046\047\050\051\052\053"
    "\054\055\057\060\061\062\063\064\065\066\067"
    "\000\071\072\073\074\075\076\077\100\101\000"
    "\102\103\104\105\106\107\110\111\112\113\000"
    "\114\115\116\117\120\121\122\123\124\125\126"
    "\000\127\130\131\132\133\134\135\136\137\140"
    "\141\142\147\150\151\152\160\161\162\164\165\167",
    //      direction 4
    "\000\000\001\000\002\003\000\004\005\006\000"
    "\000\000\000\000\007\010\011\012\000\000\000"
    "\000\000\014\015\016\017\020\021\022\023\024"
    "\025\026\027\031\032\033\034\035\036\037\040"
    "\041\042\043\045\046\047\050\051\052\053\054"
    "\055\056\060\061\062\063\064\065\066\067\070"
    "\071\072\073\074\075\076\077\100\101\000\102"
    "\103\104\105\106\107\110\111\112\113\000\114"
    "\115\116\117\120\121\122\123\124\125\126\000"
    "\127\130\131\132\133\134\135\136\137\140\141"
    "\142\000\150\151\152\153\161\162\163\165\166\170",
    //      direction 5
    "\000\000\003\000\005\006\000\010\011\012\000"
    "\014\015\016\017\020\021\022\023\024\025\026"
    "\027\000\031\032\033\034\035\036\037\040\041"
    "\042\043\000\045\046\047\050\051\052\053\054"
    "\055\056\000\060\061\062\063\064\065\066\067"
    "\070\000\072\073\074\075\076\077\100\101\000"
    "\103\104\105\106\107\110\111\112\113\000\115"
    "\116\117\120\121\122\123\124\125\126\000\130"
    "\131\132\133\134\135\136\137\140\141\142\000"
    "\144\145\146\147\150\151\152\153\154\155\156"
    "\157\000\161\162\163\000\165\166\000\170\000\000"
};



const char *cckr_table_rotate[] = {
    0,
    //      direction 1
    "\000\027\026\043\025\042\056\024\041\055\070"
    "\001\003\006\012\023\040\054\067\101\113\126"
    "\142\157\002\005\011\022\037\053\066\100\112"
    "\125\141\156\004\010\021\036\052\065\077\111"
    "\124\140\155\007\020\035\051\064\076\110\123"
    "\137\154\017\034\050\063\075\107\122\136\153"
    "\016\033\047\062\074\106\121\135\152\163\015"
    "\032\046\061\073\105\120\134\151\162\166\014"
    "\031\045\060\072\104\117\133\150\161\165\170"
    "\013\030\044\057\071\103\116\132\147\160\164"
    "\167\171\102\115\131\146\114\130\145\127\144"
    "\143",
    //      direction 2
    "\000\157\142\156\126\141\155\113\125\140\154"
    "\027\043\056\070\101\112\124\137\153\163\166"
    "\170\171\026\042\055\067\100\111\123\136\152"
    "\162\165\167\025\041\054\066\077\110\122\135"
    "\151\161\164\024\040\053\065\076\107\121\134"
    "\150\160\023\037\052\064\075\106\120\133\147"
    "\012\022\036\051\063\074\105\117\132\146\006"
    "\011\021\035\050\062\073\104\116\131\145\003"
    "\005\010\020\034\047\061\072\103\115\130\144"
    "\001\002\004\007\017\033\046\060\071\102\114"
    "\127\143\016\032\045\057\015\031\044\014\030"
    "\013",
    //      direction 3
    "\000\171\170\167\166\165\164\163\162\161\160"
    "\157\156\155\154\153\152\151\150\147\146\145"
    "\144\143\142\141\140\137\136\135\134\133\132"
    "\131\130\127\126\125\124\123\122\121\120\117"
    "\116\115\114\113\112\111\110\107\106\105\104"
    "\103\102\101\100\077\076\075\074\073\072\071"
    "\070\067\066\065\064\063\062\061\060\057\056"
    "\055\054\053\052\051\050\047\046\045\044\043"
    "\042\041\040\037\036\035\034\033\032\031\030"
    "\027\026\025\024\023\022\021\020\017\016\015"
    "\014\013\012\011\010\007\006\005\004\003\002"
    "\001",
    //      direction 4
    "\000\143\144\127\145\130\114\146\131\115\102"
    "\171\167\164\160\147\132\116\103\071\057\044"
    "\030\013\170\165\161\150\133\117\104\072\060"
    "\045\031\014\166\162\151\134\120\105\073\061"
    "\046\032\015\163\152\135\121\106\074\062\047"
    "\033\016\153\136\122\107\075\063\050\034\017"
    "\154\137\123\110\076\064\051\035\020\007\155"
    "\140\124\111\077\065\052\036\021\010\004\156"
    "\141\125\112\100\066\053\037\022\011\005\002"
    "\157\142\126\113\101\067\054\040\023\012\006"
    "\003\001\070\055\041\024\056\042\025\043\026"
    "\027",
    //      direction 5
    "\000\013\030\014\044\031\015\057\045\032\016"
    "\143\127\114\102\071\060\046\033\017\007\004"
    "\002\001\144\130\115\103\072\061\047\034\020"
    "\010\005\003\145\131\116\104\073\062\050\035"
    "\021\011\006\146\132\117\105\074\063\051\036"
    "\022\012\147\133\120\106\075\064\052\037\023"
    "\160\150\134\121\107\076\065\053\040\024\164"
    "\161\151\135\122\110\077\066\054\041\025\167"
    "\165\162\152\136\123\111\100\067\055\042\026"
    "\171\170\166\163\153\137\124\112\101\070\056"
    "\043\027\154\140\125\113\155\141\126\156\142"
    "\157"
};


const char *cckr_table_ruler_y =
"\000\005\005\006\005\006\007\005\006\007\010"
"\001\002\003\004\005\006\007\010\011\012\013"
"\014\015\002\003\004\005\006\007\010\011\012"
"\013\014\015\003\004\005\006\007\010\011\012"
"\013\014\015\004\005\006\007\010\011\012\013"
"\014\015\005\006\007\010\011\012\013\014\015"
"\005\006\007\010\011\012\013\014\015\016\005"
"\006\007\010\011\012\013\014\015\016\017\005"
"\006\007\010\011\012\013\014\015\016\017\020"
"\005\006\007\010\011\012\013\014\015\016\017"
"\020\021\012\013\014\015\013\014\015\014\015"
"\015";


const char *cckr_table_reverse[] = {
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


const char *cckr_nest_indices[] = {
    "\001\002\003\004\005\006\007\010\011\012",         // \001
    "\013\014\015\016\030\031\032\044\045\057",         // \003
    "\102\114\115\127\130\131\143\144\145\146",         // \005
    "\160\161\162\163\164\165\166\167\170\171"          // \002
    "\113\125\126\140\141\142\154\155\156\157",         // \006
    "\024\025\026\027\041\042\043\055\056\070",         // \004
};