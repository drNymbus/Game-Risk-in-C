#include <stdio.h>
#include <stdlib.h>

#include "risk_view_initialize.h"

uint coord_to_index(position_t* position){
  //transforme des coordonneesde type position_t en un index
  return (*position).pos_y * MAP_X + (*position).pos_x;
}

void set_map(country_t* map[NB_CELLS], country_t* countries[], uint nb_countries){
  uint i;
  // place les pays en fonction de leur position (position_t)
  for(i=0; i<nb_countries; i++){
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
      printf("%s", (*(*map[i]).owner).color);
      printf("%d.%s(%d)", i, (*map[i]).name, (*map[i]).current_troop);
      printf("%s", KNRM);
    }if(i%(MAP_X-1) == 0){
      printf("\n");
    }
  }
  printf("\n");
}
/*
void print_menu(state_t* state){
  if((*state).set_turn){
    for(uint i=0; i<4; i++){
      if((*position).pos_curseur == i){
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
      if((*position).pos_curseur == i){
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
*/
void print_infos(user_t* user){
  printf("  ===============================================\n");
  printf("%s", (*user).color);
  printf("Gain this turn: %d | Nb stars: %d\n", (*user).gain, (*user).nb_stars);
  printf("Nb country : %d | Nb continent : %d", (*user).nb_country, (*user).nb_continent);
  printf("%s\n", KNRM);
}

void print_ranking(user_t* users[NB_MAX_PLAYERS]){
  for(uint i=0; i<NB_MAX_PLAYERS; i++){
    printf("%s", (*users[i]).color);
    printf("%d.%s ", i, (*users[i]).name);
    printf("%s| ", KNRM);
  }
  printf("\n");
}

void print_instructions(state_t* state){
  printf("  ===================================\n");
  printf("  ===================================\n");
  if((*state).menu){
    printf("Enter the number of players");
    printf(", then enter the name then press enter for each player\n");
  }else if((*state).set_turn){
    printf("Choose \"Use stars\" to use yours stars (* = 2xtroop)\n");
    printf("\"Buy boost\" to buy an extra dice for this turn\n");
    printf("\"Add troops\" to add troops in a country\n");
    printf("\"Attack phase\" to pass to attack phase\n");
  }else if((*state).turn){
    printf("Choose \"Attack\" to attack a country\n");
    printf("\"Move\" to move troops to close country (once per turn)\n");
    printf("\"End\" to finish your turn\n");
  }
  printf("\nEnter following this schema \"index <move> nb_troops\".\n");
  printf("If no need of index or nb_troops then replace them by -1.\n");
}

void display_game(country_t* map[NB_CELLS], user_t* users[NB_MAX_PLAYERS], uint index_player, state_t* state){
  position_t position = {0,0,0};
  print_map(map, &position);
  print_infos(users[index_player]);
  print_ranking(users);
  print_instructions(state);
}
