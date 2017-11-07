#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "risk_view_initialize.h"

/*=======================INIITIALIZE========================*/

uint get_nb_countries(void) {
  FILE* f_countries = fopen("./initializer/country.txt", "r");
  uint nb_countries;

  int c = fscanf(f_countries, "%u\n", &nb_countries);
  if(c != 1) {
    fprintf(stderr, "Initialier file country.txt corrompt\n");
    exit(1);
  }

  fclose(f_countries);
  return nb_countries;
}

country_t* create_countries(void) {

  uint nb_total_countries = get_nb_countries();
  country_t* countries = (country_t*) malloc(nb_total_countries * sizeof(country_t));
  if(countries == NULL) {
    fprintf(stderr, "Cannot create all countries\n");
    fprintf(stderr, "Cannot allocate memory\n");
    exit(1);
  }

  FILE* f_countries = fopen("./initializer/country.txt", "r");
  int c = fscanf(f_countries, "\n");
  if(c != 1) {
    fprintf(stderr, "Initializer file country.txt\n");
    exit(1);
  }

  for(uint i=0; i<nb_total_countries; i++){
    country_t* country = country_alloc();
    c = fscanf(f_countries,"%d %s", &country->id, country->name);
    if(c != 2) {
      fprintf(stderr, "Initialier file country.txt corrompt\n");
      exit(1);
    }


    uint x, y;
    c = fscanf(f_countries, "%d %d", &x, &y);
    if(c != 2) {
      fprintf(stderr, "Initialier file country.txt corrompt\n");
      exit(1);
    }
    position_t* position = create_position(x, y);
    country->position = position;

    c = fscanf(f_countries, "%d", &country->nb_connections);
    if(c != 1) {
      fprintf(stderr, "Initialier file country.txt corrompt\n");
      exit(1);
    }

    for(uint j=0; j < country->nb_connections; j++){
      c = fscanf(f_countries,"%d", &country->connections[j]);
      if(c != 1) {
        fprintf(stderr, "Initialier file country.txt corrompt\n");
        exit(1);
      }

    }
    countries[i] = *country;
    c = fscanf(f_countries,"\n");
    if(c != 1) {
      fprintf(stderr, "Initialier file country.txt corrompt\n");
      exit(1);
    }
  }

  fclose(f_countries);
  return countries;
}

uint get_nb_continents(void){
  FILE* continents = fopen("./initializer/continent.txt", "r");
  uint nb_continents;

  int c = fscanf(continents, "%d\n", &nb_continents);
  if(c != 1) {
    fprintf(stderr, "Initialier file continent.txt corrompt\n");
    exit(1);
  }

  fclose(continents);
  return nb_continents;
}

continent_t* create_continents(country_t* countries, uint nb_countries){

  uint nb_continents = get_nb_countries();
  continent_t* continents = (continent_t*) malloc(nb_countries * sizeof(continent_t));
  if(countries == NULL) {
    fprintf(stderr, "Cannot create all countries\n");
    fprintf(stderr, "Cannot allocate memory\n");
    exit(1);
  }

  FILE* f_continents = fopen("./initializer/continent.txt", "r");
  int c = fscanf(f_continents, "\n");
  if(c != 1) {
    fprintf(stderr, "Initialier file country.txt corrompt\n");
    exit(1);
  }

  for(uint i=0; i < nb_continents; i++){
    continent_t* continent = continent_alloc();
    c = fscanf(f_continents, "%s %d\n", continent->name, &continent->nb_country);
    if(c != 2) {
      fprintf(stderr, "Initialier file country.txt corrompt\n");
      exit(1);
    }

    for(uint j=0; j < continent->nb_country; j++){
      c = fscanf(f_continents, "%d", &(continent->countries[j]));
      if(c != 1) {
        fprintf(stderr, "Initialier file country.txt corrompt\n");
        exit(1);
      }
    }
    continents[i] = *continent;
    c = fscanf(f_continents, "\n");
    if(c != 1) {
      fprintf(stderr, "Initialier file country.txt corrompt\n");
      exit(1);
    }
  }

  fclose(f_continents);
  return continents;
}

/*===================USER INTERACTION=====================*/

uint ask_nb_players(void){
  uint nb_players;

  int c = fscanf(stdin, "Enter the number of players : %d", &nb_players);
  if(c != 1) {
    fprintf(stderr, "Initialier file country.txt corrompt\n");
    exit(1);
  }

  return nb_players;
}

void ask_users_names(user_t* users[], uint nb_players){
  char** names = (char**) malloc(sizeof(char)*nb_players);
  for(uint i=0; i < nb_players; i++) {
    char* u_name = (char*) malloc(sizeof(char)*LENGTH_MAX);
    if(u_name == NULL) {
      fprintf(stderr, "Cannot create name\n");
      fprintf(stderr, "Cannot allocate memery\n");
      exit(1);
    }
    names[i] = u_name;
  }

  printf("Enter names : (\\in case\\length max is 30)\n");
  for(uint i=0; i<nb_players; i++){
    printf("%d.", i+1);
    int c = fscanf(stdin, "%s\n", names[i]);
    if(c != 1) {
      fprintf(stderr, "Initialier file country.txt corrompt\n");
      exit(1);
    }
    users[i]->name = names[i];
  }
}

int ask_troops(void){
  int nb_troops;

  printf("Enter the nb of troops you want to move: ");
  int c = fscanf(stdin, "%d", &nb_troops);
  if(c != 1) {
    fprintf(stderr, "Initialier file country.txt corrompt\n");
    exit(1);
  }

  return nb_troops;
}

char* ask_move(void){
  char* move = (char*) malloc(sizeof(char)*LENGTH_MAX);

  printf("Enter your move:");
  int c = fscanf(stdin, "%s\n", move);
  if(c != 1) {
    fprintf(stderr, "Initialier file country.txt corrompt\n");
    exit(1);
  }

  return move;
}

int* ask_from_to(void){
  int* res = (int*) malloc(sizeof(int)*2);

  printf("Enter id country_from: ");
  int c = fscanf(stdin, "%d", &res[0]);
  if(c != 1) {
    fprintf(stderr, "Initialier file country.txt corrompt\n");
    exit(1);
  }

  printf("Enter id country_to: ");
  c = fscanf(stdin, "%d", &res[1]);
  if(c != 1) {
    fprintf(stderr, "Initialier file country.txt corrompt\n");
    exit(1);
  }

  return res;
}

int ask_number(void){
  int nb;

  printf("Enter the number of troop(s): ");
  int c = fscanf(stdin, "%d", &nb);
  if(c != 1) {
    fprintf(stderr, "Initialier file country.txt corrompt\n");
    exit(1);
  }

  return nb;
}
