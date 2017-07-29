#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "risk_model.h"

country_t* create_countries(char* path){
  FILE* countries = fopen(path, "r");
  uint nb_total_countries;
  fscanf(countries, "%d\n", &nb_total_countries);
  static country_t countries[nb_total_countries];
  for(uint i=0; i<nb_total_countries; i++){
    
  }
  fclose(countries);
  return &countries;
}
