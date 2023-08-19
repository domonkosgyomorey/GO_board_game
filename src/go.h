#ifndef GO_H
#define GO_H

#include <stdio.h>

typedef enum{
  GO_WHITE = 0,
  GO_BLACK,
  GO_EMPTY,
} go_state;

typedef enum{
  GO_FAIL=0,
  GO_SUC,
  GO_VI_OFF,
  GO_VALID,
  GO_INVALID,
} go_return_type;

typedef struct go_board_node{
  go_state state;
  struct go_board_node** nodes;
} go_board_node_t;

typedef struct {
  int w, h;
  go_board_node_t** nodes; 
  go_state who_turn;
} go_t;

go_return_type go_init(go_t** go_board_pp, int w, int h);
void go_print(go_t* board_ptr, FILE* restrict stream);
go_return_type go_validate_move(go_t* board_ptr, int v_line, int h_line);

#endif // GO_H
