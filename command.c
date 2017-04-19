#include "command.h"

void sequence_create(struct sequence *self)
{
  self->first = NULL;
};

void sequence_add_back(struct sequence *self, enum action action, int x, int y)
{
  struct sequence_node *curr = self->first;
  struct sequence_node *new = malloc(sizeof (struct sequence_node));
  new->target = malloc(sizeof(struct coord));
  new->target->x = x;
  new->target->y = y;

  if (curr == NULL)
  {
    self->first = new;
    return;
  }
  while (curr->next != NULL)
  {
    curr = curr->next;
  }
  curr->next = new;
}

void send_coord_explicit(int x, int y)
{
  char abscisse = 'A' + x;
  printf("%c%d\n", abscisse, y);
}

void send_coord(struct coord *self)
{
  send_coord_explicit(self->x, self->y);
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

void process(struct sequence_node *sequence)
{
  switch (sequence->action)
  {
    case SHOOT: printf("SHOOT\n");
      break;
    case POLL: printf("POLL\n");
      break;
    case MOVE : printf("MOVE\n");
      break;
  }
  send_coord(sequence->target);
  sequence = sequence ->next;
  //TODO Récupérer résultat
  //TODO Prévoir prochains coups
}
