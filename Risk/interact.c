#include <stdio.h>
#include <stdlib.h>

#include "risk_view_initialize.h"

uint ask_nb_players(void) {
    uint nb=-1;
    int c=-1;

    fprintf(stdout, "Enter the number of players (/!\\ up to 5 /!\\) : ");

    while (c != 1 && nb < 0 && nb > NB_MAX_PLAYERS) {
        c = fscanf(stdin, "%u", &nb);
        if(c != 1) {
            fprintf(stderr, "Bad command entered\n");
        } else if (nb < 0 || nb > NB_MAX_PLAYERS) {
            fprintf(stderr, "Enter a valid number\n");
        }
    }

    return nb;
}

user_t** ask_users(uint nb_players) {
    user_t** users = malloc(sizeof(user_t*) * nb_players);
    if (users == NULL) {
        fprintf(stderr, "Cannot create users\n");
        exit(1);
    }
    char* color[5] = {KRED, KGRN, KYEL, KMAG, KCYN};

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