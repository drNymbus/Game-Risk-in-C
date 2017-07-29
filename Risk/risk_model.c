#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "risk_model.h"

void swap(uint tab[],uint i,uint j){
  uint tmp = tab[i];
  tab[i] = tab[j];
  tab[j] = tmp;
}

void sort_array(uint t[],uint size){
  for(uint i=0; i<size; i++){
    for(uint j=0; j<size; j++){
      if( t[i] > t[j]){
        swap(t,i,j);
      }
    }
  }
}

uint * roll_dices(uint nb_dice){
  static uint res[3];
  for(uint i=0; i<nb_dice; i++){
    srand(time(NULL));
    uint roll = rand()%6 +1;
    res[i] = roll;
  }
  if(nb_dice == 3){
    if(res[0]<res[2]){
      swap(res,0,2);
    }
    if(res[1]<res[2]){
      swap(res, 1, 2);
    }
  }
  return res;
}

void swap_user(user_t* users[NB_MAX_PLAYERS], uint i, uint j){
  user_t* p_swap = users[i];
  users[i] = users[j];
  users[j] = p_swap;
}

void ranking_struct(user_t* users[NB_MAX_PLAYERS], uint nb_players){
  for(uint i=0; i<nb_players; i++){
    uint j = i;
    while(NB_MAX_PLAYERS-j > 0){
      if((*users[j]).nb_country > (*users[j-1]).nb_country){
        swap_user(users, j, j-1);
        j--;
      }
    }
  }
}

void add_troops(country_t* country, uint gain){
  (*country).current_troop += gain;
}

void loss_troops(country_t* country, uint loss){
  (*country).current_troop -= loss;
}

void set_country_owner(country_t* country, user_t* owner){
  (*owner).nb_country++;
  uint nb_country = (*owner).nb_country;
  (*owner).countries[nb_country-1] = country;
  //char name_owner = (*owner).name;
  (*country).owner = (*owner).name;
}

void set_continent_owner(continent_t* continent, user_t* owner){
  (*owner).nb_continent++;
  uint nb_continent = (*owner).nb_continent;
  (*owner).continents[nb_continent-1] = continent;
  //char* name_owner = (*owner).name;
  (*continent).owner = (*owner).name;
}

void set_capital(country_t* country){
  (*country).capital = true;
}

void move_troops(country_t* country_from, country_t* country_to, uint nb_units){
  add_troops(country_to, nb_units);
  loss_troops(country_from, nb_units);
  if((*country_from).current_troop == 0){
    add_troops(country_from, nb_units);
    loss_troops(country_to, nb_units);
    //hard_treat_error("Cannot not move so much soldier");
  }
}

void add_stars(user_t* user){
  srand(time(NULL));
  (*user).nb_stars = (*user).nb_stars + rand() % 2 + 1;
}

uint* attack_roll(uint attack, uint defense){
  uint* attack_roll = NULL;
  uint* defense_roll = NULL;
  if(attack > 3){
    attack_roll = roll_dices(3);
  }else if(attack <= 3){
    attack_roll = roll_dices(attack -1);
  }
  if(defense > 2){
    defense_roll = roll_dices(2);
  }else{
    defense_roll = roll_dices(1);
  }
  static uint res[2] = {0,0};
  for(uint i=0; i<2; i++){
    if(attack_roll[i] > defense_roll[i]){
      res[0]++;
    }else{
      res[1]++;
    }
  }
  return res;
}

uint* attack( country_t* attack, country_t* defense ){
  uint attack_troop = (*attack).current_troop;
  uint defense_troop = (*defense).current_troop;
  uint* loss = attack_roll(attack_troop, defense_troop);
  attack_troop = attack_troop - loss[0];
  defense_troop = defense_troop - loss[1];
  return loss;
}

void set_continents_owned(user_t* owner, continent_t* continents[CONTINENT_OWNED_MAX]){
  for(uint i=0; i<CONTINENT_OWNED_MAX; i++){
    char* continent_name = (*continents[i]).name;
    uint cmpt_country = 0;
    for(uint j=0; j<(*owner).nb_country; j++){
      country_t* country = (*owner).countries[j];
      if((*country).continent[] == continent_name){
        cmpt_country++;
      }
    }
    if(cmpt_country == (*continents[i]).nb_country){
      (*continents[i]).owner = (*owner).name;
      (*owner).nb_continent++;
      (*owner).continents[(*owner).nb_continent -1] = continents[i];
    }
  }
}

uint nb_capital_owned(user_t* owner){
  country_t* countries[nb_country_max];
  for(uint i=0; i<(*owner).nb_country; i++){
    countries[i] = (*owner).countries[i];
  }
  uint nb_cap = 0;
  for(uint i=0; i<(*owner).nb_country; i++){
    country_t* country = countries[i];
    if((*country).capital){
      nb_cap++;
    }
  }
  return nb_cap;
}

void calcul_gain(user_t* owner){
  uint gain = 0, nb_country = (*owner).nb_country;
  gain = nb_country/3;
  if((*owner).nb_continent != 0)
    for(uint i=0; i<(*owner).nb_continent; i++){
      continent_t* continent = (*owner).continents[i];
      gain = gain + (*continent).bonus_troop;
    }
  gain = gain + nb_capital_owned(owner);
  (*owner).gain = gain;
}
/*
continent_t create_continent(char name[LENGTH_MAX],uint nb_country,country_t* countries[NB_CONTINENT_MAX],uint bonus_troop){
  continent_t continent;// = {name,no_owner,nb_country,countries,bonus_troop};
  for(uint i=0; name[i]!='\0'; i++){
    continent.name[i] = name[i];
  }
  continent.name[LENGTH_MAX-1] = '\0';
  continent.owner = no_owner;
  continent.nb_country = nb_country;
  for(uint i=0; i<nb_country; i++){
    continent.countries[i] = countries[i];
  }
  continent.bonus_troop = bonus_troop;
  return continent;
}

country_t create_country(char country_name[LENGTH_MAX],continent_t* continent, position_t* p_pos){
  country_t country;
  country_t* p_country = &(country);
  for(uint i=0; country_name[i]!='\0'; i++){
    (*p_country).name[i] = country_name[i];
  }
  (*p_country).name[LENGTH_MAX-1] = '\0';
  (*p_country).continent = (*continent).name;
  (*p_country).position = p_pos;
  return country;
}
*/
user_t create_user(char* name){
  user_t user;// = {name,0,{},0,{},0,0};
  user.name = name;
  user.nb_country = 0;
  user.nb_continent = 0;
  user.gain = 0;
  return user;
}

void set_position(country_t* country, uint pos_x, uint pos_y){
  position_t position = {pos_x,pos_y};
  (*country).position = &(position);
}

void set_connections(country_t* country){

}
