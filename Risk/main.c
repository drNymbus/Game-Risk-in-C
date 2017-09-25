#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#include "risk_model.h"
#include "risk_view_initialize.h"

int main(int arg_c, char** arg_v){

  state_t state = {true,false,false,false,false,false,false};
  state_t* p_state = &state;

  country_t* map[NB_CELLS];
  initialize_map(map);

  position_t curseur = {0,0,-1};
  position_t* p_curseur = &curseur;

  uint nb_countries;
  country_t* countries[nb_countries];

  uint nb_continents;
  continent_t* continents;

  uint nb_players;
  user_t* users[nb_players];

  while((*p_state).initialize){
    nb_countries = find_nb_countries(arg_v[1]);
    countries[nb_countries] = create_countries(arg_v[1]);
    set_connections(countries, nb_countries);
    nb_continents = find_nb_continents(arg_v[2]);
    continents = create_continents(countries, nb_countries, arg_v[2]);

    nb_players = ask_nb_players();
    users[nb_players] = ask_users(nb_players);
    //set users;

    (*p_state).initialize = false;
    (*p_state).set_turn = true;
  }
  for(uint i=0; i<nb_players; i++){
    char* instructions = NULL;
    while((*p_state).set_turn){
      while(!(compare_char(instructions[1], "Attack phase")) || instructions == NULL){
        display_game(map, users, i, p_state);
        instructions = ask_instructions();
        if(compare_char(instructions[1], "Use stars")){
          char y_or_no[2] = {'Y','\0'};
          if((*users[i]).nb_stars > 5){
            printf("Are you sure (Y/N)?\nYou can also buy a boost\n");
            scanf("%c", &y_or_no);
          }if(compare_char(y_or_no, "Y")){
          (*users[i]).gain += (*users[i]).nb_stars * 2;
          }
        }else if(compare_char(instructions[1], "Buy boost")){
          (*users[i]).boost = true;
          (*users[i]).nb_stars -= 5;
          if((*users[i]).nb_stars < 5){
            printf("You cannot buy a boost.\n");
            (*users[i]).boost = false;
            (*users[i]).nb_stars += 5;
          }
        }else if(compare_char(instructions[1], "Add troops")){
          if((*users[i]).gain > 0){
            uint index = (uint) instructions[0];
            uint gain = (uint) instructions[2];
            add_troops(countries[index], gain);
            (*users[i]).gain -= gain;
          }else{
            printf("You don't have troops anymore.\n");
          }
        }
      }
      (*p_state).set_turn = false;
      (*p_state).turn = true;
    }
    instructions = NULL;
    while((*p_state).turn){
      while(!(compare_char(instructions[1], "End")) || instructions == NULL){
        display_game(map, users, i, p_state);
        instructions = ask_instructions();
        if(compare_char(instructions[1], "Move")){
          int* move = ask_move();
          move_troops(move[0], move[2], move[1]);
          (*p_state).turn_move = true;
        }else if(compare_char(instructions[1], "Attack")){
          if((*p_state).turn_move){
            char y_or_no[2] = {'Y','\0'};
            printf("Care once you've attack you cannot move troops\n");
            scanf("Are you sure (Y/N): %s", &y_or_no);
            if(compare_char(y_or_no, "Y")){
              uint nb_countries = (*users[i]).nb_country;
              int* att = ask_attack();
              int* result = attack(att[0], att[1], (*users[i]).boost);
              printf("Attack loss: %d\nDefense loss: %d", result[1], result[0]);
              if(result[2])
                printf("You won a country: %s", (*users[i]).countries[nb_countries]);
                int nb_troops = ask_troops();
                add_troops(countries[att[0]], nb_troops);
            }
          }else{
            int* att = ask_attack();
            int* result = attack(att[0], att[1], (*users[i]).boost);
            printf("Attack loss: %d\nDefense loss: %d", result[1], result[0]);
          }
        }
      }
      (*p_state).turn = false;
      (*p_state).turn_move = false;
      (*p_state).end_turn = true;
    }
    while((*p_state).end_turn){

    }
  }
  return EXIT_SUCCESS;
}
