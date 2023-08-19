#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct{
  int w, h;
  go_state** board;
  go_state whos_turn; 
} go_board;

const char go_sim[3] = {'O', '#', '.'};

go_return_type go_init(go_board** go_board_pp, int w, int h);
void go_print(go_board* board_ptr, FILE* restrict stream);
go_return_type go_move(go_board* board_ptr, int v_line, int h_line);

go_return_type go_init(go_board** go_board_pp, int w, int h){
  (*go_board_pp) = (go_board*)malloc(sizeof(go_board));
  go_board* go_board_ptr = (*go_board_pp);
  if(!go_board_ptr){
    return GO_FAIL;
  }
  go_board_ptr->w=w;
  go_board_ptr->h=h;
  go_board_ptr->board = (go_state**)malloc(sizeof(char*)*h);
  go_board_ptr->whos_turn = GO_WHITE;
  if(!go_board_ptr->board){
    return GO_FAIL;
  }
  for(int i = 0; i < h; ++i){
    go_board_ptr->board[i] = (go_state*)malloc(sizeof(go_state)*w);
    if(!go_board_ptr->board[i]){
      return GO_FAIL;
    }
    for(int j = 0; j < w; ++j){
      go_board_ptr->board[i][j] = GO_EMPTY;
    }
  }
    return GO_SUC;
}

void go_print(go_board* go_board_ptr, FILE* restrict stream){
  for (int i = 0;i < go_board_ptr->h; ++i){
    fprintf(stream, "%c ", 'a'+i);
    for (int j = 0; j < go_board_ptr->w; ++j) {
      fprintf(stream, "%c", go_sim[go_board_ptr->board[i][j]]);
    }
    fprintf(stream, "\n");
  }
  fprintf(stream, "  ");
  for (int j = 0; j < go_board_ptr->w; ++j) {
    fprintf(stream, "%d", j);
  }
  fprintf(stream, "\n");
}

go_return_type go_move(go_board* board_ptr, int v_line, int h_line){
  if(v_line>=0&&v_line<board_ptr->h&&h_line>=0&&h_line<board_ptr->w){
    board_ptr->board[v_line][h_line] = go_sim[(int)board_ptr->whos_turn];
  }else{
    printf("%i %i\n", v_line, h_line);
    return GO_INVALID;
  }
  board_ptr->whos_turn^=1;
  return GO_VALID;
}


int end = 0;

int main(void){
  printf("Hello, World!\n");
  
  go_board* go;
  if(go_init(&go, 10, 10)==GO_FAIL){
    printf("Go init failed\n");
  }

  while(!end){
    char buff[255];
    int vl = (int)getc(stdin)-'a';
    int hl = atoi(fgets(buff, 3, stdin));
    printf("%i\n", go_move(go, vl, hl));
    go_print(go, stdout);
 }


  return 0;  
}
