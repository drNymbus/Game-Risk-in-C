#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <time.h>

#include "risk_view_initialize.h"

/*=======================INIITIALIZE========================*/

uint get_nb_countries(void) {
    FILE* f_countries = fopen("./initializer/country.txt", "r");
    uint nb_countries;

    int c = fscanf(f_countries, "%u", &nb_countries);
    if(c != 1) {
        fprintf(stderr, "Initialier file country.txt corrompt (%u)\n", nb_countries);
        exit(1);
    }


    fclose(f_countries);
    return nb_countries;
}

country_t** create_countries(void) {

    uint nb_total_countries=0;
    FILE* f_countries = fopen("./initializer/country.txt", "r");

    int c = fscanf(f_countries, "%u", &nb_total_countries);
    if(c != 1) {
        fprintf(stderr, "Initializer file country.txt nb_countries(%u)\n", nb_total_countries);
        fprintf(stderr, "...line(0)\n");
        exit(1);
    }

    country_t** countries = malloc(nb_total_countries * sizeof(country_t*));
    if(countries == NULL) {
        fprintf(stderr, "Cannot create all countries\n");
        fprintf(stderr, "Cannot allocate memory\n");
        exit(1);
    }

    for(uint id=0; id < nb_total_countries; id++){
        int line=id+2;

        country_t* country = country_alloc();

        char* name = malloc(sizeof(char)*LENGTH_MAX);
        if(name == NULL) {
            fprintf(stderr, "Cannot allocate memory for name\n");
            exit(1);
        }

        //set id and name  to country
        c = fscanf(f_countries,"%s", name);
        if(c != 1) {
            fprintf(stderr, "Initialier file country.txt corrompt id name (%s)", name);
            fprintf(stderr, "...line(%d)\n", line);
            exit(1);
        }
        country->id  = id;
        country->name= name;

        //set position to country
        uint x, y;
        c = fscanf(f_countries, "%d %d", &x, &y);
        if(c != 2) {
            fprintf(stderr, "Initialier file country.txt corrompt pos(%d,%d)\n", x, y);
            fprintf(stderr, "...line(%d)\n", line);
            exit(1);
        }
        position_t* position = create_position(x, y);
        country->position = position;

        //set number of connections
        uint nb_connections;
        c = fscanf(f_countries, "%d", &nb_connections);
        if(c != 1) {
            fprintf(stderr, "Initialier file country.txt corrompt nb_conn(%d)", nb_connections);
            fprintf(stderr, "...line(%d)\n", line);
            exit(1);
        }

        //set connections from id
        for(uint j=0; j < nb_connections; j++){
            int id_conn;
            c = fscanf(f_countries,"%d", &id_conn);
            if(c != 1) {
                fprintf(stderr, "Initialier file country.txt corrompt id_conn(%d)", id_conn);
                fprintf(stderr, "...line(%d)\n", line);
                exit(1);
            }

            country->nb_connections++;
            country->connections[j] = id_conn;
        }

        countries[id] = country;
    }

    fclose(f_countries);
    return countries;
}

uint get_nb_continents(void) {
    FILE* continents = fopen("./initializer/continent.txt", "r");
    uint nb_continents;

    int c = fscanf(continents, "%d", &nb_continents);
    if(c != 1) {
        fprintf(stderr, "Initialier file continent.txt corrompt\n");
        exit(1);
    }

    fclose(continents);
    return nb_continents;
}

continent_t** create_continents(country_t** countries) {

    FILE* f_continents = fopen("./initializer/continent.txt", "r");
    uint nb_continents;
    int c = fscanf(f_continents, "%d", &nb_continents);
    if(c != 1) {
        fprintf(stderr, "Initializer file continent.txt corrompt\n");
        exit(1);
    }

    continent_t** continents = malloc(nb_continents * sizeof(continent_t*));
    if(countries == NULL) {
        fprintf(stderr, "Cannot create all countries\n");
        fprintf(stderr, "Cannot allocate memory\n");
        exit(1);
    }

    for(uint i=0; i < nb_continents; i++){
        continent_t* continent = continent_alloc();

        char* name = malloc(sizeof(char) * LENGTH_MAX);
        if(name == NULL) {
            fprintf(stderr, "Cannot allocate memory ");
            fprintf(stderr, "for name continent n°%u \n", i + 1);
            exit(1);
        }
        uint nb_country;

        c = fscanf(f_continents, "%s %d", name, &nb_country);
        if(c != 2) {
            fprintf(stderr, "Initialier file continent.txt corrompt\n");
            exit(1);
        }
        continent->name = name;

        for(uint j=0; j < nb_country; j++){
            int id;
            c = fscanf(f_continents, "%d", &id);
            if(c != 1) {
                fprintf(stderr, "Initialier file continent.txt corrompt\n");
                exit(1);
            }
            continent->nb_country++;
            continent->countries[j] = id;

            countries[id]->continent = continent->id;
        }

        continents[i] = continent;
    }

    fclose(f_continents);
    return continents;
}

void free_all_countries(country_t** countries, uint nb_countries) {
    for(uint i=0; i < nb_countries; i++) {
        free_country(countries[i]);
    }
}

void free_all_continents(continent_t** continents, uint nb_continents) {
    for(uint i=0; i < nb_continents; i++) {
        free_continent(continents[i]);
    }
}
