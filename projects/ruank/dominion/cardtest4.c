/*
  Kevin Ruan
  CS 362
  Fall 2017
  Assignment 3: Card Test 4 - feast card in dominion.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "feast"
int hasError;
void asserttest(int a, int b) {
	if (a != b) {
		if (!hasError) {
			hasError = 1;
		}
	}
}

int main() {
 
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, feast, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: Trash this card --------------
	printf("TEST 1: Trash this card\n");
  
  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  
  gainCard(feast, &testG, 2, thisPlayer);

  printf("Before playing feast:\n");
  printf("Player %d feast count %d, expected %d\n", thisPlayer, fullDeckCount(thisPlayer, feast, &testG), 1);
  asserttest(fullDeckCount(thisPlayer, feast, &testG), 1);
  
  cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);
  
  printf("After playing feast:\n");
  printf("Player %d feast count %d, expected %d\n", thisPlayer, fullDeckCount(thisPlayer, feast, &testG), 0);
  asserttest(fullDeckCount(thisPlayer, feast, &testG), 0);
  
  // ----------- TEST 2: Gain card cost <= 5, try duchy card (cost 5) --------------
	printf("\nTEST 2: Gain card cost <= 5, try duchy card (cost 5)\n");
  
  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  // set conditions
  choice1 = duchy; 
  gainCard(feast, &testG, 2, thisPlayer);
  // play card
  cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);

  printf("Player %d duchy count %d, expected %d\n", thisPlayer, fullDeckCount(thisPlayer, duchy, &testG), 1);  
  asserttest(fullDeckCount(thisPlayer, duchy, &testG), 1);

  // ----------- TEST 3: Gain card cost > 5, try adventurer card (cost 6) --------------
	printf("\nTEST 3: Gain card cost > 5, try adventurer card (cost 6)\n");
  
  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  // set condition
  choice1 = adventurer; 
  gainCard(feast, &testG, 2, thisPlayer);
   // play card
  cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);

  printf("Player %d adventurer count %d, expected %d\n", thisPlayer, fullDeckCount(thisPlayer, adventurer, &testG), 0);  
  asserttest(fullDeckCount(thisPlayer, adventurer, &testG), 0);

	// ----------- TEST 4: Feast cost test --------------
	printf("\nTEST 4: Feast cost test\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	G.coins = 4;
	G.numBuys = 1;
	testG.numBuys = 1;
	testG.coins = 1;
	
	printf("Buy Feast with 4 coins: %d expected: %d\n", buyCard(feast, &G), 0);
	printf("Buy Feast with 1 coins: %d expected: %d\n", buyCard(feast, &testG), -1);
	asserttest(buyCard(feast, &G), 0);
	asserttest(buyCard(feast, &testG), -1);


	if (hasError)
    printf("\n >>>>> Failsure: Testing complete %s <<<<<\n\n", TESTCARD);
  else
    printf("\n >>>>> Success: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


