#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Return a byte at a time of the rand() keystream
char randchar(int reset) {
  static int key;
  static int i = 0; // doesn't get destroyed when the function is done
  if (reset == 0) {
    i = 0;
  }
  i = i % 4;
  if (i == 0) key = rand();
  return ((char *)(&key))[i++]; // (char *) cast the address into a list of characters
}

int main(int argc, const char* argv[]) {
  for (unsigned curTime = time(NULL); curTime >= 0; curTime--) {
    static char randstate[64];
    FILE *input, *output, *output2;

    // The size of the array affects how sophisticated a random-number generator would be
    initstate(curTime, randstate, 31); // seed, state array, array size
    if (curTime % 10000 == 0) {
    	printf("%d\n", curTime);
    }

    input = fopen("hw2.tex", "r");
    output = fopen("exOut.tex.enc", "w"); // experiment output
    
    int c1, c2, c3;
    for (int i = 0; i < 16; i++) { // check the first 16 characters
      c1 = fgetc(input);
      fputc(c1 ^ randchar(i), output);
    }
    fclose(input);
    fclose(output);

    int foundSeed = 1;
    output = fopen("exOut.tex.enc", "r");
    output2 = fopen("hw2.tex.enc", "r");
    for (int i = 0; i < 16; i++) {
      c1 = fgetc(output);
      c2 = fgetc(output2);
      if (c1 != c2) {
        foundSeed = 0;
        break;
      }
    }
    fclose(output);
    fclose(output2);
    
    if (foundSeed) {
      printf("Found Seed!\n");
      printf("%d", curTime); // 1649189470
      return 0;
    }
  }
}
