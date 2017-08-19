#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "risk_model.h"
#include "risk_view.h"

uint coord_to_index(position_t* position){
  //transforme des coordonneesde type position_t en un index
  return (*position).pos_y * MAP_X + (*position).pos_x;
}

void set_map(country_t* map[NB_CELLS], country_t* countries[], uint nb_countries){
  // defini toutes les cases comme "vide"
  for(uint j=0; j<NB_CELLS; j++){
    (*map[j]).name = "empty";
  }
  // puis place les pays en fonction de leur position
  for(uint i=0; i<nb_countries; i++){
    uint index = coord_to_index((*countries[i]).position);
    map[index] = countries[i];
  }
}

void print_map(country_t* map[NB_CELLS]){
  char empty[6] = "empty";
  for(uint i=0; i<NB_CELLS; i++){
    if(compare_char((*map[i]).name, empty)){
      printf(" ");
    }else{
      printf("%s", map[i].name);
    }if(i%(MAP_X-1) == 0){
      printf("\n");
    }
  }
  printf("\n");
}

void print_infos(user_t* user){
  printf("%s", (*user).color);
  printf("Gain this turn: %d | Nb stars: %d\n", (*user).gain, (*user).nb_stars);
  printf("Nb country : %d | Nb continent : %d", (*user).nb_country, (*user).nb_continent);
  printf("%s\n", KNRM);
}

void print_ranking(user_t* users[NB_MAX_PLAYERS]){
  for(uint i=0; i<NB_MAX_PLAYERS; i++){
    printf("%s", (*user).color);
    printf("%d.%s ", i, (*user).name);
    printf("%s| ", KNRM);
  }
  printf("\n");
}
