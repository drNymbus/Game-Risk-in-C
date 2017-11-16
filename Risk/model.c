#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "risk_model.h"
//#include "risk_view_initialize.h"

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

country_t* country_alloc(void) {
    int* connections = (int*) malloc(NB_CONNECTIONS_MAX * sizeof(int));
    if(connections == NULL) {
        fprintf(stderr, "Cannot create connection array\n");
        fprintf(stderr, "Cannot allocate memory\n");
        exit(1);
    }

    country_t* country = (country_t*) malloc(sizeof(country_t));
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

void set_country_id(country_t* country, int id) {
    country->id = id;
}

void set_country_name(country_t* country, char* name) {
    country->name = name;
}

void set_country_owner(country_t* country, user_t* user) {
    country->owner = user;
}

void set_nb_connections(country_t* country, uint nb_connections) {
    country->nb_connections = nb_connections;
}

void connect_countries_id(country_t* country1, int id) {
    country1->nb_connections++;
    country1->connections[country1->nb_connections - 1] = id;
}

void connect_countries(country_t* country1, country_t* country2) {
    int conn = country1->nb_connections++;
    country1->connections[conn] = country2->id;

    conn = country2->nb_connections++;
    country2->connections[conn] = country1->id;
}

void add_troops(country_t* country, int nb_troops) {
    if(nb_troops < 0) {
        fprintf(stderr, "Invalid nb_troops\n");
        exit(1);
    }

    country->current_troop += nb_troops;
    if(country->current_troop < 0) {
        fprintf(stderr, "Too many troops in country (limit id 2**63, theorically)\n");
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
        fprintf(stderr, "Too many troops in country (limit id 2**63, theorically)\n");
        exit(1);
    }
}

void set_continent(country_t* country, continent_t* continent) {
    country->continent = continent;
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



int get_id(country_t* country) {
    return country->id;
}

int* get_connections(country_t* country) {
    return country->connections;
}

/*============CONTINENT====================*/

continent_t* continent_alloc(void) {
    int* countries = (int*) malloc(CONTINENT_OWNED_MAX * sizeof(int));
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

void set_nb_countries(continent_t* continent, uint nb_connections) {
    continent->nb_country = nb_connections;
}

void country_id_to_continent(continent_t* continent, int id) {
    continent->nb_country++;
    continent->countries[continent->nb_country - 1] = id;
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

user_t* user_alloc(void) {
    int* countries = (int*) malloc(NB_COUNTRY_MAX * sizeof(int));
    int* continents = (int*) malloc(CONTINENT_OWNED_MAX * sizeof(int));
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
    user->countries[user->nb_country - 1] = country->id;

    country->owner = user;
}

void loss_country(user_t* user, country_t* country) {
    for(uint i=0; i < user->nb_country; i++) {

        if(user->countries[i] == country->id) {

            for(uint j=i; j < user->nb_country; j++){
                user->countries[j] = user->countries[j+1];
            }
            user->nb_country -= 1;
            return;
        }

    }
    fprintf(stderr, "Error country shouldn't be lost...\n");
    exit(1);
}

void add_stars(user_t* user, int nb_stars) {//put negative nb_stars to get loss_stars function
    user->nb_stars += nb_stars;
}

void add_calculation_gain(user_t* user, continent_t* continents[]) {
    uint gain = user->gain;
    for(uint i=0; i < user->nb_continent; i++) {
        gain += continents[user->continents[i]]->bonus_troop;
    }
    gain += user->nb_country / 3;
    user->gain = gain;
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
    } else if(user->nb_stars < 0 && boost) {
        fprintf(stderr, "Cannot activate boost, not enough stars");
    }
    user->boost = boost;
}

void apply_boost(user_t* user) {
    if(!(user->boost)) {
        fprintf(stderr, "Cannot apply boost");
        user->gain -= user->nb_stars * 2;
    }
    user->gain += user->nb_stars * 2;
}

void free_user(user_t* user) {
    free(user->countries);
    free(user->continents);
    free(user);
    user = NULL;
}
