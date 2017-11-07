#include "risk_model.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"

#define DECO_CELL_H '-'
#define DECO_CELL_V '|'

typedef struct{
  bool initialize;
  bool menu;
  bool set_turn;
  bool turn;
  bool end_turn;
  bool use_stars;
  bool turn_move;
  bool success;
}state_t;

/*==============VIEW======================*/

void print_list_country(country_t* countries[], uint nb_country);

/*===============INITIALIZER=======================*/

uint find_nb_countries(char* path);
country_t* create_countries(char* path);
void create_connnections(country_t* countries[], uint nb_countries);
uint find_nb_continents(char* path);
continent_t* create_continents(country_t* countries[], uint nb_countries, char* path);

/*==================USER INTERACTION========================*/

uint ask_nb_players(void);
user_t* ask_users(uint nb_players);
int ask_troops(void);
char* ask_instructions(void);
int* ask_move(void);
int* ask_attack(void);
