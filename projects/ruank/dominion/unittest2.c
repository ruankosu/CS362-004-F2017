/*
  Kevin Ruan
  CS 362
  Fall 2017
  Assignment 3: Card Test 2 - Test adventurer in dominion.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
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
  const char *FUNC_STR = "fullDeckCount";
  
  int player = 0;
  int seed = 1000;
  int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
    
	printf("----------------- Testing function: %s ----------------\n", FUNC_STR);
  
  // ----------- TEST 1: Player number invalid --------------
  player = -1;
  printf("TEST 1: Player number invalid (-1) \n");
  printf("fullDeckCount state = %d, expected = %d\n", fullDeckCount(player, 0, &G), 0);
  asserttest(fullDeckCount(player, 0, &G), 0);

  // ----------- TEST 2: x1 adventurer card in player 0's hand and deck --------------
  printf("\nTEST 2: x1 adventurer card in player 0's hand and deck\n");
  player = 0;
  G.hand[player][0] = adventurer;
  G.deck[player][0] = adventurer;
  printf("fullDeckCount state = %d, expected = %d\n", fullDeckCount(player, adventurer, &G), 2);
  asserttest(fullDeckCount(player, adventurer, &G), 2);

  // ----------- TEST 3: x1 adventurer card in player 0's discard pile --------------
  player = 0;
  G.discardCount[player] = 1;
  G.discard[player][0] = adventurer;
  printf("\nTEST 3: Add x1 adventurer card in player 0's discard pile\n");  
  printf("fullDeckCount state = %d, expected = %d\n", fullDeckCount(player, adventurer, &G), 3); 
  asserttest(fullDeckCount(player, adventurer, &G), 3);
  
	if (hasError)
    printf("\n >>>>> Failsure: Testing complete %s <<<<<\n\n", FUNC_STR);
  else
    printf("\n >>>>> Success: Testing complete %s <<<<<\n\n", FUNC_STR);

  return 0;
}
