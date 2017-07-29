#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "risk_view.h"
#include "risk_model.h"

country_t* create_country(char name, char owner, uint nb_conn, char conn[], uint max_troop, char continent){
  country_t country = {name,owner,nb_conn,conn,0,max_troop,continent,false};
  return &(country);
}

int main(uint nb_players){
  country_t* Canada = create_country('Canada','Bot',2,{'USA','Alaska'},50,'North America');
  country_t* USA = create_country('USA','Bot',1,{'Canada'},50,'North America');
  country_t* Alaska = create_country('Alaska','Bot',1,{'Canada'},15,'North America');
  printf('Canada : %c, 2 connections: %d, Continent : %c',(*Canada).country,(*Canada).nb_connections,(*Canada).continent);
  return EXIT_SUCCESS;
}
