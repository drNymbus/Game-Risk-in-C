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
    system("cls"); //MS-DOS
    /*system("clear"); //UNIX*/
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
