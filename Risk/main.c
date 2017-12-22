#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "risk_view_initialize.h"

int main(void) {
    printf("Begin...\n");

    char* path_country  = "../../Risk/initializer/country.txt";
    char* path_continent= "../../Risk/initializer/continent.txt";

    state_t *state = malloc(sizeof(state_t));
    if (state == NULL) {
        fprintf(stderr, "Can't create state_t");
        exit(1);
    }
    initiliaze_state(state);

    user_t** users;
    uint nb_players;

    uint nb_countries  = get_nb_countries(path_country);
    country_t** countries = malloc(nb_countries * sizeof(country_t*));
    if(countries == NULL) {
        fprintf(stderr, "Cannot create all countries\n");
        exit(1);
    }
    create_countries(countries, path_country);

    uint nb_continents = get_nb_continents(path_continent);
    continent_t** continents = malloc(nb_continents * sizeof(continent_t*));
    if(continents == NULL) {
        fprintf(stderr, "Cannot create all continents\n");
        exit(1);
    }
    create_continents(continents, countries, path_continent);

    char* command = malloc(sizeof(char) * LENGTH_MAX);
    if (command == NULL) {
        fprintf(stderr, "Can't create command string\n");
        exit(1);
    }

    while (!state->end_game) {
        if (state->initialize) {

            nb_players = ask_nb_players();
            users = ask_users(nb_players);

            if (yes_no()) {
                state->initialize = false;
                state->set_board = true;
            } else {
                free_all_users(users, nb_players);
                free(users);
                nb_players=-1;
            }//state->end_game  = true;
        } else if (state->set_board) {
            /*while (!all_possessed(countries, nb_countries)) {
                print_grid(continents, nb_continents, countries);
                choose_country(countries, nb_countries, users, nb_players);
            }*/

            printf("\n Fake set_board \n");
            if (yes_no()) {
                state->who_turn = 0;
                state->set_board= false;
                state->set_turn = true;
            } else {
                for (uint i=0; i < nb_countries; i++) {
                    countries[i]->owner = NULL;
                }
            }
        } else if (state->set_turn) {
            user_t* user_turn = users[state->who_turn];
            printf("Turn ==> %s \n", user_turn->name);
            user_turn->gain += calculation_gain(user_turn, continents);

            do {
                ask_move(command);
                if (command == "deploy") {

                }
            }while (command != "Attack");

            if (yes_no()) {
                state->set_turn= false;
                state->turn    = true;
            }
        } else if (state->turn) {
            if (yes_no()) {
                state->turn    = true;
                state->end_turn= false;
            }
        } else if (state->end_turn) {
            next_turn(state, nb_players);
        }
    }

    printf("Freeing...\n");
    free_all_users(users, nb_players);
    free(users);

    free_all_continents(continents, nb_continents);
    free(continents);

    free_all_countries(countries, nb_countries);
    free(countries);

    printf("Done...\n");
    return EXIT_SUCCESS;
}
