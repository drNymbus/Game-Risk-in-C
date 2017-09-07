#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"

#define DECO_CELL_H '-'
#define DECO_CELL_V '|'
#define MAP_X 10
#define MAP_Y 10
#define NB_CELLS MAP_X*MAP_Y

uint coord_to_index(position_t* position);

void set_map(country_t* map[NB_CELLS], country_t* countries[], uint nb_countries);

void print_map(country_t* map[NB_CELLS], position_t* position);
void print_menu(state_t* state, position_t* position);
void print_infos(user_t* user);
void print_ranking(user_t* users[NB_MAX_PLAYERS]);
void print_instructions(state_t* state);
void display_game(country_t* map[NB_CELLS], user_t* users[NB_MAX_PLAYERS], uint index_player);

/********************************************************************************/


typedef struct{
  bool initialize;
  //bool menu;
  bool set_turn;
  bool turn;
  bool end_turn;
  bool use_stars;
  bool turn_move;
  bool success;
}state_t;

uint find_nb_countries(char* path);
country_t* create_countries(char* path);
void set_connnections(country_t* countries[], uint nb_countries);
uint find_nb_continents(char* path);
continent_t* create_continents(countries_t* countries[], uint nb_countries, char* path);
void initialize_countries(country_t* countries[], uint nb_countries);

void set_bots(user_t* users[NB_MAX_PLAYERS], uint nb_countries);
void set_colors_to_users(user_t* users[NB_MAX_PLAYERS]);
void set_owner(country_t* country, user_t* owner);
void set_country_to_owner(country_t* countries[], uint nb_countries, user_t* users[NB_MAX_PLAYERS]);

uint ask_nb_players(void);
user_t* ask_users(uint nb_players);
int ask_troops(void);
char* ask_instructions(void);
int* ask_move(void);
int* ask_attack(void);
