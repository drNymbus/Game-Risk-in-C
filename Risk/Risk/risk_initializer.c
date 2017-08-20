#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "risk_model.h"

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

//uint find_nb_continents(char* path){}

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

uint ask_nb_players(void){
  uint nb_players;
  printf("Enter the number of players (1 to 5): ");
  scanf("%d", &nb_players);
}

user_t* ask_users(uint nb_players){
  static user_t users[NB_MAX_PLAYERS];
  printf("Enter names : (\\in case\\length max is 30)\n");
  for(uint i=0; i<nb_players; i++){
    printf("%d.", i+1);
    scanf("%s", users[i].name);
  }
  return &users;
}

uint ask_troops(void){
  uint nb_troops;
  printf("Enter the number of troops: ");
  scanf("%d", &nb_troops);
}
