#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Return a byte at a time of the rand() keystream
char randchar() {
  static int key;
  static int i = 0; // doesn't get destroyed when the function is done
  i = i % 4;
  if (i == 0) key = rand();
  return ((char *)(&key))[i++]; // (char *) cast the address into a list of characters
}

int main(int argc, const char* argv[]) {
  static char randstate[64];
  // The size of the array affects how sophisticated a random-number generator would be
  initstate(1649189470, randstate, 31); // seed, state array, array size

  FILE *input, *output;
  input = fopen("hw2.tex", "r");
  output = fopen("123.tex.enc", "w");

  int c;
  char randC;
  while ((c = fgetc(input)) != EOF)
  {
    fputc(c ^ randchar(), output);
  } 

  fclose(input);
  fclose(output);
}