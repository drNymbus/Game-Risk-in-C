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
