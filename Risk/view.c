#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "risk_view_initialize.h"

void print_list_country(country_t* countries, uint nb_country) {
    for(uint i=0; i < nb_country; i++){
        printf("%s %d", countries[i].name, countries[i].nb_connections);
        printf("\t cap=%d \n", countries[i].capital);
    }
}

void print_list_continent(continent_t* continents, uint nb_continents, user_t* user) {
    for(uint i=0; i < nb_continents; i++) {
        if(user->nb_continent > 0) {
            if(user->continents[i] == continents[i].id) {
                printf("%s", user->color)
                printf("%s(%u countries)", continents[i].name, continents[i].nb_country);
                printf("%s", KNRM);
            }
        } else {
            printf("%s(%u countries)", continents[i].name, continents[i].nb_country);
        }
    }
    printf("\n");
}
