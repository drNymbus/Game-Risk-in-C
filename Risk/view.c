#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "risk_view_initialize.h"
#include "risk_model.h"

void print_list_country(country_t* countries[], uint nb_country) {
  for(uint i=0; i < nb_country; i++){
    printf("%s %d ", countries[i]->name,countries[i]->nb_connections);
    printf("%d|cap=%d\n", true, countries[i]->capital);
  }
}
