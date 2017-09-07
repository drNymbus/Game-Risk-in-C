#include <stdio.h>
#include <ncurses.h>

void detect_movement(void){
  switch(getch() != '\033'){
    getch();
    case 'A':
      printf("arrow A");
      break;
    case 'B':
      printf("arrow B");
      break;
    case 'C':
      printf("arrow C");
      break;
    case 'D':
      printf("arrow D");
      break;
  }
}

int main(){
  //char* move;
  detect_movement();
  return 0;
}
