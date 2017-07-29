#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "risk_model.h"

int main(void){
  FILE* file = fopen("initializer/country.txt", "r");
  country_t country;
  uint nb_country;
  fscanf(file,"%d\n%s %d %d",&nb_country,country.name,&country.nb_connections,&country.max_troop);
  position_t position;
  fscanf(file, "%d %d", &position.pos_x, &position.pos_y);
  char islande[7];
  fscanf(file,"\n%s", islande);
  printf("Islande = %s", islande);
  return 0;
}
