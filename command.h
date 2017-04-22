#ifndef COMMAND_H
#define  COMMAND_H

#include "command.h"
#include "intel.h"
#include <stdio.h>
#include <stdlib.h>


enum action
{
  SHOOT,
  POLL,
  MOVE
};

struct sequence_node
{
  enum action action;
  struct coord *target;
  struct sequence_node *next;
};

struct sequence
{
  struct sequence_node *first;
};

void sequence_create(struct sequence *self);
void sequence_add_back(struct sequence *self, enum action action, int x, int y);
void send_coord_explicit(int x, int y);
void send_coord(struct coord *self);
void send_coord_relative(struct coord *self, int x, int y);
void set_mine(struct map *self, int x, int y);
void process(struct sequence_node **sequence, struct position_info *info, char buffer[BUFSIZE]);

#endif
