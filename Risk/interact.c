#include <stdio.h>
#include <stdlib.h>

#include "risk_view_initialize.h"

bool yes_no(void) {
    char valid = getc(stdin);
    do {
        while (valid != '\n') {valid = getc(stdin);}
        fprintf(stdout, "Are you sure ? (y/n) ");
        fscanf(stdin, "%c", &valid);
    } while (valid != 'y' && valid != 'n');

    if (valid == 'y') return true;
    return false;
}

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

action ask_move(void) {
    char move[LENGTH_MAX];
    char empty=getc(stdin);
    action user_move = STOP;

    do {
        while (empty != '\n') { empty = getc(stdin); }
        fprintf(stdout, "Enter your move : ");

        fscanf(stdin, "%s", move);
        lower_case(move);
        if (compare_string(move, "attack")) {user_move=ATTACK;}
        if (compare_string(move, "deploy")) {user_move=DEPLOY;}
        if (compare_string(move, "move"))   {user_move=MOVE;}
        if (compare_string(move, "boost"))  {user_move=BOOST;}
        if (compare_string(move, "end"))    {user_move=END;}

    } while (user_move == STOP);

    return user_move;
}

int ask_id_country(char* msg, uint nb_countries) {
    char empty=getc(stdin);
    int id=-1;

    do {
        while (empty != '\n') empty=getc(stdin);
        fprintf(stdout, "%s", msg);
        fscanf(stdin, "%d", &id);
    } while (id < 0 && id > nb_countries);

    return id;
}

void choose_country(country_t** countries, uint nb_countries, user_t** users, uint nb_users) {
    char empty = getc(stdin);
    char convert[LENGTH_MAX];
    char* receive;
    uint id=-1;
    int c=0;

    for (uint i=0; i < nb_users; i++) {

        do {
            while (empty != '\n') {empty = getc(stdin);}
            fprintf(stdout, "%s, you need choose a country (enter the id) : ", users[i]->name);
            c = fscanf(stdin, "%s", convert);
            id = strtoul(convert, &receive, 10);

            if (c != 1) {
                fprintf(stderr, "Invalid command \n");
            } else if (id > nb_countries || id == -1) {
                fprintf(stderr, "Invalid ID entered \n");
            }

        } while (c != 1 || id > nb_countries);

        if (countries[id]->owner) {i--;fprintf(stderr,"This country is already taken\n");}
        else {countries[id]->owner = users[i];}
    }
}

void lower_case(char* str) {
    uint i=0;
    while (str[i] != '\0') {
        if (str[i] > 64 && str[i] < 91) {str[i] += 'A'-'a';}
        i++;
    }
}

bool compare_string(char* s1, char* s2) {
    if (length_string(s1) != length_string(s2)) return false;

    uint i=0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return false;
        i++;
    }
    return true;
}