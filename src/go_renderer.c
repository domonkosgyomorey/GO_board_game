#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include "go_renderer.h"
#include "go.h"

go_t* go_ptr;

void go_renderer_show(){
  int cw = GO_BOARD_SIZE/(go_ptr->w+1);
  int ch = GO_BOARD_SIZE/(go_ptr->h+1);
  for(int i = 0; i < go_ptr->h+2; ++i){
    Vector2 s = {GO_PADDING, (i*ch)+GO_PADDING};
    Vector2 e = {GO_BOARD_SIZE+GO_PADDING, (i*ch)+GO_PADDING};
    DrawLineEx(s, e, 2, (Color){0, 0, 0, 128});
  }
  for(int i = 0; i < go_ptr->w+2; ++i){
    Vector2 s = {(i*cw)+GO_PADDING, GO_PADDING};
    Vector2 e = {(i*cw)+GO_PADDING, GO_BOARD_SIZE+GO_PADDING};
    DrawLineEx(s, e, 2, (Color){0, 0, 0, 128});
  }
  char buff[255];
  sprintf(buff, "Black score: %i", go_ptr->black_score);
  DrawText(buff, GO_TXT_POS_X, GO_TXT_POS_Y, GO_TXT_FNT_SIZE, DARKBROWN);
  sprintf(buff, "White score: %i", go_ptr->white_score);
  DrawText(buff, GO_TXT_POS_X+GO_TXT_PADD, GO_TXT_POS_Y, GO_TXT_FNT_SIZE, DARKBROWN);

}

void go_renderer_start(int go_board_w, int go_board_h){
  
  go_ptr = (go_t*)malloc(sizeof(go_t));
  go_init(&go_ptr, go_board_w, go_board_h);

  InitWindow(GO_WINDOW_SIZE, GO_WINDOW_SIZE+GO_PADDING, "GO");
  SetTargetFPS(60);
  
  while(!WindowShouldClose()){

    BeginDrawing();
      ClearBackground((Color){242, 188, 107, 255});
      go_renderer_show();
    EndDrawing();

    go_renderer_show();
  }
  CloseWindow();
}
