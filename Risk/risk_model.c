#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "risk_model.h"

bool compare_char(char* char1, char* char2){
  uint i = 0;
  while(char1+i != "\0"){
    if(char1+i != char2+i){
      return false;
    }
    i++;
  }
  return true;
}

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
  for(uint i=0; i<nb_dice; i++){ //simule le lancer de des
    srand(time(NULL));
    uint roll = rand()%6 +1;
    res[i] = roll;
  }
  if(nb_dice == 3){ // compare les lancers de des
    if(res[0]<res[2]){ // pour ne garder que les 2 plus grands
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
  // trie les joueurs en fonction du nombre de pays passeder
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

void set_capital(country_t* country){
  (*country).capital = true;
}

void move_troops(country_t* country_from, country_t* country_to, uint nb_units){
  add_troops(country_to, nb_units);
  loss_troops(country_from, nb_units);
  if((*country_from).current_troop == 0){
    add_troops(country_from, nb_units);
    loss_troops(country_to, nb_units);
  }
}

void add_stars(user_t* user){
  srand(time(NULL));
  (*user).nb_stars = (*user).nb_stars + rand() % 2 + 1;
}

uint* attack_roll(uint attack, uint defense){
  // attack et defense represente le nombre de troop dans le pays
  uint* attack_roll = NULL;
  uint* defense_roll = NULL;
  // le nb de troop determine le nb de des
  if(attack > 3){
    attack_roll = roll_dices(3);
  }else if(attack <= 3){
    attack_roll = roll_dices(attack -1);
  }
  // meme chose pour la defense
  if(defense > 2){
    defense_roll = roll_dices(2);
  }else{
    defense_roll = roll_dices(1);
  }
  static uint res[2] = {0,0};
  for(uint i=0; i<2; i++){ // compare les lancers de des
    if(attack_roll[i] > defense_roll[i]){
      res[0]++;
    }else{
      res[1]++;
    }
  }
  // res[0] = nb de mort en defense
  // res[1] = nb de mort en attaque
  return res;
}

uint* attack( country_t* attack, country_t* defense ){
  // simule l'attaque d'un pays de a a z
  uint attack_troop = (*attack).current_troop;
  uint defense_troop = (*defense).current_troop;
  uint* loss = attack_roll(attack_troop, defense_troop);
  loss_troops(attack, loss[1]);
  loss_troops(defense, loss[0]);
  // retourne le nb de perte pour l'affichage
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
  uint nb_cap =  0;
  for(uint i=0; i<(*owner).nb_country; i++){
    if((*(*owner).countries[i]).capital){
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
