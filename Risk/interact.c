#include <stdio.h>
#include <stdlib.h>

#include "risk_view_initialize.h"

uint ask_nb_players(void) {
    char convert[LENGTH_MAX];
    char* receive;
    uint nb=0;
    int c=0;

    do {
        fprintf(stdout, "Enter the number of players (/!\\ up to 5 /!\\) : ");
        c = fscanf(stdin, "%s", convert);
        if (c != 1) {
            fprintf(stderr, "Bad command entered\n");
        } else {
            nb = strtoul(convert, &receive, 10);
        }
    } while (c != 1 || nb > NB_MAX_PLAYERS || nb == 0);

    return nb;
}

user_t** ask_users(uint nb_players) {
    user_t** users = malloc(sizeof(user_t*) * nb_players);
    if (users == NULL) {
        fprintf(stderr, "Cannot create users\n");
        exit(1);
    }
    char* color[5] = {"\x1B[31m", "\x1B[32m", "\x1B[33m", "\x1B[35m", "\x1B[36m"};

    if (nb_players <= NB_MAX_PLAYERS) {

        for (uint i=0; i < nb_players; i++) {
            user_t* user = user_alloc();

            char* name = malloc(sizeof(char) * LENGTH_MAX);
            int c=-1;
            fprintf(stdout, "(%d).", i+1);

            while (c != 1) c = fscanf(stdin, "%s", name);
            user->name = name;
            user->color= color[i];

            users[i] = user;
            fprintf(stdout, "\n");
        }

        return users;
    }

    free(users);
    fprintf(stderr, "NB players superior to NB_MAX_PLAYERS \n");
    exit(1);
}

int ask_troops(void) {
    int c=-1;
    uint nb;
    fprintf(stdout, "Enter the number of troops : ");

    while (c != 1) c = fscanf(stdin, "%u", &nb);

    return nb;
}

void choose_country(country_t** countries, uint nb_countries, user_t** users, uint nb_users) {
    uint id=-1;
    int c=0;
    for (uint i=0; i < nb_users; i++) {
        do {
            fprintf(stdout, "%s, you need choose a country (enter the id) : ", users[i]->name);
            c = fscanf(stdin, "%u", &id);
            if (c != 1) {
                fprintf(stderr, "Invalid command \n");
            } else if (id > nb_countries) {
                fprintf(stderr, "Invalid ID entered \n");
            }
        } while (c != 1 || id > nb_countries);
        if (countries[id]->owner) {i--;}
        else {countries[id]->owner = users[i];}
    }
}