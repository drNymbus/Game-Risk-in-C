#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "risk_view_initialize.h"

void print_list_country(country_t* countries, uint nb_country) {
    for(uint i=0; i < nb_country; i++){
        printf("%s %d", countries[i].name, countries[i].nb_connections);
        printf(" | cap=%d\n", countries[i].capital);
    }
}

void print_list_continent(continent_t* continents, uint nb_continents) {
    for(uint i=0; i < nb_continents; i++) {
        printf("Continent %s located at %p, ", continents[i].name, &continents[i]);
        printf("%s %d\n", continents[i].name, continents[i].nb_country);
        printf("LIST COUNTRY : ");
        for(uint j=0; j < continents[i].nb_country; j++) {
            printf(" %d ", continents[i].countries[j]);
        }
    }
}
