#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "risk_view_initialize.h"

/*=======================INIITIALIZE========================*/

uint get_nb_countries() {
  FILE* f_countries = fopen("./initializer/country.txt", "r");
  uint nb_countries;

  fscanf(f_countries, "%u\n", &nb_countries);

  fclose(f_countries);
  return nb_countries;
}

country_t* create_countries() {

  uint nb_total_countries = get_nb_countries();
  country_t* countries[nb_total_countries];

  FILE* f_countries = fopen("./initializer/country.txt", "r");
  fscanf(f_countries, "\n");

  for(uint i=0; i<nb_total_countries; i++){
    fscanf(f_countries,"%d %s", &countries[i]->id, countries[i]->name);

    uint x, y;
    fscanf(f_countries, "%d %d", &x, &y);
    position_t* position = create_position(x, y);
    countries[i]->position = &position;

    fscanf(f_countries, "%d", &countries[i]->nb_connections);

    for(uint j=0; j < countries[i]->nb_connections; j++){
      fscanf(f_countries,"%d", countries[i]->connections[j]);
    }
    fscanf(f_countries,"\n");
  }

  fclose(f_countries);
  return countries;
}

uint find_nb_continents(void){
  FILE* continents = fopen("./initializer/continent.txt", "r");
  uint nb_continents;
  fscanf(continents, "%d\n", &nb_continents);
  return nb_continents;
}

continent_t* create_continents(country_t* countries[], uint nb_countries, char* path){
  FILE* continents = fopen(path, "r");
  uint nb_continents;
  fscanf(continents, "%d\n", &nb_continents);
  continent_t* continent[nb_continents] = malloc(sizeof(nb_continents*continent_t));
  for(uint i=0; i<nb_continents; i++){
    fscanf(continents, "%s %d\n", (*continent[i]).name, (*continent[i]).nb_country);
    for(uint j=0; j<(*continent[i]).nb_country; j++){
      char name_country[LENGTH_MAX];
      fscanf(continents, "%s\n", name_country);
      for(uint index=0; index<nb_countries; index++){
        if(compare_char((*countries[index]).name, name_country)){
          (*countries[index]).continent = continent[i];
        }
      }
    }
  }
  return continent;
}

/*===================USER INTERACTION=====================*/

uint ask_nb_players(void){
  uint nb_players = NB_MAX_PLAYERS+1;
  while(nb_players > NB_MAX_PLAYERS){
    printf("Enter the number of players (1 to 5): ");
    scanf("%d", &nb_players);
  }
  return nb_players;
}

user_t* ask_users(uint nb_players){
  static user_t users[NB_MAX_PLAYERS];
  printf("Enter names : (\\in case\\length max is 30)\n");
  for(uint i=0; i<nb_players; i++){
    printf("%d.", i+1);
    scanf("%s\n", users[i].name);
  }
  return users;
}

int ask_troops(void){
  int nb_troops;
  scanf("Enter the nb of troops you want to move: %d", &nb_troops);
  return nb_troops;
}

char* ask_instructions(void){
  static char index[2];
  static char instruction[7];
  static char nb[3];
  scanf("%s %s %s", index, instruction, nb);
  static char* instructions[3] = {index, instruction, nb};
  return &instructions;
}

int* ask_move(void){
  printf("Enter \"index1 nb_troops index2\"\n");
  uint i1, nb_troops, i2;
  scanf("%d %d %d\n", &i1, &nb_troops, &i2);
  int result[3] = {i1, nb_troops, i2};
  return result;
}

int* ask_attack(void){
  printf("Enter \"index1 index2\"\n");
  uint i1, i2;
  scanf("%d %d\n", &i1, &i2);
  int result[2] = {i1, i2};
  return result;
}
