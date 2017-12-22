#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <time.h>

#include "risk_view_initialize.h"

uint get_nb_countries(char* path) {
    FILE* f_countries = fopen(path, "r");
    if (f_countries == NULL) {
        perror("Error");
        exit(1);
    }
    uint nb_countries;

    int c = fscanf(f_countries, "%u", &nb_countries);
    if(c != 1) {
        fprintf(stderr, "Initializer file country.txt corrupt (%u)\n", nb_countries);
        exit(1);
    }

    fclose(f_countries);
    return nb_countries;
}

void create_countries(country_t** countries, char* path) {

    uint nb_total_countries;
    FILE* f_countries = fopen(path, "r");

    int c = fscanf(f_countries, "%u", &nb_total_countries);
    if(c != 1) {
        fprintf(stderr, "Initializer file country.txt nb_countries(%u)\n", nb_total_countries);
        fprintf(stderr, "...line(0)\n");
        exit(1);
    }

    for(uint id=0; id < nb_total_countries; id++){
        int line=id+2;

        country_t* country = country_alloc();

        char name[LENGTH_MAX];
        //set id and name  to country
        c = fscanf(f_countries,"%s", name);
        if(c != 1) {
            fprintf(stderr, "Initializer file country.txt corrupt id name (%s)", name);
            fprintf(stderr, "...line(%d)\n", line);
            exit(1);
        }
        country->id  = id;
        //printf("%s \n", name);
        country->name= name;

        //set position to country
        uint x, y;
        c = fscanf(f_countries, "%d %d", &x, &y);
        if(c != 2) {
            fprintf(stderr, "Initializer file country.txt corrupt pos(%d,%d)\n", x, y);
            fprintf(stderr, "...line(%d)\n", line);
            exit(1);
        }
        position_t* position = create_position(x, y);
        country->position = position;

        //set number of connections
        uint nb_connections;
        c = fscanf(f_countries, "%d", &nb_connections);
        if(c != 1) {
            fprintf(stderr, "Initializer file country.txt corrupt nb_conn(%d)", nb_connections);
            fprintf(stderr, "...line(%d)\n", line);
            exit(1);
        }

        //set connections from id
        for(uint j=0; j < nb_connections; j++){
            int id_conn;
            c = fscanf(f_countries,"%d", &id_conn);
            if(c != 1) {
                fprintf(stderr, "Initializer file country.txt corrupt id_conn(%d)", id_conn);
                fprintf(stderr, "...line(%d)\n", line);
                exit(1);
            }

            country->nb_connections++;
            country->connections[j] = id_conn;
        }

        countries[id] = country;
        //printf("%s \n", countries[id]->name);
    }
    //printf("Supposed to be GRANDE-BRETAGNE: %s \n", countries[0]->name);
/*
    for (uint i=0; i < nb_total_countries; i++) {
        printf("%d.%s (%u) \n", i, countries[i]->name, countries[i]->nb_connections);
    }
*/
    fclose(f_countries);
    //return countries;
}



uint get_nb_continents(char* path) {
    FILE* continents = fopen(path, "r");
    uint nb_continents;

    int c = fscanf(continents, "%d", &nb_continents);
    if(c != 1) {
        fprintf(stderr, "Initializer file continent.txt corrupt\n");
        exit(1);
    }

    fclose(continents);
    return nb_continents;
}

void create_continents(continent_t** continents, country_t** countries, char* path) {

    FILE* f_continents = fopen(path, "r");
    uint nb_continents;
    int c = fscanf(f_continents, "%d", &nb_continents);
    if(c != 1) {
        fprintf(stderr, "Initializer file continent.txt corrupt\n");
        exit(1);
    }

    for(uint i=0; i < nb_continents; i++){
        continent_t* continent = continent_alloc();

        char name[LENGTH_MAX];
        uint nb_country;

        c = fscanf(f_continents, "%s %d", name, &nb_country);
        if(c != 2) {
            fprintf(stderr, "Initializer file continent.txt corrupt\n");
            exit(1);
        }
        continent->id = i;
        continent->name = name;

        for(uint j=0; j < nb_country; j++){
            int id;
            c = fscanf(f_continents, "%d", &id);
            if(c != 1) {
                fprintf(stderr, "Initializer file continent.txt corrupt\n");
                exit(1);
            }
            continent->nb_country++;
            continent->countries[j] = id;

            countries[id]->continent = continent->id;
        }

        continents[i] = continent;
        //printf("%s \n", continents[i]->name);
    }
    //printf("Supposed to be EUROPE : %s \n", continents[0]->name);
/*
    for (uint i=0; i < nb_continents; i++) {
        printf("%d.%s \n", i, continents[i]->name);
        for (uint j=0; j < continents[i]->nb_country; j++) {
            int id = continents[i]->countries[j];
            printf("\t%d.%s \n", j, countries[id]->name);
        }
    }
*/
    fclose(f_continents);
    //return continents;
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

void free_all_users(user_t** users, uint nb_users) {
    for (uint i=0; i < nb_users; i++) {
        free_user(users[i]);
    }
}
