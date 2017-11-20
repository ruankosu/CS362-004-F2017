/*
  Kevin Ruan
  CS 362
  Fall 2017
  Assignment 4: Random Test - smithy card in dominion.c
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

#define TESTCARD "smithy"
int test1_passed = 0, test2_passed = 0, test3_passed = 0;

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
  int newCards = 0;
  int discarded = 1;
  srand(time(NULL));
  
  int numTests = 1000, i=0;
  
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
    G.hand[thisPlayer][handpos] = smithy;     

    // ----------- TEST 1: +3 cards --------------
    // printf("TEST 1: +3 cards\n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

    newCards = 3;
    if (asserttest(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded) &&
        asserttest(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards) &&
        asserttest(testG.playedCardCount, G.playedCardCount + discarded)) 
        {
          test1_passed++;
        }

    // ----------- TEST 2: Check smithy is not trashed after play --------------
    gainCard(smithy, &testG, 2, thisPlayer);
    int before = fullDeckCount(thisPlayer, smithy, &testG);
    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    int after = fullDeckCount(thisPlayer, smithy, &testG);
    
    if(asserttest(before, after)) {
      test2_passed++;
    }
    
    // ----------- TEST 3: smithy cost test --------------
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.numBuys = 1;
    testG.coins = (rand() % 10) + 1;
    testG.supplyCount[smithy] = floor(rand() % 10) + 1;
    
    if (testG.supplyCount[smithy] == 0) {
      if (asserttest(buyCard(smithy, &testG), -1)) {
        test3_passed++;
      }
    }
    else if (testG.coins >= 4) {
      if (asserttest(buyCard(smithy, &testG), 0)) {
        test3_passed++;
      }
    } else if (testG.coins < 4) {
      if (asserttest(buyCard(smithy, &testG), -1)) {
        test3_passed++;
      }
    }

  }
  printf("\n >>>>> %s: Test 1 completed with %d passes. <<<<<\n", TESTCARD, test1_passed);
  printf(" >>>>> %s: Test 2 completed with %d passes. <<<<<\n", TESTCARD, test2_passed);
  printf(" >>>>> %s: Test 3 completed with %d passes. <<<<<\n\n", TESTCARD, test3_passed);
  
	return 0;
}


