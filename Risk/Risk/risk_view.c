#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "risk_model.h"
#include "risk_view.h"
#include "risk_initializer.h"

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

void print_map(country_t* map[NB_CELLS], position_t* position){
  char empty[6] = "empty";
  for(uint i=0; i<NB_CELLS; i++){
    if(compare_char((*map[i]).name, empty)){
      printf(" ");
    }else{
      if(compare_position(position, (*map[i]).position)){
        printf("!");
      }
      printf("%s", map[i].name);
    }if(i%(MAP_X-1) == 0){
      printf("\n");
    }
  }
  printf("\n");
}

void print_menu(state_t* state){
  if((*state).set_turn){
    for(uint i=0; i<4; i++){
      if((*position).pos_x == i){
        printf("!");
      }
      if(i == 0){
        printf("Use_stars  ");
      }else if(i == 1){
        printf("Buy_boost  ");
      }else if(i == 2){
        printf("Add_troops ");
      }else if(i == 3){
        printf("Attack phase");
      }
    }
    printf("\n");
  }
  if((*state).turn){
    for(uint j=0; j<4; j++){
      if((*position).pos_x == i){
        printf("!");
      }
      if(i == 0){
        printf("Attack  ");
      }else if(i == 1){
        printf("Move    ");
      }else if(i == 2){
        printf("End");
      }
    }
    printf("\n");
  }
}

void print_infos(user_t* user){
  printf("     ===============================================\n", );
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

void print_instructions(state_t* state){
  if((*state).menu){
    printf("  ===================================\n");
    printf("  ===================================\n");
    printf("Enter the number of players");
    printf(", then enter the name then press enter for each player\n");
  }else if((*state).set_turn){
    printf("  ===================================\n");
    printf("  ===================================\n");
    printf("Choose \"Use stars\" to use yours stars (* = 2xtroop)\n");
    printf("\"Buy boost\" to buy an extra dice for this turn\n", );
    printf("\"Add troops\" to add troops in a country\n");
    printf("\"Attack phase\" to pass to attack phase\n", );
  }else if((*state).turn){
    printf("  ===================================\n");
    printf("  ===================================\n");
    printf("Choose \"Attack\" to attack a country\n");
    printf("\"Move\" to move troops to close country (once per turn)\n");
    printf("\"End\" to finish your turn\n", );
  }
}
