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
  self->x = x;
  self->y = y;
}

void position_info_create(struct position_info *self)
{
  self->coord = malloc(sizeof(struct coord));
  position_info_init(self);
}

void position_info_init(struct position_info *self)
{
  self->N = self->E = self->W = self->S = 1;
  set_coord(self->coord, -1, -1);
  self->center_shot = false;
}
