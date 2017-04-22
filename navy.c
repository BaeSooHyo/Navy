#include "command.h"
#include "intel.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

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
  set_mine(&ennemy_navy, 1, 9);
  set_mine(&ennemy_navy, 3, 9);
  set_mine(&ennemy_navy, 5, 9);
  set_mine(&ennemy_navy, 7, 9);
  set_mine(&ennemy_navy, 9, 9);

//TODO Placer bateaux efficacement

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

  //plan d'attaque
  struct sequence blitzkrieg;
  sequence_create(&blitzkrieg);
  sequence_add_back(&blitzkrieg, POLL,  1, 1);  //B1
  sequence_add_back(&blitzkrieg, POLL,  1, 4);  //B4
  sequence_add_back(&blitzkrieg, POLL,  1, 7);  //B7
  sequence_add_back(&blitzkrieg, POLL,  4, 7);  //E7
  sequence_add_back(&blitzkrieg, POLL,  4, 4);  //E4
  sequence_add_back(&blitzkrieg, POLL,  4, 1);  //E1
  sequence_add_back(&blitzkrieg, POLL,  7, 1);  //H1
  sequence_add_back(&blitzkrieg, POLL,  7, 4);  //H4
  sequence_add_back(&blitzkrieg, POLL,  7, 7);  //H7
  sequence_add_back(&blitzkrieg, SHOOT, 9, 1);  //J1
  sequence_add_back(&blitzkrieg, SHOOT, 9, 3);  //J3
  sequence_add_back(&blitzkrieg, SHOOT, 9, 5);  //J5
  sequence_add_back(&blitzkrieg, SHOOT, 9, 7);  //J7
  struct position_info info;
  position_info_create(&info);

  while(strcmp(buffer, "START\n"))
  {
    fgets(buffer, BUFSIZE, stdin);
    fprintf(stderr, "%s", buffer);
  }

  for (size_t i = 1; ; i++)
  {
    fprintf(stderr, "\nRound %lu : \n", i);
    process(&blitzkrieg, &info, &ennemy_navy, buffer);
  }
  return EXIT_SUCCESS;
}
