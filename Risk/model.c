#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "risk_model.h"
//#include "risk_view_initialize.h"

void initiliaze_state(state_t* state) {
    state->who_turn  = -1;
    state->end_game  = false;
    state->initialize= true;
    state->set_board = false;
    state->set_turn  = false;
    state->turn      = false;
    state->end_turn  = false;
}

void next_turn(state_t* state, uint nb_players) {
    state->who_turn++;
    if (state->who_turn == nb_players) {
        state->who_turn = 0;
    }
}

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

    char* name = malloc(sizeof(char) * LENGTH_MAX);
    if(name == NULL) {
        fprintf(stderr, "Cannot allocate memory for name\n");
        exit(1);
    }

    country_t* country = (country_t*) malloc(sizeof(country_t));
    if(country == NULL) {
        fprintf(stderr, "Cannot create country\n");
        fprintf(stderr, "Cannot allocate memory\n");
        exit(1);
    }

    country->name = name;
    country->connections = connections;
    country->nb_connections = 0;

    country->current_troop = 0;
    country->continent = -1;

    country->capital = false;
    country->position = NULL;
    country->owner = NULL;

    return country;
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
        fprintf(stderr, "Too many troops in country (limit id (2**64)-1, theorically)\n");
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
        fprintf(stderr, "Too many troops in country (limit id (2**64)-1, theorically)\n");
        exit(1);
    }
}

void free_country(country_t* country) {
    //printf("Freeing country : %s", country->name);
//    free(country->name);
    free(country->connections);

    free(country);
}

bool all_possessed(country_t** countries, uint nb_countries) {
    for (uint i=0; i < nb_countries; i++) {
        if (countries[i]->owner == NULL) {return false;}
    }
    return true;
}

/*================================CONTINENT===================================*/

continent_t* continent_alloc(void) {
    int* countries = (int*) malloc(NB_CONTINENT_MAX * sizeof(int));
    if(countries == NULL) {
        fprintf(stderr, "Cannot create countries array\n");
        exit(1);
    }

    char* name = malloc(sizeof(char) * LENGTH_MAX);
    if (name == NULL) {
        fprintf(stderr, "Can't create name coutry \n");
        exit(1);
    }

    continent_t* continent = (continent_t*) malloc(sizeof(continent_t));
    if(continent == NULL) {
        fprintf(stderr, "Cannot create continent\n");
        exit(1);
    }

    continent->name = name;
    continent->countries = countries;
    continent->nb_country=0;

    continent->bonus_troop=0;
    continent->owner=NULL;

    return continent;
}

void free_continent(continent_t* continent) {
    free(continent->name);
    free(continent->countries);

    free(continent);
}

/*===========================================USER=========================================*/

user_t* user_alloc(void) {
    int* countries = (int*) malloc(NB_COUNTRY_MAX * sizeof(int));
    int* continents = (int*) malloc(CONTINENT_OWNED_MAX * sizeof(int));
    if(countries == NULL || continents == NULL) {
        fprintf(stderr, "Cannot create countries and/or continents array\n");
        fprintf(stderr, "Cannot allocate memory\n");
        exit(1);
    }

    user_t* user = (user_t*) malloc(sizeof(user_t));
    if(user == NULL) {
        fprintf(stderr, "Cannot allocate memory\n");
        exit(1);
    }

    user->countries = countries;
    user->continents = continents;

    user->nb_country=0;
    user->nb_continent=0;
    user->nb_stars=0;
    user->gain=0;

    user->color=NULL;
    user->name =NULL;

    return user;
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

uint calculation_gain(user_t* user, continent_t** continents) {
    uint gain = user->gain;
    for(uint i=0; i < user->nb_continent; i++) {
        gain += continents[user->continents[i]]->bonus_troop;
    }
    gain += user->nb_country / 3;
    return gain;
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
    free(user->name);
    free(user->countries);
    free(user->continents);
    free(user);
}
