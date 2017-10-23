/*
  Kevin Ruan
  CS 362
  Fall 2017
  Assignment 3: Card Test 3 - council_room card in dominion.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council_room"
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
  int buys = 0;
  int discarded = 1;

  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int seed = 1000;
  int numPlayers = 2;
  int player1 = 0;
  int player2 = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: +4 Cards --------------
	printf("TEST 1: +4 Cards \n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

  newCards = 4;
	printf("hand count = %d, expected = %d\n", testG.handCount[player1], G.handCount[player1] + newCards - discarded);
  printf("deck count = %d, expected = %d\n", testG.deckCount[player1], G.deckCount[player1] - newCards);
  asserttest(testG.handCount[player1], G.handCount[player1] + newCards - discarded);
  asserttest(testG.deckCount[player1], G.deckCount[player1] - newCards);

  // ----------- TEST 2: +1 Buy --------------
	printf("\nTEST 2: +1 Buy\n");
  
  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

  buys = 1;
  printf("buy count = %d, expected = %d\n", testG.numBuys, G.numBuys + buys);
  asserttest(testG.numBuys, G.numBuys + buys);

	// ----------- TEST 3: Each other player draws a card --------------
	printf("\nTEST 3: Each other player draws a card\n");
  
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

  newCards = 4;
  printf("Player %d plays the card.\n", player1);
  printf("Player %d hand count %d, expected %d\n", player1, testG.handCount[player1], G.handCount[player1] + newCards - discarded);
  printf("Player %d deck count %d, expected %d\n", player1, testG.deckCount[player1], G.deckCount[player1] - newCards);
  newCards = 1;
  printf("Player %d hand count %d, expected %d\n", player2, testG.handCount[player2], G.handCount[player1] + newCards - discarded);
  printf("Player %d deck count %d, expected %d\n", player2, testG.deckCount[player2], G.deckCount[player1] - newCards);

	// ----------- TEST 4: Council Room cost test --------------
	printf("\nTEST 4: Council Room cost test\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	G.coins = 5;
	G.numBuys = 1;
	testG.numBuys = 1;
	testG.coins = 1;
	
	printf("Buy Council Room with 5 coins: %d expected: %d\n", buyCard(smithy, &G), 0);
	printf("Buy Council Room with 1 coins: %d expected: %d\n", buyCard(smithy, &testG), -1);
	asserttest(buyCard(smithy, &G), 0);
	asserttest(buyCard(smithy, &testG), -1);

	if (hasError)
    printf("\n >>>>> Failsure: Testing complete %s <<<<<\n\n", TESTCARD);
  else
    printf("\n >>>>> Success: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


