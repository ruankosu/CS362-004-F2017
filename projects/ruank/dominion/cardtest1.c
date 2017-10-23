/*
  Kevin Ruan
  CS 362
  Fall 2017
  Assignment 3: Card Test 1 - smithy card in dominion.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"
int hasError;

void asserttest(int a, int b) {
	if (a != b) {
		if (!hasError) {
			hasError = 1;
		}
	}
}

int main() {
  int newCards = 0;
  int discarded = 1;

  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: +3 cards --------------
	printf("TEST 1: +3 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 3;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
	printf("played count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + discarded);
	asserttest(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	asserttest(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
	asserttest(testG.playedCardCount, G.playedCardCount + discarded);

	// ----------- TEST 2: Check smithy is not trashed after play --------------
	printf("\nTEST 2: Check smithy is not trashed after play\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	gainCard(smithy, &testG, 2, thisPlayer);	
	printf("Gaining 1 smithy card for player %d\n", thisPlayer);
	printf("Before playing smithy:\n");
  printf("Player %d smithy count %d, expected %d\n", thisPlayer, fullDeckCount(thisPlayer, smithy, &testG), 1);
  asserttest(fullDeckCount(thisPlayer, smithy, &testG), 1);
  
  cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
  
  printf("After playing smithy:\n");
  printf("Player %d smithy count %d, expected %d\n", thisPlayer, fullDeckCount(thisPlayer, smithy, &testG), 1);
  asserttest(fullDeckCount(thisPlayer, smithy, &testG), 1);
  
	
	// ----------- TEST 3: smithy cost test --------------
	printf("\nTEST 3: Smithy cost test\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	G.coins = 4;
	G.numBuys = 1;
	testG.numBuys = 1;
	testG.coins = 1;
	
	printf("Buy smithy with 4 coins: %d expected: %d\n", buyCard(smithy, &G), 0);
	printf("Buy smithy with 1 coins: %d expected: %d\n", buyCard(smithy, &testG), -1);
	asserttest(buyCard(smithy, &G), 0);
	asserttest(buyCard(smithy, &testG), -1);

	if (hasError)
		printf("\n >>>>> Failsure: Testing complete %s <<<<<\n\n", TESTCARD);
	else
		printf("\n >>>>> Success: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


