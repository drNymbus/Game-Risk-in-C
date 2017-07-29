#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "risk_model.h"
#include "risk_view.h"

int main(void){
  user_t* user1 = create_user("Toto");
  user_t* user2 = create_user("Guy");
  user_t* users[] = {user1, user2};
  print_infos(users);
  return EXIT_SUCCESS;
}
