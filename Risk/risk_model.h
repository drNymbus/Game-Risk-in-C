#define NB_CONNECTIONS_MAX 6
#define NB_COUNTRY_MAX 42

#define NB_CONTINENT_MAX 12
#define CONTINENT_OWNED_MAX 6

#define NB_MAX_PLAYERS 5
#define NO_OWNER "NULL"

#define LENGTH_MAX 30

#define MAP_X 10
#define MAP_Y 10
#define NB_CELLS MAP_X*MAP_Y


typedef unsigned int uint;

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

position_t* create_position(uint x, uint y);

/*====================COUNTRY=====================*/

country_t* country_alloc(void);
void set_country_id(country_t* country, int id);
void set_country_name(country_t* country, char* name);
void set_country_owner(country_t* country, user_t* user);
void set_nb_connections(country_t* country, uint nb_connections);
void connect_countries_id(country_t* country1, int id);
void add_troops(country_t* country, int nb_troops);
void loss_troops(country_t* country, int nb_troops);
void set_continent(country_t* country, continent_t* continent);
void set_capital(country_t* country, bool is);
void set_position(country_t* country, position_t* position);
void free_country(country_t* country);

int get_id(country_t* country);
int* get_connections(country_t* country);

/*============CONTINENT====================*/

continent_t* continent_alloc(void);
void set_id_continent(continent_t* continent, int id);
void set_continent_name(continent_t* continent, char* name);
void set_owner_continent(continent_t* continent, user_t* user);
void set_nb_countries(continent_t* continent, uint nb_connections);
void country_id_to_continent(continent_t* continent, int id);
void set_bonus_troop(continent_t* continent, int bonus_troops);
void free_continent(continent_t* continent);

/*=============USER=============*/

user_t* user_alloc(void);
void set_user_name(user_t* user, char* name);
void add_country(user_t* user, country_t* country);
void loss_country(user_t* user, country_t* country);
void add_stars(user_t* user, int nb_stars);
uint calculation_gain(user_t* user);
void set_gain(user_t* user, uint gain);
void set_color_user(user_t* user, char* color);
void activate_boost(user_t* user, bool boost);
void free_user(user_t* user);
