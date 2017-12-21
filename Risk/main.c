#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#include "risk_model.h"
#include "risk_view_initialize.h"

int main(void) {
    printf("Begin...\n");
    state_t *state = malloc(sizeof(state_t));
    if (state == NULL) {
        fprintf(stderr, "Can't create state_t");
        exit(1);
    }
    initiliaze_state(state);

    country_t** countries=NULL;
    uint nb_countries=0;

    continent_t** continents=NULL;
    uint nb_continents=0;

    user_t** users;
    uint nb_players;
    
    while (!state->end_game) {
        if (state->initialize) {
            nb_countries  = get_nb_countries();
            countries = malloc(nb_countries * sizeof(country_t*));
            if(countries == NULL) {
                fprintf(stderr, "Cannot create all countries\n");
                exit(1);
            }

            nb_continents = get_nb_continents();
            continents = malloc(nb_continents * sizeof(continent_t*));
            if(continents == NULL) {
                fprintf(stderr, "Cannot create all continents\n");
                exit(1);
            }

            create_countries(countries);
            create_continents(continents, countries);

            nb_players = ask_nb_players();
            users = ask_users(nb_players);

            state->initialize= false;
            state->set_board = true;
            //state->end_game  = true;
        } else if (state->set_board) {
            while (!all_possessed(countries, nb_countries)) {
                print_grid(continents, nb_continents, countries);
                choose_country(countries, nb_countries, users, nb_players);
            }
            state->end_game = true;
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
