#include "command.h"
#include "intel.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFSIZE 256


/*
Grille 10x10
x : A-J
y : 0-9
5 mines
5 navires : 5 4 3 3 2
3 actions : SHOOT POLL MOVE
*/


int main(int argc, char const *argv[]) {
  struct sequence blitzkrieg;
  sequence_create(&blitzkrieg);
  sequence_add_back(&blitzkrieg, 1, 1 ,POLL);
  sequence_add_back(&blitzkrieg, 1, 4 ,POLL);
  sequence_add_back(&blitzkrieg, 1, 7 ,POLL);
  sequence_add_back(&blitzkrieg, 4, 7 ,POLL);
  sequence_add_back(&blitzkrieg, 4, 4 ,POLL);
  sequence_add_back(&blitzkrieg, 4, 1 ,POLL);
  sequence_add_back(&blitzkrieg, 7, 1 ,POLL);
  sequence_add_back(&blitzkrieg, 7, 4 ,POLL);
  sequence_add_back(&blitzkrieg, 7, 7 ,POLL);
  sequence_add_back(&blitzkrieg, 9, 1 ,SHOOT);
  sequence_add_back(&blitzkrieg, 9, 3 ,SHOOT);
  sequence_add_back(&blitzkrieg, 9, 5 ,SHOOT);
  sequence_add_back(&blitzkrieg, 9, 7 ,SHOOT);

  setbuf(stdout, NULL);
  char buffer[BUFSIZE];
  struct coord radar;
  set_coord(&radar, 2, 2);
  struct map ennemy;
  map_create(&ennemy);

  // mines
  set_mine(&ennemy, 1, 9);
  set_mine(&ennemy, 3, 9);
  set_mine(&ennemy, 5, 9);
  set_mine(&ennemy, 7, 9);
  set_mine(&ennemy, 9, 9);


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


  process(blitzkrieg.first);



  for (size_t i = 0; ; i++)
  {
    // printf("SHOOT\n"); // SHOOT or POLL or MOVE
    // printf("D2\n");
    fgets(buffer, BUFSIZE, stdin);
    fprintf(stderr, "%s", buffer);
    process(blitzkrieg.first);
    fgets(buffer, BUFSIZE, stdin); // NOTHING or ATTACK
    fprintf(stderr, "%s\n", buffer);
    //TODO Récupérer infos ici
  }
  return EXIT_SUCCESS;
}
