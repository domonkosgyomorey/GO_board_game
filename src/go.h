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
  int id;
  struct go_board_node** nodes;
} go_board_node_t;

typedef struct {
  int w, h;
  go_board_node_t** nodes; 
  int white_score;
  int black_score;
  int last_move_v, last_move_h;
  go_state who_turn;
} go_t;

go_return_type go_init(go_t** go_pp, int w, int h);
void go_print(go_t* go_ptr, FILE* stream);
go_return_type go_validate_move(go_t* go_ptr, int v_line, int h_line);
int go_count_groupy_free_space(go_t* go_ptr, go_board_node_t* node);
void go_remove_closed_group(go_t* go_ptr);

#endif // GO_H
