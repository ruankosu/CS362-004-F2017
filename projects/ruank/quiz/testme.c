#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
  return rand() % (126 + 1 - 32) + 32; // rand() & (max + 1 - min) + min; for completness
}

char *inputString()
{
  int i;
  int BUFFER_SIZE = 6; // max length of the test array is 6  
  char s[4] = "rest"; // set of character that would lead to exit
  char *output = malloc(sizeof(char) * BUFFER_SIZE);

  // if we hit an even iteration, we'll generate a random string for a full set of characters
  if (rand() % 2 == 0) {
    for (i = 0; i < BUFFER_SIZE - 1; i++) {
      output[i] = (char)(rand() % (122 + 1 - 97) + 97);
    }   
    return output; 
  // otherwise, we'll generate a version using the same letters that would lead to print("error")
  } else {
    for (i = 0; i < BUFFER_SIZE - 1; i++) {
      output[i] = s[rand() % 4];
    }
    return output;
  }
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
