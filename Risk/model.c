#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "risk_model.h"

position_t* create_position(uint x, uint y) {
  position_t* pos = (position_t*) malloc(sizeof(position_t));
  if(pos == NULL) {
    fprintf(stderr, "Cannot create position\n");
    fprintf(stderr, "Cannot allocate memory\n");
    exit(1);
  }
  if(y > MAP_Y) {
    fprintf(stderr, "Invalid parameter y(%d) for position\n", y);
    exit(1);
  } else if(x > MAP_X) {
    fprintf(stderr, "Invalid parameter x(%d) for position\n", x);
    exit(1);
  }

  pos->pos_x = x;
  pos->pos_y = y;

  return pos;
}

/*====================COUNTRY=====================*/

country_t* country_alloc() {
  int* connections = (int*) malloc(NB_CONNECTIONS_MAX * sizeof(int));
  if(connections == NULL) {
    fprintf(stderr, "Cannot create connection array\n");
    fprintf(stderr, "Cannot allocate memory\n");
    exit(1);
  }

  country_t* country = (country_t*) malloc(sizeof(country_t*));
  if(country == NULL) {
    fprintf(stderr, "Cannot create country\n");
    fprintf(stderr, "Cannot allocate memory\n");
    exit(1);
  }

  country->nb_connections = 0;
  country->current_troop = 0;
  country->capital = false;
  country->continent = NULL;
  country->position = NULL;
  country->connections = connections;

  return country;
}

void set_country_name(country_t* country, char* name) {
  country->name = name;
}

void set_country_owner(country_t* country, user_t* user) {
  country->owner = user;
}
void connect_countries(country_t* country1, country_t* country2) {
  country1->nb_connections += 1;
  country1->connections[country1->nb_connections - 1] = country2->id;

  country2->nb_connections += 1;
  country2->connections[country2->nb_connections - 1] = country1->id;
}

void add_troops(country_t* country, int nb_troops) {
  if(nb_troops < 0) {
    fprintf(stderr, "Invalid nb_troops\n");
    exit(1);
  }

  country->current_troop += nb_troops;
  if(country->current_troop < 0) {
    fprintf(stderr, "Too many troops in country\n");
    exit(1);
  }
}

void loss_troops(country_t* country, int nb_troops) {
  if(nb_troops < 0) {
    fprintf(stderr, "Invalid nb_troops\n");
    exit(1);
  }

  country->current_troop -= nb_troops;
  if(country->current_troop < 0) {
    fprintf(stderr, "Too many troops in country\n");
    exit(1);
  }
}

void set_capital(country_t* country) {
  if(country->capital) {
    fprintf(stderr, "Country already a capital\n");
    return;
  }
  country->capital = true;
}

void set_position(country_t* country, position_t* position) {
  country->position = position;
}

void free_country(country_t* country) {
  free(country->connections);
  country->connections = NULL;

  free(country);
  country = NULL;
}

/*============CONTINENT====================*/

continent_t* continent_alloc() {
  country_t* countries = (country_t*) malloc(NB_CONTINENT_MAX * sizeof(country_t));
  if(countries == NULL) {
    fprintf(stderr, "Cannot create countries array\n");
    fprintf(stderr, "Cannot allocate memory\n");
    exit(1);
  }

  continent_t* continent = (continent_t*) malloc(sizeof(continent_t));
  if(continent == NULL) {
    fprintf(stderr, "Cannot create continent\n");
    fprintf(stderr, "Cannot allocate memory\n");
    exit(1);
  }

  continent->countries = countries;
  continent->bonus_troop = 0;
  continent->nb_country = 0;

  return continent;
}

void set_continent_name(continent_t* continent, char* name) {
  continent->name = name;
}

void set_owner_continent(continent_t* continent, user_t* user) {
  continent->owner = user;
}

void country_to_continent(continent_t* continent, country_t* country) {
  continent->nb_country += 1;
  continent->countries[continent->nb_country - 1] = *country;

  country->continent = continent;
}

void set_bonus_troop(continent_t* continent, int bonus_troop) {
  continent->bonus_troop = bonus_troop;
}

void free_continent(continent_t* continent) {
  free(continent->countries);
  continent->countries = NULL;
  free(continent);
  continent = NULL;
}

/*=============USER=============*/

user_t* user_alloc() {
  country_t* countries = (country_t*) malloc(NB_COUNTRY_MAX * sizeof(country_t));
  continent_t* continents = (continent_t*) malloc(CONTINENT_OWNED_MAX * sizeof(continent_t));
  if(countries == NULL || continents == NULL) {
    fprintf(stderr, "Cannot create countries and/or continents array\n");
    fprintf(stderr, "Cannot allocate memory\n");
    exit(1);
  }
  user_t* user = (user_t*) malloc(sizeof(user_t));

  user->countries = countries;
  user->continents = continents;

  user->nb_country = 0;
  user->nb_continent = 0;
  user->nb_stars = 0;
  user->boost = false;

  return user;
}

void set_user_name(user_t* user, char* name) {
  user->name = name;
}

void add_country(user_t* user, country_t* country) {
  user->nb_country += 1;
  user->countries[user->nb_country - 1] = *country;

  country->owner = user;
}

void loss_country(user_t* user, country_t* country) {
  for(uint i=0; i < user->nb_country; i++) {

    if(user->countries[i].name == country->name) {
      for(uint j=i; j < user->nb_country; j++){
        user->countries[j] = user->countries[j+1];
      }
      user->nb_country -= 1;
    }

  }
}

void add_stars(user_t* user, int nb_stars) {//put negative nb_stars to get loss_stars function
  user->nb_stars += nb_stars;
}

uint calculation_gain(user_t* user) {
  uint gain = 0;
  for(uint i=0; i < user->nb_continent; i++) {
    gain += user->continents[i].bonus_troop;
  }
  gain += user->nb_country / 3;
  return gain;
}

void set_gain(user_t* user, uint gain) {
  user->gain = gain;
}

void set_color_user(user_t* user, char* color) {
  user->color = color;
}

void activate_boost(user_t* user, bool boost) {
  if(user->boost == boost) {
    fprintf(stderr, "Boost already %s\n", boost ? "true" : "fasle");
  }
  user->boost = boost;
}

void free_user(user_t* user) {
  free(user->countries);
  free(user->continents);
  free(user);
  user = NULL;
}
