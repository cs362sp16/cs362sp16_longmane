#include "dominion.h"
#include "dominion_helpers.h"

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

int main()
{
	struct gameState* state = calloc(1, sizeof(struct gameState));
	int tester, base;

	base = state->handCount[0]+3;

	//Testing smithy
	cardEffect(13,0,0,0,state,0,0);
	tester = state->handCount[0];

	myassert(tester==base, "smithy");

	good_assert();

	return 0;
}