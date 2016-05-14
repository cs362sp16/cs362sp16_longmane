// Emily Longman
// 5/13/16
// random card test 2
// smithy

#include "dominion.h"
#include "interface.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]){
	
	struct gameState g;
	int seed, test_max, num_playaz, player, deck_size, hand_size, output, turn, i;
	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute};
	
	if(argc = 3){
		seed = atoi(argv[1]);
		test_max = atoi(argv[2]);
		output = atoi(argv[3]);	
	}
		
	for(i = 0; i < test_max; i++){		
		num_playaz = rand() %3 + 2;
		
		initializeGame(num_playaz, k, seed, &g);
	
		//randomly test players
		player = rand() % num_playaz;
		deck_size = rand() % MAX_DECK;
		hand_size = rand() % MAX_HAND;
		
		g.whoseTurn = player;
		g.deckCount[player] = deck_size;
		g.handCount[player] = hand_size;
		
		addCardToHand(player, smithy, &g);
		playCard(hand_size, 0, 0, 0, &g);
		
		printf("Smithy Test #%d: Players [%d] Player [%d] Deck Count [%d] Hand Count [%d + 1]\n", i, num_playaz, player, deck_size, hand_size);	
	}
}