#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "risk_view_initialize.h"

uint length_string(char* s) {
    //printf("string is %s \n", s);
    uint i=0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}

void print_empty_country(void) {
    for (uint i=0; i < LENGTH_MAX; i++) {
        printf(" ");
    }
    printf("|");
}

void print_country(country_t* country) {
    uint space = LENGTH_MAX - length_string(country->name);
    for (uint i=0; i < space/2; i++) {
        printf(" ");
    }
    if (country->owner) {printf("%s", country->owner->color);}
    printf("%u.", country->id);
    printf("%s(%d)" KNRM, country->name, country->current_troop);
    for (uint i=0; i < space/2; i++) {
        printf(" ");
    }
    printf("|");
}

void print_continent(continent_t* continent) {
    uint space = LENGTH_MAX - length_string(continent->name);
    for (uint i=0; i < space/2; i++) {
        printf(" ");
    }
    printf("%s", continent->name);
    for (uint i=0; i < space/2; i++) {
        printf(" ");
    }
    printf(" ");
}

void print_grid(continent_t** continents, uint nb_continents, country_t** countries) {
    for (uint i = 0; i < nb_continents; i++) {
        print_continent(continents[i]);
    }
    printf("\n\n");

    for (uint i = 0; i < NB_CONTINENT_MAX; i++) {
        for (uint j = 0; j < nb_continents; j++) {
            uint id = continents[j]->countries[i];
            if (continents[j]->nb_country > i) {print_country(countries[id]);}
            else {print_empty_country();}
        }
        printf("\n");
    }
}

void display_instructions(state_t* state) {
    printf("Commands : ");
    if (state->set_turn) {
        printf("'attack' to launch attack_phase, ");
        printf("'move' to move troops, ");
        printf("'deploy' to deploy troops (from gain), ");
        printf("'boost' to activate boost");
    } else if (state->turn) {
        printf("'attack' to go in attack mode, ");
        printf("'end' to end your turn");
    }
    printf("\n\n");
}

void display_user_info(user_t* user) {
    if (user == NULL) {
        return;
    }

    printf("\n");
    printf("Nb countries possessed : %d |\n", user->nb_country);
    printf("Nb stars possessed : %d     |\n", user->nb_stars);
    printf("Nb troops to deploy : %d    |\n", user->gain);

    if (user->boost) {
        printf("You boost is acive          |\n");
    } else {
        printf("You're boost is not active |\n");
    }
}

void display_rules(void) {
    //printf("");
}