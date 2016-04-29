#include "dominion.h"
#include <stdio.h>

int failed = 0;

int myassert(int val,char* msg) {
  if (val == -1) {
    printf("FAILURE: %s\n",msg);
    failed = 1;
  }
}

void good_assert() {
  if (!failed) {
    printf ("SUCCESS!\n");
  }
}

// tests the drawCard function
int main(){

  struct gameState g;
  int r;
  
  int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
    			outpost,baron,tribute};
  
  initializeGame(2, k, 5, &g);
  
  r = drawCard(1, &g);
  myassert(r == -1, "Could not draw card");
  
  good_assert(); 
}