/*
  Kevin Ruan
  CS 362
  Fall 2017
  Assignment 3: Unit Test 4 - Test shuffle() function in dominion.c
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
  const char *FUNC_STR = "shuffle";

  int player = 0;
  int seed = 1000;
  int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
    
	//printf("----------------- Testing function: %s ----------------\n", FUNC_STR);
  
  // ----------- TEST 1: Player number invalid (-1) --------------
  // player = -1;
  // printf("\nTEST 1: Player number invalid (-1) \n");
  // printf("shuffle state = %d, expected = %d\n", shuffle(player, &G), -1);
  // asserttest(shuffle(player, &G), -1);

  // ----------- TEST 2: Shuffle results in same number of cards --------------
  player = 0;
  memcpy(&testG, &G, sizeof(struct gameState)); 
  shuffle(player, &testG);
  printf("\nTEST 2: Shuffle results in same number of cards \n");
  printf("deckCount[player] state = %d, expected = %d\n", testG.deckCount[player], G.deckCount[player]);
  asserttest(testG.deckCount[player], G.deckCount[player]);
  
  // ----------- TEST 3: Zero cards the player's deck --------------
  player = 0;

  memcpy(&testG, &G, sizeof(struct gameState));

  testG.deckCount[player] = 0;
  printf("\nTEST 3: Zero cards the player's deck \n");
  printf("shuffle state = %d, expected = %d\n", shuffle(player, &testG), -1);
  asserttest(shuffle(player, &testG), -1);

  // ----------- TEST 4: Make sure the cards are shuffled --------------
  player = 0;
  memcpy(&testG, &G, sizeof(struct gameState));
  // Run shuffle for both game states
  shuffle(player, &testG);
  shuffle(player, &G);
  
  // Loop through both sets to make sure at least one card is is different
  int i, same = 1;
  if (testG.deckCount[player] == G.deckCount[player]) {
    i = 0; 
    while (same && i < G.deckCount[player]) {
      if (testG.deck[player][i] != G.deck[player][i])
        same = 0; 
      i++; 
    }
  }
  printf("\nTEST 4: Make sure the cards are shuffled \n");
  printf("shuffle state = %d, expected = %d\n", same, 0);  
  asserttest(same, 0);

  if (hasError)
    printf("\n >>>>> Failsure: Testing complete %s <<<<<\n\n", FUNC_STR);
  else
    printf("\n >>>>> Success: Testing complete %s <<<<<\n\n", FUNC_STR);

  return 0;
}
