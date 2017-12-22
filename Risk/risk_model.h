#include <stdbool.h>

#define NB_CONNECTIONS_MAX 6
#define NB_COUNTRY_MAX 42

#define NB_CONTINENT_MAX 12
#define CONTINENT_OWNED_MAX 6

#define NB_MAX_PLAYERS 5

#define LENGTH_MAX 30

#define MAP_X 10
#define MAP_Y 10
#define NB_CELLS MAP_X*MAP_Y


typedef unsigned int uint;

typedef struct{
    int who_turn;
    bool end_game;
    bool initialize;
    bool set_board;
    bool set_turn;
    bool turn;
    bool end_turn;
}state_t;


typedef struct position_t{
    uint pos_x;
    uint pos_y;
} position_t;

typedef struct country_t{
    int id;
    char* name;
    struct user_t* owner;//ID
    uint nb_connections;
    int* connections;
    int current_troop;
    int continent;
    bool capital;
    position_t* position;
} country_t;

typedef struct continent_t{
    int id;
    char* name;
    struct user_t* owner;//ID
    uint nb_country;
    int* countries;
    int bonus_troop;
} continent_t;

typedef struct user_t{
    char* name;
    uint nb_country;
    int* countries;
    uint nb_continent;
    int* continents;
    int nb_stars;
    uint gain;
    char* color;
    bool boost;
} user_t;

void initiliaze_state(state_t* state);
void next_turn(state_t* state, uint nb_players);

position_t* create_position(uint x, uint y);

/*====================COUNTRY=====================*/

country_t* country_alloc(void);
void free_country(country_t* country);

void connect_countries(country_t* country1, country_t* country2);

void add_troops(country_t* country, int nb_troops);
void loss_troops(country_t* country, int nb_troops);

bool all_possessed(country_t** countries, uint nb_countries);

/*============CONTINENT====================*/

continent_t* continent_alloc(void);
void free_continent(continent_t* continent);

/*=============USER=============*/

user_t* user_alloc(void);
void free_user(user_t* user);

void add_country(user_t* user, country_t* country);
void loss_country(user_t* user, country_t* country);

void add_stars(user_t* user, int nb_stars);
uint calculation_gain(user_t* user, continent_t** continents);
void activate_boost(user_t* user, bool boost);
