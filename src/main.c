#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "go.h"

int end = 0;

int main(void){
  printf("Hello, World!\n");
  
  go_t* go;
  if(go_init(&go, 4, 4)==GO_FAIL){
    printf("Go init failed\n");
  }

  while(!end){
    char buff[255];
    int vl = ((int)getc(stdin)-'a');
    printf("%i\n", vl);
    int hl = atoi(fgets(buff, 3, stdin));
    go_validate_move(go, vl, hl);
    go_print(go, stdout);
 }
  return 0;  
}
