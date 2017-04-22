#include "command.h"
#include "intel.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>



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

//TODO Placer bateaux

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

  //plan
  struct sequence blitzkrieg;
  sequence_create(&blitzkrieg);
  sequence_add_back(&blitzkrieg, POLL,  1, 1);
  sequence_add_back(&blitzkrieg, POLL,  1, 4);
  sequence_add_back(&blitzkrieg, POLL,  1, 7);
  sequence_add_back(&blitzkrieg, POLL,  4, 7);
  sequence_add_back(&blitzkrieg, POLL,  4, 4);
  sequence_add_back(&blitzkrieg, POLL,  4, 1);
  sequence_add_back(&blitzkrieg, POLL,  7, 1);
  sequence_add_back(&blitzkrieg, POLL,  7, 4);
  sequence_add_back(&blitzkrieg, POLL,  7, 7);
  sequence_add_back(&blitzkrieg, SHOOT, 9, 1);
  sequence_add_back(&blitzkrieg, SHOOT, 9, 3);
  sequence_add_back(&blitzkrieg, SHOOT, 9, 5);
  sequence_add_back(&blitzkrieg, SHOOT, 9, 7);
  struct sequence_node *current_attack = blitzkrieg.first;
  struct position_info info;
  position_info_create(&info);

  while(strcmp(buffer, "START\n"))
  {
    fgets(buffer, BUFSIZE, stdin);
    fprintf(stderr, "%s", buffer);
  }

  for (size_t i = 1; ; i++)
  {
    //FIXME Reset ne fonctionne pas
    fprintf(stderr, "%d\n", current_attack );
    fprintf(stderr, "\nRound %lu : \n", i);
    process(&current_attack, &info, buffer);
    if (current_attack == NULL){current_attack = blitzkrieg.first;}
  }
  return EXIT_SUCCESS;
}
