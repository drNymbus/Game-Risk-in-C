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
    initilize_state(state);

    country_t** countries=NULL;
    uint nb_countries=0;

    continent_t** continents=NULL;
    uint nb_continents=0;

    //user_t* users;
    //uint nb_players;
    
    while (!state->end_game) {
        if (state->initialize) {
            printf("Initialize...\n");
            nb_countries  = get_nb_countries();
            nb_continents = get_nb_continents();

            countries = create_countries();
            continents= create_continents(countries);

            state->initialize= false;
            state->set_board = true;
        } else if (state->set_board) {
            printf("Print grid...\n");
            print_grid(continents, nb_continents, countries);
            state->end_game=true;
        }
    }


    free_all_continents(continents, nb_continents);
    free_all_countries(countries, nb_countries);
    free(continents);
    free(countries);

    return EXIT_SUCCESS;
}
