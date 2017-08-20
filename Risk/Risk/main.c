#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "risk_initializer.h"
#include "risk_view.h"
#include "risk_model.h"

state_t state = {false,false,false,false};
state_t* p_state = &state;

position_t curseur = {0,0};
position_t* p_curseur = &curseur;

int main(int arg_c, char* arg_v){
  if(argc > 3){

  }
  (*p_state).initialize = true;
  if((*p_state).initialize){
    uint nb_countries = find_nb_countries(arg_v[1]);
    country_t* countries[] =  create_countries(arg_v[1]);
    set_connnections(countries, nb_countries);
    //uint nb_continents = find_nb_continents(arg_v[2]);
    continent_t* continents[] = create_continents(countries,nb_countries,arg_v[2]);
    (*p_state).initialize = false;
    (*p_state).menu = true;
  }
  if((*p_state).menu){
    uint nb_players = ask_nb_players();
    user_t* users[NB_MAX_PLAYERS] = ask_users();
    if(nb_players < 5){
      set_bots(users, nb_players);
    }
    set_colors_to_users(users);
    set_country_to_owner(countries, nb_countries, users);
  }
  return EXIT_SUCCESS;
}
