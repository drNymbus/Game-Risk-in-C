#include "risk_model.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
/*
#define DECO_CELL_H '-'
#define DECO_CELL_V '|'
*/

/*=========================VIEW============================*/

void print_empty_country(void);
void print_country(country_t*country);
void print_continent(continent_t* continent);
void print_grid(continent_t** continents, uint nb_continents, country_t** countries);

/*======================INITIALIZER========================*/

uint get_nb_countries(void);
country_t** create_countries(void);
uint get_nb_continents(void);
continent_t** create_continents(country_t** countries);

void free_all_countries(country_t** countries, uint nb_countries);
void free_all_continents(continent_t** continents, uint nb_continents);

/*===================USER INTERACTION=======================*/

uint ask_nb_players(void);
user_t** ask_users(uint nb_players);
int ask_troops(void);
char* ask_move(void);
int* ask_from_to(void);
//int ask_number(void);
