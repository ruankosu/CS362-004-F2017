/*
  Kevin Ruan
  CS 362
  Fall 2017
  Assignment 4: Random Test - council_room card in dominion.c
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

#define TESTCARD "council_room"
int test1_passed = 0, test2_passed = 0, test3_passed = 0, test4_passed = 0;

int asserttest(int a, int b) {
	if (a == b) {
    return 1;
  }
  return 0;
}

int randomRange(int min, int max) {
  return floor((rand() % (max + 1 - min))) + min;
}

int main() {
  int numTests = 1000, i=0;
  int newCards = 0;
  int buys = 0;
  int discarded = 1;

  printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
  printf("TEST 1: +4 Cards \n");
  printf("TEST 2: +1 Buy\n");
  printf("TEST 3: Each other player draws a card\n");
  printf("TEST 4: Council Room cost test\n");
  srand(time(NULL));
  
  for (i = 0; i < numTests; i++) {
    int handpos = rand() % MAX_HAND, choice1 = rand() % 27, choice2 = rand() % 27, choice3 = rand() % 27, bonus = rand() % 27;
    int seed = randomRange(1000,2000);
    int numPlayers = randomRange(2, MAX_PLAYERS); // For completeness. Randome players 2 to 4.
    int thisPlayer = rand() % numPlayers;    
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    G.whoseTurn = thisPlayer;
    G.deckCount[thisPlayer] = randomRange(10,12);
    G.discardCount[thisPlayer] = randomRange(10, 12);
    G.handCount[thisPlayer] = randomRange(10,12);

    int n;
    for (n = 0; n < G.handCount[thisPlayer]; n++) {
      G.hand[thisPlayer][n] = randomRange(4,27);
    }
    for (n = 0; n < G.deckCount[thisPlayer]; n++) {
      G.deck[thisPlayer][n] = randomRange(4,27);
    }
    for (n = 0; n < G.discardCount[thisPlayer]; n++) {
      G.discard[thisPlayer][n] = randomRange(4,27);
    }

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // ----------- TEST 1: +4 Cards --------------
    cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
    newCards = 4;
    if (asserttest(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded) &&
        asserttest(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards)) {
          test1_passed++;
        }

    // ----------- TEST 2: +1 Buy --------------
    buys = 1;
    if (asserttest(testG.numBuys, G.numBuys + buys)) {
      test2_passed++;
    };

    // ----------- TEST 3: Each other player draws a card --------------
    newCards = 1;
    int otherPlayer;
    if (thisPlayer + 1 >= numPlayers) {
      otherPlayer = 0; 
    } else {
      otherPlayer = thisPlayer + 1;
    }
    if (asserttest(testG.handCount[otherPlayer], testG.handCount[thisPlayer] + newCards) &&
        asserttest(testG.deckCount[otherPlayer], testG.deckCount[thisPlayer] - newCards)) {
          test3_passed++;
        }

    // ----------- TEST 4: Council Room cost test --------------
    // copy the game state to a test case
    testG.numBuys = 1;
    testG.coins = (rand() % 10) + 1;
    testG.supplyCount[council_room] = floor(rand() % 10) + 1;
    
    if (testG.supplyCount[council_room] == 0) {
      if (asserttest(buyCard(council_room, &testG), -1)) {
        test4_passed++;
      }
    }
    else if (testG.coins >= 5) {
      if (asserttest(buyCard(council_room, &testG), 0)) {
        test4_passed++;
      }
    } else if (testG.coins < 5) {
      if (asserttest(buyCard(council_room, &testG), -1)) {
        test4_passed++;
      }
    }
  }

  printf("\n >>>>> %s: Test 1 completed with %d passes. <<<<<\n", TESTCARD, test1_passed);
  printf(" >>>>> %s: Test 2 completed with %d passes. <<<<<\n", TESTCARD, test2_passed);
  printf(" >>>>> %s: Test 3 completed with %d passes. <<<<<\n\n", TESTCARD, test3_passed);
  printf(" >>>>> %s: Test 4 completed with %d passes. <<<<<\n\n", TESTCARD, test4_passed);
  
  return 0;
}


