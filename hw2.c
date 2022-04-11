#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Return a byte at a time of the rand() keystream
char randchar() {
  static int key;
  static int i = 0; // doesn't get destroyed when the function is done
  i = i % 4;
  if (i == 0) key = rand();
  printf("%d\n", key);
  printf("%p\n", &key);
  printf("%s", (char *)(&key));
  return ((char *)(&key))[i++]; // (char *) cast the address into a list of characters
}

int main(int argc, const char* argv[]) {
  static char randstate[64];
  // The size of the array affects how sophisticated a random-number generator would be
  initstate(time(NULL),randstate,31); // seed, state array, array size

  FILE *input, *output;
  input = fopen("hw2.tex", "r");
  output = fopen("hw2.tex.enc", "w");

  int c;
  char randC;
  while ((c = fgetc(input)) != EOF)
  {
    printf("%d\n", c);
    randC = randchar();
    printf("%c\n", randC);
    fputc(c ^ randC,output);
  }
    

  fclose(input);
  fclose(output);
}