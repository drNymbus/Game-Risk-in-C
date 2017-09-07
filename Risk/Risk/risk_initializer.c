#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "risk_model.h"
#include "risk_view_intialize.h"

uint find_nb_countries(char* path){
  FILE* countries = fopen(path, "r");
  uint nb_total_countries;
  fscanf(countries, "%d", &nb_total_countries);
  return nb_total_countries;
}

country_t* create_countries(char* path){
  FILE* countries = fopen(path, "r");
  uint nb_total_countries;
  fscanf(countries, "%d\n", &nb_total_countries);
  static country_t countries[nb_total_countries];
  for(uint i=0; i<nb_total_countries; i++){
    fscanf(countries,"%s",countries[i].name);
    fscanf(countries,"%d %d",&countries[i].nb_connections,&countries[i].max_troop);
    position_t position;
    fscanf(countrie,"%d %d",&position.pos_x,&position,position.pos_y);
    countries[i].position = &position;
    for(uint j=0; j<&countries.nb_connections-1; j++){
      fscanf(countries,"%s",NULL);
    }
    fscanf(countries,"%s\n",NULL);
  }
  fclose(countries);
  return &countries;
}

void set_connections(country_t* countries[], uint nb_countries, char* path){
  FILE* connections = fopen(path, "r");
  for(uint i=0; i<nb_countries; i++){
    fscanf(connections, "%s %d %d", NULL,NULL,NULL);
    fscanf(connections,"%d %d", NULL,NULL);
    for(uint j=0; j<(*countries).nb_connections; j++){
      char name_conn[LENGTH_MAX];
      fscanf(connections, "%s", name_conn);
      for(uint index_conn; index_conn<nb_countries; index_conn++){
        if(compare_char(countries[index_conn].name, name_conn){
          countries[i].connections[j] = countries[index_conn];
        }
      }
    }
    fscanf(connections, "\n");
  }
}

uint find_nb_continents(char* path){
  FILE* continents = fopen(path, "r");
  uint nb_continents;
  fscanf(continents, "%d\n", nb_continents);
  return nb_continents;
}

continent_t* create_continents(country_t* countries[], uint nb_countries, char* path){
  FILE* continents = fopen(path, "r");
  uint nb_continents;
  fscanf(continents, "%d\n", nb_continents);
  static continent_t* continent[nb_continents];
  for(uint i=0; i<nb_continents; i++){
    fscanf(contients, "%s %d\n", continent[i].name, &continent[i].nb_country);
    for(uint j=0; j<continent[i].nb_country; j++){
      char name_country;
      fscanf(continents, "%s\n", name_country);
      for(uint index=0; index<nb_countries; index++){
        if(compare_char(countries[index], name_country)){
          countries[index].continent = continent[i];
        }
      }
    }
  }
  return &continent;
}

void initialize_countries(country_t* countries[], uint nb_countries){
  for(uint i=0; i<nb_countries; i++){
    (*countries[i]).owner = NULL;
    (*countries[i]).current_troop = 0;
    (*countries[i]).capital = false;
  }
}

void set_bots(user_t* users[NB_MAX_PLAYERS], uint nb_players){
  for(uint i=0; i<nb_players; i++){
    users[NB_MAX_PLAYERS-i].name = "BOT";
  }
}

void set_colors_to_users(user_t* users[NB_MAX_PLAYERS]){
  char* colors[NB_MAX_PLAYERS] = {KRED,KGRN,KYEL,KMAG,KCYN};
  for(uint i=0; i<NB_MAX_PLAYERS; i++){
    (*users[i]).color = colors[i];
  }
}

void set_owner(country_t* country, user_t* owner){
  (*country).owner = (*owner).name;
  (*owner).nb_country++;
  (*owner).countries[(*owner).nb_country-1] = country;
}

void set_country_to_owner(country_t* countries[], uint nb_countries, user_t* users[NB_MAX_PLAYERS]){
  for(uint i=0; i<NB_MAX_PLAYERS; i++){
    for(uint j=0; j<nb_countries/NB_MAX_PLAYERS;bool country_taken=false){
      srand(time(NULL));
      uint index_country = rand()%nb_countries;
      if((*countries[index_country]).owner != NULL){
        set_owner(countries[index_country], users[i]);
        i++
      }
    }
}

uint ask_nb_players(void){
  uint nb_players = NB_MAX_PLAYERS+1;
  while(nb_players > NB_MAX_PLAYERS){
    printf("Enter the number of players (1 to 5): ");
    scanf("%d", &nb_players);
  }
}

user_t* ask_users(uint nb_players){
  static user_t users[NB_MAX_PLAYERS];
  printf("Enter names : (\\in case\\length max is 30)\n");
  for(uint i=0; i<nb_players; i++){
    printf("%d.", i+1);
    scanf("%s\n", users[i].name);
  }
  return &users;
}

int ask_troops(void){
  int nb_troops;
  scanf("Enter the nb of troops you want to move: %d", &nb_troops);
  return nb_troops;
}

char* ask_instructions(void){
  char index[1];
  char instruction[7];
  char nb[3];
  scanf("%s %s %s", index, instruction, nb);
  static char* instructions[3];
  instructions[0] = index;
  instructions[1] = instruction;
  instructions[2] = nb;
  return instructions;
}

int* ask_move(void){
  printf("Enter \"index1 nb_troops index2\"\n");
  uint i1, nb_troops, i2;
  scanf("%d %d %d\n", &i1, &nb_troops, &i2);
  static int* result[3] = {&i1, &nb_troops, &i2};
  return result;
}

int* ask_attack(void){
  printf("Enter \"index1 index2\"\n");
  uint i1, i2;
  scanf("%d %d\n", &i1, &i2);
  static int* result[2] = {&i1, &i2};
  return result;
}
