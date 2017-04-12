#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFSIZE 256

enum boatType
{
  PorteAvions,
  Croiseur,
  ContreTorpilleur,
  SousMarin,
  Torpilleur
};

struct boat
{
  enum boatType type;
  size_t size;
  bool hit;
};

struct coord
{
  size_t x;
  size_t y;
};

struct map
{
  int i;
};

int main(int argc, char const *argv[]) {
  setbuf(stdout, NULL);

  char buffer[BUFSIZE];

  // mines
  printf("B2\n");
  printf("D0\n");
  printf("C4\n");
  printf("C8\n");
  printf("E5\n");

  // ships
  printf("B2B6\n");
  fgets(buffer, BUFSIZE, stdin);
  printf("E8H8\n");
  fgets(buffer, BUFSIZE, stdin);
  printf("D1F1\n");
  fgets(buffer, BUFSIZE, stdin);
  printf("G5I5\n");
  fgets(buffer, BUFSIZE, stdin);
  printf("I0I1\n");
  fgets(buffer, BUFSIZE, stdin);

  for (;;)
  {
    printf("SHOOT\n"); // or POOL or MOVE
    printf("D2\n");
    fgets(buffer, BUFSIZE, stdin);
    fgets(buffer, BUFSIZE, stdin); // NOTHING or ATTACK
  }
  return EXIT_SUCCESS;
}


//PLAN
/*
Se deplacer sur les cases tirées par l'ennemi
Couvrir une zone et remplir la map
Position initiale sur les bords
*/
