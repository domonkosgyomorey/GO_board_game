#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "go.h"
#include "go_renderer.h"
int end = 0;

int main(void){
  printf("Hello, World!\n");
  
  go_renderer_start(9, 9);
  
  return 0;
  
  go_t* go;
  if(go_init(&go, 7, 7)==GO_FAIL){
    printf("Go init failed\n");
  }



  while(!end){
    go_print(go, stdout);
    char buff[255];
    int vl = ((int)getc(stdin)-'a');
    int hl = atoi(fgets(buff, 3, stdin));
    go_validate_move(go, vl, hl);
    go_remove_closed_group(go);
    printf(" black score:%i\n white score:%i\n", go->black_score, go->white_score);
  }
  return 0;  
}
