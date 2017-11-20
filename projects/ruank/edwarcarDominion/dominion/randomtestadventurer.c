/*
  Kevin Ruan
  CS 362
  Fall 2017
  Assignment 4: Random Test - adventurer card in dominion.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TESTCARD "adventurer"
int test1_passed = 0, test2_passed = 0;

int asserttest(int a, int b) {
	if (a == b) {
    return 1;
  }
  return 0;
}

int randomRange(int min, int max) {
  return (rand() % (max + 1 - min)) + min;
}

int main() {
  printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
  printf("Running 1000 tests of random state, player number, and card counts\n");
  printf("\nTEST 1: Play take 2 treasury cards from discard."); 
  printf("\nTEST 2: Adventurer cost test\n");
  printf("\nTEST 3: No state change should occur to the victory card piles and kingdom card piles\n");
  
  srand(time(NULL));

  int numTests = 1000, i=0;
  int newCards = 0;
  int discarded = 1;

  for (i = 0; i < numTests; i++) {

    int handpos = rand() % MAX_HAND, choice1 = rand() % 27, choice2 = rand() % 27, choice3 = rand() % 27, bonus = rand() % 27;
    int seed = floor(rand() % 2000 + 1000);
    int numPlayers = (rand() % (MAX_PLAYERS + 1 - 2)) + 2; // For completeness. Randome players 2 to 4.
    int thisPlayer = rand() % numPlayers;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    G.whoseTurn = thisPlayer;
    G.deckCount[thisPlayer] = randomRange(5,10);
    G.discardCount[thisPlayer] = randomRange(5,10);
    G.handCount[thisPlayer] = randomRange(5,10);

    // Set cards based on random card counts
    int n;
    for (n = 0; n < G.handCount[thisPlayer]; n++) {
      G.hand[thisPlayer][n] = randomRange(4,27);
    }
    for (n = 0; n < G.deckCount[thisPlayer]; n++) {
      G.deck[thisPlayer][n] = randomRange(4,27);
    }
    for (n = 0; n < G.discardCount[thisPlayer]; n++) {
      G.discard[thisPlayer][n] = randomRange(4,8);
    }
    G.hand[thisPlayer][handpos] = adventurer;
    
    memcpy(&testG, &G, sizeof(struct gameState));
    // ----------- TEST 1: Play Adventurer Card from initial state --------------

    // copy the game state to a test case
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    newCards = 2;
    if (asserttest(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded + newCards) &&
        asserttest(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards) &&
        asserttest(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded))
        {
          test1_passed++;
        }

    // ----------- TEST 2: Adventurer cost test --------------

    testG.numBuys = 1;
    testG.coins = (rand() % 10) + 1;
    testG.supplyCount[adventurer] = floor(rand() % 10) + 1;

    if (testG.supplyCount[adventurer] == 0) {
      if (asserttest(buyCard(adventurer, &testG), -1)) {
        test2_passed++;
      }
    }
    else if (testG.coins >= 6) {
      if (asserttest(buyCard(adventurer, &testG), 0)) {
        test2_passed++;
      }
    } else if (testG.coins < 6) {
      if (asserttest(buyCard(adventurer, &testG), -1)) {
        test2_passed++;
      }
    }
  
  }


  printf("\n >>>>> %s: Test 1 completed with %d passes. <<<<<\n", TESTCARD, test1_passed);
  printf(" >>>>> %s: Test 2 completed with %d passes. <<<<<\n", TESTCARD, test2_passed);

  return 0;
}
