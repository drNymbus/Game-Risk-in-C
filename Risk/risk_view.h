#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define NB_CELLS 100 // l * L
#define DECO_CELL_H '-'
#define DECO_CELL_V '|'
#define MAP_X 10
#define MAP_Y 10

uint coord_to_index(position_t* position);

void char_fusion(char char1[], char char2[]);

/*char* game_array(continent_t* continents[],user_t* user,uint nb_continent){
  static char map[nb_cells];
  for(uint cell=0; cell<nb_cells-1; cell++){
    map[cell] = 'N';
  }
  return &(map);
}

void set_countries(char map[NB_CELLS]);
void set_deco_cell(char map[NB_CELLS]);
void print_char(char s[]);
void set_ranking_cell(char map[NB_CELLS]);
void set_info_cell(char map[NB_CELLS]);
void set_uselss_cell(char map[NB_CELLS]);
*/

void set_countries(country_t* map[NB_CELLS], country_t* countries[], uint nb_countries);

/*####################################################################################*/

void print_map(country_t* map[NB_CELLS]);

void swap_user(user_t* users[], uint i, uint j);
void ranking_users(user_t* users[], uint nb_players);
void print_infos(user_t* users[NB_MAX_PLAYERS]);
