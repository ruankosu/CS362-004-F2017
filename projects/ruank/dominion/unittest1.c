/*
  Kevin Ruan
  CS 362
  Fall 2017
  Assignment 3: Unit Test 1 - Test isGameOver() function in dominion.c
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
  const char *FUNC_STR = "isGameOver";
  int i;
  int seed = 1000;
  int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
    
	printf("----------------- Testing function: %s ----------------\n", FUNC_STR);
    
  // ----------- TEST 1: Province card count = 0 --------------
  G.supplyCount[province] = 0;
  printf("TEST 1: Province supply = 0\n");
  printf("isGameOver state = %d, expected = %d\n", isGameOver(&G), 1);
  asserttest(isGameOver(&G), 1);

  // ----------- TEST 2: Province card count > 0 --------------
  G.supplyCount[province] = 1;
  printf("\nTEST 2: Province supply > 1\n");
  printf("isGameOver state = %d, expected = %d\n", isGameOver(&G), 0);
  asserttest(isGameOver(&G), 0);  

  // ----------- TEST 3: Three supply piles = 0 --------------
  for (i = 0; i < 3; i++) {
    G.supplyCount[i] = 0;
  }
  printf("\nTEST 3: Three supply piles = 0\n");
  printf("isGameOver state = %d, expected = %d\n", isGameOver(&G), 1);
  asserttest(isGameOver(&G), 1);
  
	if (hasError)
    printf("\n >>>>> Failsure: Testing complete %s <<<<<\n\n", FUNC_STR);
  else
    printf("\n >>>>> Success: Testing complete %s <<<<<\n\n", FUNC_STR);

	return 0;
}
