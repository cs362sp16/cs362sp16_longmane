#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dominion.h"
#include "interface.h"
#include "rngs.h"
#include "dominion_helpers.h"

#define NUM_TOTAL_K_CARDS (treasure_map + 1)
#define STRING_LEN 32

//game function
struct gameState init_Game(long seed);
void game_play(long seed);

//card functions
int card_check_same(enum CARD *cards, enum CARD c, int max);
void card_random(enum CARD *cards);
int card_action(enum CARD *cards, int length);
int card_action_index(struct gameState *g);
int card_play(struct gameState *g);
int card_buy(struct gameState *g);

//player functions
void player_action(struct gameState *g);
int player_buy(struct gameState *g);


int main(int argc, char **argv)
{
	long seed;
	
	srand(time(NULL));
	
	if(argc != 2){
		printf("USAGE: [Program Name]\n");
		printf("You may want to put the output into a file for later use\n");
		return 0;
	} else{
		seed = atoi(argv[1]);
	}

	game_play(seed);
	
	return 0;	
}

int card_check_same(enum CARD *cards, enum CARD c, int max)
{
	int i;
	
	for(i = 0; i < max; i++){
		if(cards[i] == c){
			return 1;
		}
	}
	return 0;
}

void card_random(enum CARD *cards)
{
	int i;
	
	for(i = 0; i < 10; i++){
		cards[i] = (enum CARD)(int)floor(Random() * NUM_TOTAL_K_CARDS);
		
		while(card_check_same(cards, cards[i], i-1)){
			cards[i] = (enum CARD)(int)floor(Random() * NUM_TOTAL_K_CARDS);
		}
	}
}

struct gameState init_Game(long seed)
{
	int num_players;
	struct gameState g;
	enum CARD cards[10];
	
	SelectStream(1);
	PutSeed(seed);
	
	card_random(cards);
	num_players = rand() %3 + 1;
	num_players++;
	printf("DEBUG: NUM PLAYERS %d\n", num_players);
	
	initializeGame(num_players, (int *)cards, (int)seed, &g);
	
	printf("DEBUG: NUM PLAYERS GAMESTATE %d\n", g.numPlayers);
	
	return g;
}

int card_action(enum CARD *cards, int length)
{
	int i;
	
	for(i = 0; i < length; i++){
		if(cards[i] >= adventurer && cards[i] <= treasure_map){
			return 1;
		}
	}
	return 0;
}

int card_action_index(struct gameState *g)
{
	int count, index;
	enum CARD *hand;
	
	count = g->handCount[g->whoseTurn];
	//may need *hand
	hand = g->hand[g->whoseTurn];
	
	if(!card_action(hand, count)){
		return -1;
	}
	
	index = (int)floor(Random() * count);
	
	while(!(hand[index] >= adventurer && hand[index] <= treasure_map)){
		index = (int)floor(Random() * count);
	}
	
	return index;
}

int card_play(struct gameState *g)
{
	int index, r;
	enum CARD c;
	
	index = card_action_index(g);
	c = g->hand[g->whoseTurn][index];

	r = playCard(index, 0, 0, 0, &g);
	
	printf("CARD: Playing [%d]\n", c);
	
	return r;	
}

int card_buy(struct gameState *g)
{
	enum CARD c;
	int tmp_num;
	char cardName[STRING_LEN];
	
	if(g->coins == 0 || g->numBuys == 0){
		printf("CARD: Invalid Buy\n");
		return -1;
	}
	
	c = (enum CARD)(int)floor(Random() * NUM_TOTAL_K_CARDS);
	
	while(getCost(c) > g->coins || c == curse || g->supplyCount[c] == 0){
		c = (enum CARD)(int)floor(Random() * NUM_TOTAL_K_CARDS);
	}
	
	tmp_num = c;
	
	cardNumToName(tmp_num, cardName);
	
	printf("CARD: Valid Buy [%s]\n", cardName);
	buyCard(c, g);
	
	return 0;
}

void player_action(struct gameState *g)
{
	int r;
	
	r = 1;
	
	while(r && g->numActions != 0 && card_action(g->hand[g->whoseTurn], g->handCount[g->whoseTurn])){
		r = card_play(g) == -1 ? 0 : 1;
	}
}

int player_buy(struct gameState *g)
{
	updateCoins(g->whoseTurn, g, 0);
	while(g->coins > 0 && g->numBuys > 0){
		card_buy(g);
	}
}

void game_play(long seed)
{
	int i, players;
	int w[4];
	struct gameState g;
	
	g = init_Game(seed);
	
	players = g.numPlayers;
	
	printf("GAME: Starting\n");
	printf("GAME: Players [%d]\n", players);
	
	printf("\n########################\n\n");
	
	while(!isGameOver(&g)){
		printf("\n          ----          \n\n");
		printf("PLAYER: Turn [%d]\n", g.whoseTurn);
		player_action(&g);
		player_buy(&g);
		printf("PLAYER: End Turn\n");
		endTurn(&g);
	}
	
	printf("\n########################\n\n");
	
	printf("FINAL STATS\n");
	
	for(i = 0; i < players; i++){
		printf("STATS: Player[%d] Score [%d]\n", i, scoreFor(i, &g));
	}
	
	getWinners(w, &g);
	for(i = 0; i< players; i++){
		if(w[i]){
			printf("WINNER: Player [%d]\n", i);
		}
	}
}