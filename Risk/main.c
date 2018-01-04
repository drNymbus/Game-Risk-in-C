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

    action user_move;

    display_rules();

    while (!state->end_game) {
        if (state->draw) {
            //system("cls"); //MS-DOS
            system("clear"); //UNIX

            display_instructions(state);
            print_grid(continents, nb_continents, countries);
            display_user_info(users[state->who_turn]);

            state->draw = false;
        }

        if (state->initialize) {

            nb_players = ask_nb_players();
            fprintf(stdout, "Enter the names of all players : \n");
            users = ask_users(nb_players);

            if (yes_no()) {
                state->initialize = false;
                state->set_board = true;
                state->draw = true;
            } else {
                free_all_users(users, nb_players);
                free(users);
                nb_players=-1;
            }


        } else if (state->set_board) {
            /*while (!all_possessed(countries, nb_countries)) {
                system("clear");
                print_grid(continents, nb_continents, countries);
                choose_country(countries, nb_countries, users, nb_players);
            }*/

            printf("\n Fake set_board \n");
            if (yes_no()) {
                state->who_turn = 0;
                state->set_board= false;
                state->set_turn = true;
                state->draw = true;
            } else {
                for (uint i=0; i < nb_countries; i++) {
                    countries[i]->owner = NULL;
                }
            }


        } else if (state->set_turn) {
            user_t* user_turn = users[state->who_turn];
            printf("Turn ==> %s \n", user_turn->name);
            user_turn->gain += calculation_gain(user_turn, continents);
            user_turn->boost = false;

            user_move = ask_move();
            if (user_move == DEPLOY) {
                if (user_turn->gain > 0) {
                    int nb_troops = ask_troops();
                    int to = ask_id_country("Where do you want your new troops (country's id): ", nb_countries);

                    state->draw = add_troops(countries[to], nb_troops);
                }
                fprintf(stderr, "You cannot deploy your gain is not sufficient... \n");

            } else if (user_move == MOVE) {
                int from, to;
                from = ask_id_country("Choose the country's id from : ", nb_countries);
                to = ask_id_country("Where do you want the unit (enter the country id) : ", nb_countries);
                int nb_troops = ask_troops();

                if (are_connected(countries, from, to)) {
                    state->draw = loss_troops(countries[from], nb_troops);
                    if (state->draw) state->draw=add_troops(countries[to], nb_troops);
                }

            } else if (user_move == BOOST) {
                if (user_turn->nb_stars > 1  && user_turn->boost) {user_turn->boost = true;state->draw = true;}
                else if (user_turn->boost) {fprintf(stderr, "Boost already active");}
                else {fprintf(stderr, "Not enough stars to apply boost (min. 2)\n");}

            } else if (user_move == ATTACK) {
                fprintf(stdout, "You'll pass in attack mode.");
                if (yes_no()) {
                    state->set_turn = false;
                    state->turn = true;
                    state->draw = true;
                }
            }


        } else if (state->turn) {
            if (yes_no()) {
                state->turn = true;
                state->end_turn = false;
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
