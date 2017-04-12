#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFSIZE 256
#define MAPSIZE 10

#define MINE 50

/*
Grille 10x10
x : A-J
y : 0-9
5 mines
5 navires
3 actions : SHOOT POLL MOVE
*/

enum boatType
{
  PorteAvions,          //5
  Croiseur,             //4
  ContreTorpilleur,     //3
  SousMarin,            //3
  Torpilleur            //2
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
  int map[MAPSIZE][MAPSIZE];
/*
Valeurs :
  0 : nul
  10 : tiré vide
  20 : tiré touché
  30 : scanné vide
  40 : scanné detecté
  50 : miné



*/
};


void map_create(struct map *self);
void set_coord(struct coord *self, int x, int y);
void move_coord(struct coord *self, int x, int y);
void set_mine(struct map *self, int x, int y);
void send_coord_explicit(int x, int y);
void send_coord(struct coord *self);

int main(int argc, char const *argv[]) {
  setbuf(stdout, NULL);

  char buffer[BUFSIZE];
  struct coord radar;
  set_coord(&radar, 2, 2);
  struct map ennemy;
  map_create(&ennemy);

  // mines
  set_mine(&ennemy, 2, 2);
  set_mine(&ennemy, 4, 0);
  set_mine(&ennemy, 3, 4);
  set_mine(&ennemy, 3, 8);
  set_mine(&ennemy, 5, 5);

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



  for (size_t i = 0; ; i++)
  {
    printf("POLL\n"); // SHOOT or POLL or MOVE
    printf("D2\n");
    fgets(buffer, BUFSIZE, stdin);
    fgets(buffer, BUFSIZE, stdin); // NOTHING or ATTACK
    //TODO Récupérer infos ici
  }
  return EXIT_SUCCESS;
}

void map_create(struct map *self)
{
  for (size_t i = 0; i < MAPSIZE; i++)
  {
    for(size_t j = 0; j < MAPSIZE; j++)
    {
      self->map[i][j] = 0;
    }
  }
}

void set_coord(struct coord *self, int x, int y)
{
  if ((0 <= x && x < 10)&&(0 <= y && y < 10))
  {
  self->x = x;
  self->y = y;
  }
}

void move_coord(struct coord *self, int x, int y)
{
  if ((0 <= self->x + x && self->x + x < 10)&&(0 <= self->y + y && self->y + y < 10))
  {
  self->x = x;
  self->y = y;
  }
}

void set_mine(struct map *self, int x, int y)
{
  if (!((0 <= x && x < 10)&&(0 <= y && y < 10)))
  {
    x = 2; y = 2;
  }
  self->map[x][y] = MINE;
  send_coord_explicit(x,y);
}

void send_coord_explicit(int x, int y)
{
  char abscisse = 'A' + y;
  printf("%c%d\n", abscisse, y);
}

void send_coord(struct coord *self)
{
  send_coord_explicit(self->x, self->y);
}



//PLAN
/*
Se deplacer sur les cases tirées par l'ennemi
Couvrir une zone et remplir la map
Position initiale sur les bords
*/
