#ifndef INTEL_H
#define  INTEL_H

#include "intel.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAPSIZE 10
#define MINE 50
#define BUFSIZE 256


struct coord
{
  int x;
  int y;
};

struct map
{
  int map[MAPSIZE][MAPSIZE];
};

struct position_info
{
  struct coord *coord;
  int N;
  int S;
  int E;
  int W;
  bool center_shot;

};

void map_create(struct map *self);
void set_mine(struct map *self, int x, int y);
void set_coord(struct coord *self, int x, int y);
void set_mine(struct map *self, int x, int y);
void position_info_create(struct position_info *self);
void position_info_init(struct position_info *self);


#endif
