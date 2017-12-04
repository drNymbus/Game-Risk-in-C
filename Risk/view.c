#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "risk_view_initialize.h"

void print_empty_country(void) {
    for (uint i=0; i < LENGTH_MAX; i++) {
        printf(" ");
    }
    printf("|");
}

void print_country(country_t* country) {
    uint space = LENGTH_MAX - strlen(country->name);
    for (uint i=0; i < space/2; i++) {
        printf(" ");
    }
    printf("%s", country->name);
    for (uint i=0; i < space/2; i++) {
        printf(" ");
    }
    printf("|");
}

void print_continent(continent_t* continent) {
    uint space = LENGTH_MAX - strlen(continent->name);
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
            if (continents[j]->nb_country > j) print_country(countries[continents[j]->countries[i]]);
        }
        printf("\n");
    }
}