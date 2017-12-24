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

uint length_string(char* s);
void print_empty_country(void);
void print_country(country_t*country);
void print_continent(continent_t* continent);
void print_grid(continent_t** continents, uint nb_continents, country_t** countries);
void display_instructions(state_t* state);
void display_user_info(user_t* user);
void display_rules(void);

/*======================INITIALIZER========================*/

uint get_nb_countries(char* path);
void create_countries(country_t** countries, char* path);

uint get_nb_continents(char* path);
void create_continents(continent_t** continents, country_t** countries, char* path);

void free_all_countries(country_t** countries, uint nb_countries);
void free_all_continents(continent_t** continents, uint nb_continents);
void free_all_users(user_t** users, uint nb_users);

/*===================USER INTERACTION=======================*/

bool yes_no(void);
uint ask_nb_players(void);
user_t** ask_users(uint nb_players);
int ask_troops(void);
action ask_move(void);
int ask_id_country(char* msg, uint nb_countries);
void choose_country(country_t** countries, uint nb_countries, user_t** users, uint nb_users);
void lower_case(char* str);
bool compare_string(char* s1, char* s2);
