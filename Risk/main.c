#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#include "risk_model.h"
#include "risk_view_initialize.h"

int main(void){

/*  user_t* users = NULL;
  uint nb_players;
*/
    country_t* countries;
    uint nb_countries;

    continent_t* continents;
    uint nb_continents;

    nb_countries = get_nb_countries();
    printf("Number of countries : %d\n", nb_countries);
    countries = create_countries();
    printf("\n\n");

    printf("List of countries:\n");
    print_list_country(countries, nb_countries);
    printf("\n\n");

    nb_continents = get_nb_continents();
    printf("Number of continents: %d\n", nb_continents);
    printf("\n\n");

    continents = create_continents(countries, nb_countries);
    printf("List of continent:\n");
    print_list_continent(continents, nb_continents);
    printf("\n\n");

/*  nb_players = ask_nb_players();
  users[nb_players] = ask_users(nb_players);
*/

    free_all_countries(countries, nb_countries);
    free_all_continents(continents, nb_continents);
    return 0;
}
