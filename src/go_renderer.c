#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <raylib.h>
#include "go_renderer.h"
#include "go.h"

go_t* go_ptr;

void go_renderer_draw_pieces(int cw, int ch){
  for(int i = 0; i < go_ptr->h; ++i){
    for(int j = 0; j < go_ptr->w; ++j){
      if(go_ptr->nodes[i][j].state!=GO_EMPTY){
        DrawCircle(GO_PADDING+j*cw, GO_PADDING+i*ch, (int)((cw<ch?ch:cw)/2), go_ptr->nodes[i][j].state?BLACK:RAYWHITE);
      }
    }
  }
}

// Draw the board and the text and etc.
void go_renderer_show(int cw, int ch){
 
  // Grid
  float round_bug = 2.3f;
  for(int i = 0; i < go_ptr->h; ++i){
    Vector2 s = {GO_PADDING, (i*ch)+GO_PADDING};
    Vector2 e = {GO_BOARD_SIZE-(int)(cw/round_bug), (i*ch)+GO_PADDING};
    DrawLineEx(s, e, 2, (Color){0, 0, 0, 128});
  }
  for(int i = 0; i < go_ptr->w; ++i){
    Vector2 s = {(i*cw)+GO_PADDING, GO_PADDING};
    Vector2 e = {(i*cw)+GO_PADDING, GO_BOARD_SIZE-(int)(ch/round_bug)};
    DrawLineEx(s, e, 2, (Color){0, 0, 0, 128});
  }

  // Scores
  char buff[255];
  sprintf(buff, "Black score: %i", go_ptr->black_score);
  DrawText(buff, GO_TXT_POS_X, GO_TXT_POS_Y, GO_TXT_FNT_SIZE, DARKBROWN);
  sprintf(buff, "White score: %i", go_ptr->white_score);
  DrawText(buff, GO_TXT_POS_X+GO_TXT_PADD, GO_TXT_POS_Y, GO_TXT_FNT_SIZE, DARKBROWN);

  // In hand piece
  int xi = GetMouseX()+GO_PADDING+cw/4;
  int yi = GetMouseY()+GO_PADDING+ch/4;
  if(xi>GO_PADDING&&xi<GO_PADDING+GO_BOARD_SIZE&&yi>GO_PADDING&&yi<GO_PADDING+GO_BOARD_SIZE){
    xi /= cw;           // Remove the remainder from xi
    xi *= cw;
    yi /= ch;
    yi *= ch;
  }
  DrawCircle(xi-(int)(cw/2.5), yi-(int)(ch/2.5), (int)((cw<ch?ch:cw)/2.5), go_ptr->who_turn?BLACK:RAYWHITE);
 
  // On board piece
  go_renderer_draw_pieces(cw, ch);
}

void go_renderer_start(int go_board_w, int go_board_h){  
  go_ptr = (go_t*)malloc(sizeof(go_t));
  go_init(&go_ptr, go_board_w, go_board_h);

  InitWindow(GO_WINDOW_SIZE, GO_WINDOW_SIZE+GO_PADDING, "GO");
  SetTargetFPS(60);
  
  while(!WindowShouldClose()){
    int cw = GO_BOARD_SIZE/(go_ptr->w);
    int ch = GO_BOARD_SIZE/(go_ptr->h);
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ 
      int xi = GetMouseX()+GO_PADDING+cw/4;
      int yi = GetMouseY()+GO_PADDING+ch/4;
      if(xi>GO_PADDING&&xi<GO_PADDING+GO_BOARD_SIZE&&yi>GO_PADDING&&yi<GO_PADDING+GO_BOARD_SIZE){
        xi /= cw;           // Remove the remainder from xi
        yi /= ch;
        go_validate_move(go_ptr, yi-1, xi-1);
        go_remove_closed_group(go_ptr);
        go_print(go_ptr, stdout);
      }
    }

    BeginDrawing();
      ClearBackground((Color){242, 188, 107, 255});
      go_renderer_show(cw, ch);
    EndDrawing();
  }
  CloseWindow();
}
