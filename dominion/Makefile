CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	
unittestresults.out: dominion.o rngs.o
	gcc -o unittest1 unittest1.c dominion.c rngs.o $(CFLAGS)
	gcc -o unittest2 unittest2.c dominion.c rngs.o $(CFLAGS)
	gcc -o unittest3 unittest3.c dominion.c rngs.o $(CFLAGS)
	gcc -o unittest4 unittest4.c dominion.c rngs.o $(CFLAGS)
	gcc -o cardtest1 cardtest1.c dominion.c rngs.o $(CFLAGS)
	gcc -o cardtest2 cardtest2.c dominion.c rngs.o $(CFLAGS)

	rm -f unittestresults.out
	-./unittest1 >> unittestresults.out
	-./unittest2 >> unittestresults.out
	-./unittest3 >> unittestresults.out
	-./unittest4 >> unittestresults.out
	-./cardtest1 >> unittestresults.out
	-./cardtest2 >> unittestresults.out

	gcov dominion.c >> unittestresults.out
	
all: playdom player

clean:
	rm -f *.o playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.a *.dSYM