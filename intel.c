#include "intel.h"
#include "command.h"

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
