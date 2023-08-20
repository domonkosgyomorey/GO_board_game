#include <stdlib.h>
#include <stdio.h>
#include "go.h"

const char go_sim[3] = {'O', '#', '.'};

go_return_type go_init(go_t** go_pp, int w, int h){
  w = w>GO_MAX_BOARD_SIZE?GO_MAX_BOARD_SIZE:w;
  h = h>GO_MAX_BOARD_SIZE?GO_MAX_BOARD_SIZE:w;

  (*go_pp) = (go_t*)malloc(sizeof(go_t));
  go_t* go_ptr = (*go_pp);
  if(!go_pp){
    return GO_FAIL;
  }

  go_ptr->w=w;
  go_ptr->h=h;
  go_ptr->who_turn = GO_WHITE;
  go_ptr->nodes = (go_board_node_t**)malloc(sizeof(go_board_node_t*)*h);
  if(!go_ptr->nodes)
    return GO_FAIL;

  
  for(int i = 0; i < h; ++i){
    go_ptr->nodes[i] = (go_board_node_t*)malloc(sizeof(go_board_node_t)*w);
    if(!go_ptr->nodes[i])
      return GO_FAIL;
  }

  int global_id_count = 0;
  for(int i = 0; i < h; ++i){
    for(int j = 0; j < w; ++j){  
      go_ptr->nodes[i][j].nodes = (go_board_node_t**)malloc(sizeof(go_board_node_t*)*4);
      if(!go_ptr->nodes[i][j].nodes)
        return GO_FAIL;

      if(i>0){
        go_ptr->nodes[i][j].nodes[0] = &(go_ptr->nodes[i-1][j]);
      }
      if(j<w-1){
        go_ptr->nodes[i][j].nodes[1] = &(go_ptr->nodes[i][j+1]);
      }
      if(i<h-1){
        go_ptr->nodes[i][j].nodes[2] = &(go_ptr->nodes[i+1][j]);
      }
      if(j>0){
        go_ptr->nodes[i][j].nodes[3] = &(go_ptr->nodes[i][j-1]);
      }
      go_ptr->nodes[i][j].state = GO_EMPTY;
      go_ptr->nodes[i][j].id = global_id_count++;
    }
  }
  return GO_SUC;
}

void go_print(go_t* go_ptr, FILE* restrict stream){
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
  if(v_line>=0&&v_line<go_ptr->h&&h_line>=0&&h_line<go_ptr->w){
    if(go_ptr->nodes[v_line][h_line].state==GO_EMPTY){
      go_ptr->nodes[v_line][h_line].state = go_ptr->who_turn;
    }else{
      printf("Wrong move: %c%i position isn't empty\n", v_line+'a', h_line);
      return GO_INVALID;
    }
  }else{
    printf("Wrong move: %c%i position is outside of the map\n", (char)(v_line+'a'), h_line);
    return GO_INVALID;
  }
  go_ptr->who_turn^=1;
  go_ptr->last_move_v = v_line;
  go_ptr->last_move_h = h_line;
  return GO_VALID;
}

void go_count_free_space_rec(go_board_node_t** rec_list, go_board_node_t* node_ptr, int* frees){
  for(int i = 0; i < 4; ++i){ 
    go_board_node_t* node = node_ptr->nodes[i];
    if(node&&!rec_list[node->id]){
      rec_list[node->id] = node;
      if(node->state==node_ptr->state){
        go_count_free_space_rec(rec_list, node, frees);
      }else if(node->state==GO_EMPTY){
        (*frees)++;
      }
    }
  }
}

int go_node_is_free(int w, int h, go_board_node_t* node){
  go_board_node_t** rec_list = (go_board_node_t**)malloc(sizeof(go_board_node_t*)*h*w);
  int frees = 0;
  go_count_free_space_rec(rec_list, node, &frees);
  return frees;
}

void go_remove_closed_group(go_t* go_ptr){
  int remove_tags[go_ptr->h][go_ptr->w];
  for(int i = 0; i < go_ptr->h; ++i){
    for(int j = 0; j < go_ptr->w; ++j){
      if(go_ptr->nodes[i][j].state==GO_EMPTY||(i==go_ptr->last_move_v&&j==go_ptr->last_move_h)){
        continue;
      }
      remove_tags[i][j] = !(go_node_is_free(go_ptr->w, go_ptr->h, &go_ptr->nodes[i][j]));
    }
  }
  for(int i = 0; i < go_ptr->h; ++i){
    for(int j = 0; j < go_ptr->w; ++j){
      if(remove_tags[i][j]==1){
        if(go_ptr->nodes[i][j].state==GO_WHITE){
          go_ptr->black_score++;
        }else{
          go_ptr->white_score++;
        }
        go_ptr->nodes[i][j].state = GO_EMPTY;
      }
    }
  }
}

