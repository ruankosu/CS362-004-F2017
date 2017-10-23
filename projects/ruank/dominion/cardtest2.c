/*
  Kevin Ruan
  CS 362
  Fall 2017
  Assignment 3: Card Test 2 - adventurer card in dominion.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"
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

  int i;
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

	// ----------- TEST 1: Play Adventurer Card from initial state --------------
	printf("TEST 1: Play Adventurer Card \n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  newCards = 2;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded + newCards);
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
  printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
  asserttest(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded + newCards);
  asserttest(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
  asserttest(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);

  // ----------- TEST 2: Check treasury card in deck and hand --------------
	printf("\nTEST 2: Check treasury card in deck and hand \n");
  
  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  int cardDrawn, countHandG = 0, countDeckG = 0, countHandTestG = 0, countDeckTestG = 0;
  for (i = 0; i < G.handCount[thisPlayer]; i++) {
    cardDrawn = G.hand[thisPlayer][i]; 
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
      countHandG++;
  }
  for (i = 0; i < G.deckCount[thisPlayer]; i++) {
    cardDrawn = G.deck[thisPlayer][i]; 
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
      countDeckG++;
  }
  for (i = 0; i < testG.handCount[thisPlayer]; i++) {  
    cardDrawn = testG.hand[thisPlayer][i]; 
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
     countHandTestG++;
  }
  for (i = 0; i < testG.deckCount[thisPlayer]; i++) {
    cardDrawn = testG.deck[thisPlayer][i]; 
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
      countDeckTestG++;
  }

  newCards = 2;
  printf("hand count = %d, expected = %d\n", countHandTestG, countHandG + newCards);
  printf("deck count = %d, expected = %d\n", countDeckTestG, countDeckG - newCards);
  asserttest(countHandTestG, countHandG + newCards);
  asserttest(countDeckTestG, countDeckG - newCards);

  // ----------- TEST 3: Number of revealed cards to discard --------------
	printf("\nTEST 3: Number of revealed cards to discard \n");
  
  // Set condition to have two non treasury cards at the top and two treasury cards right beneat
  G.deck[thisPlayer][G.deckCount[thisPlayer]-1] = estate;
  G.deck[thisPlayer][G.deckCount[thisPlayer]-2] = estate;
  G.deck[thisPlayer][G.deckCount[thisPlayer]-3] = copper;
  G.deck[thisPlayer][G.deckCount[thisPlayer]-4] = copper;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  newCards = 2;
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded + newCards);
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards - 2);
  printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 2 + discarded);
  asserttest(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded + newCards);
  asserttest(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards - 2);
  asserttest(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 2 + discarded);

  // ----------- TEST 4: Adventurer cost test --------------
  printf("\nTEST 4: Adventurer cost test \n");

  memcpy(&testG, &G, sizeof(struct gameState));
  G.numBuys = 1;  
  G.coins = 6;
  testG.numBuys = 1;
  testG.numBuys = 1;

  printf("Buy adventurer with 6 coins: %d expected: %d\n", buyCard(adventurer, &G), 0);
	printf("Buy adventurer with 1 coins: %d expected: %d\n", buyCard(adventurer, &testG), -1);
	asserttest(buyCard(adventurer, &G), 0);
	asserttest(buyCard(adventurer, &testG), -1);


	if (hasError)
    printf("\n >>>>> Failsure: Testing complete %s <<<<<\n\n", TESTCARD);
  else
    printf("\n >>>>> Success: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


