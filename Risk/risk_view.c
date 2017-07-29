#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "risk_model.h"
#include "risk_view.h"

uint coord_to_index(position_t* position){
  return (*position).pos_y * 10 + (*position).pos_x;
}

/*void char_fusion(char char1[], char char2[]){
  char result[];
  uint index = 0;
  while(char1[index] != '\0'){
    result[index] = char1[index];
    index++;
  }
  result[i] = ' ';
  index++;
  uint j=0;
  while(char2[j] != '\0'){
    result[index] = char2[j];
    index++, j++;
  }
  return result;
}

char* game_array(continent_t* continents[],user_t* user,uint nb_continent){
  static char map[nb_cells];
  for(uint cell=0; cell<nb_cells-1; cell++){
    map[cell] = 'N';
  }
  return &(map);
}*/

void set_countries(country_t* map[NB_CELLS], country_t* countries[], uint nb_countries){
  for(uint i=0; i<nb_countries; i++){
    uint index = coord_to_index((*countries[i]).position);
    map[index] = countries[i];
  }
}

void print_map(country_t* map[NB_CELLS]){
  for(uint i=0; i<NB_CELLS; i++){
    char* country_name = (*map[i]).name;
    printf("%s\n", country_name);
    if(i%10 == 0){
      printf("\n");
    }
  }
}

void swap_user(user_t* users[NB_MAX_PLAYERS], uint i, uint j){
  user_t* p_swap = users[i];
  users[i] = users[j];
  users[j] = p_swap;
}

void ranking_users(user_t* users[NB_MAX_PLAYERS], uint nb_players){
  for(uint i=0; i<nb_players; i++){
    uint j = i;
    while(nb_max_players-j >= 0){
      if((*users[j]).nb_country > (*users[j-1]).nb_country){
        swap_user(users, j, j-1);
        j--;
      }
    }
  }
}

void print_infos(user_t* users[NB_MAX]){
  ranking_users(users, NB_MAX_PLAYERS);
  uint count = 0;
  do{
    for(uint i=0; i<NB_MAX_PLAYERS; i++){
      if(count == 0){
        printf("%d.%s", i+1, (*users[i]).name);
      }else{
        printf("Points:%d", (*users[i]).gain);
      }
    }
    printf("\n");
    count++;
  }while(count<2);
}
