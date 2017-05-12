#define _POSIX_C_SOURCE 200809L

#include "command.h"
#include "intel.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

/*
Grille 10x10
x : A-J
y : 0-9
5 mines
5 navires : 5 4 4 3 2
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
  //Tirage au sort d'une disposition de bateaux parmi 4 possibilités
  //Les dispositions sont crées selon un motif de base, qui est modifié par miroir
  srand(time(NULL));
  int hasard = rand();
  fprintf(stderr, "%d\n", hasard);
  if(hasard % 4 == 0)
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
  else if(hasard % 4 == 1)
  {
    printf("C9C5\n");
    fgets(buffer, BUFSIZE, stdin);
    printf("H4E4\n");
    fgets(buffer, BUFSIZE, stdin);
    printf("F3F1\n");
    fgets(buffer, BUFSIZE, stdin);
    printf("H3H1\n");
    fgets(buffer, BUFSIZE, stdin);
    printf("B7B6\n");
    fgets(buffer, BUFSIZE, stdin);
    fprintf(stderr, "Disposition n°1\n");
  }
  else if (hasard % 4 == 2)
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
  else
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

  //Partie de base du parcours de recherche
  sequence_add_back(&attack, POLL,    4,   4);  //E4
  sequence_add_back(&attack, POLL,    4,   1);  //E1
  sequence_add_back(&attack, POLL,    7,   1);  //H1
  sequence_add_back(&attack, POLL,    8,   4);  //I4
  sequence_add_back(&attack, POLL,    5,   5);  //F5
  sequence_add_back(&attack, POLL,    8,   7);  //I7
  sequence_add_back(&attack, POLL,    5,   8);  //F8
  sequence_add_back(&attack, POLL,    2,   8);  //C8
  sequence_add_back(&attack, POLL,    1,   5);  //B5
  sequence_add_back(&attack, POLL,    1,   2);  //B2

  //Parcours supplémentaire du parcours de recherche
  //Dans le cas où des bateaux ennemis sont placés côte à côte
  //il est possible que certaines cases soient protégées de la recherche
  sequence_add_back(&attack, SHOOT,   6,   4);  //G4
  sequence_add_back(&attack, POLL,    1,   1);  //B1
  sequence_add_back(&attack, POLL,    8,   1);  //I1
  sequence_add_back(&attack, POLL,    8,   8);  //I8
  sequence_add_back(&attack, POLL,    1,   8);  //B8

  sequence_next(&attack);

  struct info info;
  info_create(&info);

  while(strcmp(buffer, "START\n"))
  {
    fgets(buffer, BUFSIZE, stdin);
    fprintf(stderr, "%s", buffer);
  }

  //Boucle de jeu
  for (size_t i = 1; ; i++)
  {
    fprintf(stderr, "\n[-- Round %lu --]\n", i);
    process(&attack, &info, &ennemy_navy, buffer);
  }
  return EXIT_SUCCESS;
}
