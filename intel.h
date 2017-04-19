#ifndef INTEL_H
#define  INTEL_H

#include "intel.h"

#include <stdio.h>
#include <stdlib.h>

#define MAPSIZE 10
#define MINE 50

struct coord
{
  int x;
  int y;
};

struct map
{
  int map[MAPSIZE][MAPSIZE];
};

void map_create(struct map *self);
void set_mine(struct map *self, int x, int y);
void set_coord(struct coord *self, int x, int y);
void set_mine(struct map *self, int x, int y);


#endif
