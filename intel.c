#include "intel.h"
#include "command.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


//Stocke les informations d'un plan d'eau
void map_create(struct map *self)
{
  for (size_t i = 0; i < MAPSIZE; i++)
  {
    for (size_t j = 0; j < MAPSIZE; j++)
    {
      self->map[i][j] = 0;
    }
  }
}

void coord_set(struct coord *self, int x, int y)
{
  self->x = x;
  self->y = y;
}

void info_create(struct info *self)
{
  info_init(self);
}

void info_init(struct info *self)
{
  self->N = self->E = self->W = self->S = 1;
  coord_set(&(self->coord), -1, -1);     //(-1;-1) : absence d'information
  self->center_shot = false;
}


//Retourne vrai si la case correspondant aux coordonnées passées en paramètres
//ne contient ni mine ni morceau de bateau détruit
bool map_shootable(struct map *self, int x, int y)
{
  if (x < 0 || x >= MAPSIZE || y < 0 || y >= MAPSIZE){return false;}
  return (self->map[x][y] == 0);
}

//Indique que la case correspondant aux coordonnées passées en paramètres
//est un morceau de bateau détruit
void map_set_destroyed(struct map *self, int x, int y)
{
  self->map[x][y] = DESTROYED;
}

//Indique que la case correspondant aux coordonnées passées en paramètres
//est une mine
void map_set_mine(struct map *self, int x, int y)
{
  self->map[x][y] = MINE;
}
