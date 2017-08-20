#define NB_CONNECTIONS_MAX 6
#define NB_CONTINENT_MAX 12
#define NB_COUNTRY_MAX 42
#define CONTINENT_OWNED_MAX 6
#define NB_MAX_PLAYERS 5
#define NO_OWNER "NULL"
#define LENGTH_MAX 30

typedef unsigned int uint;
struct continent_t;

typedef struct{
  uint pos_x;
  uint pos_y;
} position_t;

typedef struct{
  char name[LENGTH_MAX];
  char* owner;
  uint nb_connections;
  struct country_t* connections[NB_CONNECTIONS_MAX];
  uint current_troop;
  uint max_troop;
  struct continent_t* continent;//char* continent;
  bool capital;
  position_t position;
} country_t;

typedef struct{
  char name[LENGTH_MAX];
  char* owner;
  uint nb_country;
  country_t* countries[NB_CONTINENT_MAX];
  int bonus_troop;
} continent_t;

typedef struct{
  char* name;
  uint nb_country;
  country_t* countries[NB_COUNTRY_MAX];
  uint nb_continent;
  continent_t* continents[CONTINENT_OWNED_MAX];
  uint nb_stars;
  uint gain;
  char color;
} user_t;

bool compare_char(char* char1, char* char2);
void swap(uint tab[],uint i,uint j);
void sort_array(uint t[],uint size);

uint * roll_dices(uint nb_dice);


void add_troops(country_t* country, uint gain);
void loss_troops(country_t* country, uint loss);

void set_country_owner(country_t* country, user_t* owner);
void set_capital(country_t* country);

void move_troops(country_t* country_from, country_t* country_to, uint nb_units);

void add_stars(user_t* user);

uint* attack_roll(uint attack, uint defense);
uint* attack( country_t* attack, country_t* defense);

void set_continents_owned(user_t* owner, continent_t* continents[CONTINENT_OWNED_MAX]);
uint nb_capital_owned(user_t* owner);
void calcul_gain(user_t* owner);

void set_position(position_t* position, uint pos_x, uint pos_y);
bool compare_position(position_t* pos1, position_t* pos2);
