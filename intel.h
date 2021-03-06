#ifndef INTEL_H
#define  INTEL_H

// #include "intel.h"

#include <stdbool.h>

#define MAPSIZE 10
#define BUFSIZE 256

#define VIDE 0
#define MINE 1
#define DESTROYED 2

struct coord
{
  int x;
  int y;
};

struct map
{
  int map[MAPSIZE][MAPSIZE];
};

struct info
{
  struct coord coord;
  int N;                //Nord
  int S;                //Sud
  int E;                //Est
  int W;                //Ouest
  bool center_shot;

};

void map_create(struct map *self);
void coord_set(struct coord *self, int x, int y);
void info_create(struct info *self);
void info_init(struct info *self);
bool map_shootable(struct map *self, int x, int y);
void map_set_destroyed(struct map *self, int x, int y);
void map_set_mine(struct map *self, int x, int y);


#endif
