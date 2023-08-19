#include <stdlib.h>
#include <stdio.h>
#include "go.h"

const char go_sim[3] = {'O', '#', '.'};

go_return_type go_init(go_t** go_pp, int w, int h){
  (*go_pp) = (go_t*)malloc(sizeof(go_t));
  go_t* go_ptr = (*go_pp);
  if(!go_pp){
    return GO_FAIL;
  }
  go_ptr->w=w;
  go_ptr->h=h;
  go_ptr->nodes = (go_board_node_t**)malloc(sizeof(go_board_node_t*)*h);
  go_ptr->who_turn = GO_WHITE;
  if(!go_ptr->nodes)
    return GO_FAIL;
  
  for(int i = 0; i < h; ++i){
    go_ptr->nodes[i] = (go_board_node_t*)malloc(sizeof(go_board_node_t)*w);
    if(!go_ptr->nodes[i])
      return GO_FAIL;
  }
  int dir_flag;
  const char up     = 1;
  const char right  = 2;
  const char down   = 4;
  const char left   = 8;
  for(int i = 0; i < h; ++i){
    dir_flag = 0xf;
    for(int j = 0; j < w; ++j){  
      go_ptr->nodes[i][j].nodes = (go_board_node_t**)malloc(sizeof(go_board_node_t*)*4);
      if(!go_ptr->nodes[i][j].nodes)
        return GO_FAIL;
      dir_flag^=(i>0)   <<0;
      dir_flag^=(j<w-1) <<2;
      dir_flag^=(j>0)   <<3;
      dir_flag^=(j<h-1) <<1;
      if(dir_flag&up)
        go_ptr->nodes[i][j].nodes[0] = &(go_ptr->nodes[i-1][j]);
      if(dir_flag&right)
        go_ptr->nodes[i][j].nodes[1] = &(go_ptr->nodes[i][j+1]);
      if(dir_flag&down)
        go_ptr->nodes[i][j].nodes[2] = &(go_ptr->nodes[i+1][j]);
      if(dir_flag&left)
        go_ptr->nodes[i][j].nodes[3] = &(go_ptr->nodes[i][j-1]);
      go_ptr->nodes[i][j].state = GO_EMPTY;
    }
  }
  return GO_SUC;
}

void go_print(go_t* go_ptr, FILE* restrict stream){
  printf("%c %c %c\n", go_sim[0], go_sim[1], go_sim[2]);

  for (int i = 0;i < go_ptr->h; ++i){
    fprintf(stream, "%c ", 'a'+i);
    for (int j = 0; j < go_ptr->w; ++j) {
      fprintf(stream, "%c", go_sim[go_ptr->nodes[i][j].state]);
    }
    fprintf(stream, "\n");
  }
  fprintf(stream, "  ");
  for (int j = 0; j < go_ptr->w; ++j) {
    fprintf(stream, "%d", j);
  }
  fprintf(stream, "\n");
}

go_return_type go_validate_move(go_t* go_ptr, int v_line, int h_line){
  if(v_line>=0&&v_line<go_ptr->h&&h_line>=0&&h_line<go_ptr->w&&go_ptr->nodes[v_line][h_line].state==GO_EMPTY){
    go_ptr->nodes[v_line][h_line].state = go_sim[go_ptr->who_turn];
  }else{
    printf("your move: %c %i %i>=0=%i %i<%i=%i %i>=0=%i %i<%i=%i\n", (char)(v_line+'a'), h_line, v_line, v_line>=0, v_line, go_ptr->h, v_line<go_ptr->h, h_line, h_line>=0, h_line, go_ptr->h, h_line<go_ptr->h);
    return GO_INVALID;
  }
  go_ptr->who_turn^=1;
  return GO_VALID;
}
