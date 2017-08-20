typedef struct{
  bool initialize;
  bool menu;
  bool set_turn;
  bool turn;
  bool use_stars;
  bool use_boost;
}state_t;

uint find_nb_countries(char* path);
country_t* create_countries(char* path);
void set_connnections(country_t* countries[], uint nb_countries);
//uint find_nb_continents(char* path);
continent_t* create_continents(countries_t* countries[], uint nb_countries, char* path);

void set_bots(user_t* users[NB_MAX_PLAYERS], uint nb_countries);
void set_colors_to_users(user_t* users[NB_MAX_PLAYERS]);
void set_owner(country_t* country, user_t* owner);
void set_country_to_owner(country_t* countries[], uint nb_countries, user_t* users[NB_MAX_PLAYERS]);

uint ask_nb_players(void);
user_t* ask_users(uint nb_players);
uint ask_troops(void);
