#define _POSIX_C_SOURCE 200809L

#include "command.h"
#include "intel.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

/*
Grille 10x10
x : A-J
y : 0-9
5 mines
5 navires : 5 4 3 3 2
3 actions : SHOOT POLL MOVE
*/

int main(int argc, char const *argv[])
{
  setbuf(stdout, NULL);
  char buffer[BUFSIZE];

  struct map ennemy_navy;
  map_create(&ennemy_navy);

  // mines
  set_mine(&ennemy_navy, 1, 0); //B0
  set_mine(&ennemy_navy, 9, 1); //J1
  set_mine(&ennemy_navy, 8, 9); //I9
  set_mine(&ennemy_navy, 0, 8); //A8
  set_mine(&ennemy_navy, 4, 6); //D6

  // bataux

  srand(time(NULL));
  int hasard = rand();
  fprintf(stderr, "%d\n", hasard);
  if(hasard % 6 == 0 || hasard %6 == 5)
  {
    printf("C0C4\n");
    fgets(buffer, BUFSIZE, stdin);
    printf("H5E5\n");
    fgets(buffer, BUFSIZE, stdin);
    printf("F6F8\n");
    fgets(buffer, BUFSIZE, stdin);
    printf("H6H8\n");
    fgets(buffer, BUFSIZE, stdin);
    printf("B2B3\n");
    fgets(buffer, BUFSIZE, stdin);
    fprintf(stderr, "Disposition n°1\n");
  }
  else if (hasard % 6 == 1 || hasard % 6 == 4 )
  {
    printf("H9H5\n");
    fgets(buffer, BUFSIZE, stdin);
    printf("C4F4\n");
    fgets(buffer, BUFSIZE, stdin);
    printf("E3E1\n");
    fgets(buffer, BUFSIZE, stdin);
    printf("C3C1\n");
    fgets(buffer, BUFSIZE, stdin);
    printf("I7I6\n");
    fgets(buffer, BUFSIZE, stdin);
    fprintf(stderr, "Disposition n°2\n");
  }
  else  // %2 ou %3 == 0
  {
    printf("H0H4\n");
    fgets(buffer, BUFSIZE, stdin);
    printf("C5F5\n");
    fgets(buffer, BUFSIZE, stdin);
    printf("E6E8\n");
    fgets(buffer, BUFSIZE, stdin);
    printf("C6C8\n");
    fgets(buffer, BUFSIZE, stdin);
    printf("I2I3\n");
    fgets(buffer, BUFSIZE, stdin);
    fprintf(stderr, "Disposition n°3\n");
  }

  // plan d'attaque
  struct sequence attack;
  sequence_create(&attack);

  sequence_add_back(&attack, POLL,    4,   4);  //E4
  sequence_add_back(&attack, POLL,    4,   1);  //E1
  sequence_add_back(&attack, SHOOT,   6,   4);  //G4
  sequence_add_back(&attack, POLL,    7,   1);  //H1
  sequence_add_back(&attack, POLL,    8,   4);  //I4
  sequence_add_back(&attack, POLL,    5,   5);  //F5
  sequence_add_back(&attack, POLL,    8,   7);  //I7
  sequence_add_back(&attack, POLL,    5,   8);  //F8
  sequence_add_back(&attack, POLL,    2,   8);  //C8
  sequence_add_back(&attack, POLL,    1,   5);  //B5
  sequence_add_back(&attack, POLL,    1,   2);  //B2


  sequence_add_back(&attack, SHOOT,   0,   0);  //A0
  sequence_add_back(&attack, SHOOT,   2,   0);  //C0

  sequence_add_back(&attack, SHOOT,   9,   0);  //J0
  sequence_add_back(&attack, SHOOT,   9,   2);  //J2

  sequence_add_back(&attack, SHOOT,   9,   9);  //J9
  sequence_add_back(&attack, SHOOT,   7,   2);  //H9

  sequence_add_back(&attack, SHOOT,   0,   9);  //A9
  sequence_add_back(&attack, SHOOT,   0,   7);  //A7

  struct info info;
  info_create(&info);

  while(strcmp(buffer, "START\n"))
  {
    fgets(buffer, BUFSIZE, stdin);
    fprintf(stderr, "%s", buffer);
  }

  for (size_t i = 1; ; i++)
  {
    fprintf(stderr, "\n[-- Round %lu --]\n", i);
    process(&attack, &info, &ennemy_navy, buffer);
  }
  return EXIT_SUCCESS;
}
