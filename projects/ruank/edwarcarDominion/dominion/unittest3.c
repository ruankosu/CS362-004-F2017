/*
  Kevin Ruan
  CS 362
  Fall 2017
  Assignment 3: Unit Test 3 - Test updateCoins() function in dominion.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int hasError;

void asserttest(int a, int b) {
	if (a != b) {
		if (!hasError) {
			hasError = 1;
		}
	}
}

int main() {
  const char *FUNC_STR = "updateCoins";

  int player = 0;
  int seed = 1000;
  int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
    
	printf("----------------- Testing function: %s ----------------\n", FUNC_STR);
  
  // ----------- TEST 1: Player number invalid (-1)--------------
  player = -1;
  updateCoins(-1, &G, 0);
  printf("TEST 1: Player number invalid (-1) \n");
  printf("updateCoins state = %d, expected = %d\n", G.coins, 0);
  asserttest(G.coins, 0);

  // ----------- TEST 2: Player 0 has 3 cards in hand: 1 copper, 1 silver, and 1 gold --------------
  player = 0;
  memcpy(&testG, &G, sizeof(struct gameState));
  
  testG.handCount[player] = 3;
  testG.hand[player][0] = copper;
  testG.hand[player][1] = silver;
  testG.hand[player][2] = gold;
  updateCoins(player, &testG, 0);
  printf("\nTEST 2: Player 0 has 1 copper, 1 silver, and 1 gold \n");
  printf("updateCoins state = %d, expected = %d\n", testG.coins, 6);
  asserttest(testG.coins, 6);

  // ----------- TEST 3: Player 0 has 3 cards in hand: 1 copper, 1 silver, 1 gold and 1 bonus --------------
  player = 0;
  memcpy(&testG, &G, sizeof(struct gameState));
  
  testG.handCount[player] = 3;
  testG.hand[player][0] = copper;
  testG.hand[player][1] = silver;
  testG.hand[player][2] = gold;
  updateCoins(player, &testG, 1);
  printf("\nTEST 3: Player 0 has 3 cards in hand: 1 copper, 1 silver, 1 gold and 1 bonus  \n");
  printf("updateCoins state = %d, expected = %d\n", testG.coins, 7);
  asserttest(testG.coins, 7);

	if (hasError)
    printf("\n >>>>> Failsure: Testing complete %s <<<<<\n\n", FUNC_STR);
  else
    printf("\n >>>>> Success: Testing complete %s <<<<<\n\n", FUNC_STR);

  return 0;
}
