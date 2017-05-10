#include "command.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void sequence_create(struct sequence *self)
{
  self->first = self->current = NULL;
};

//Crée un nouvel élément à la fin de la séquence
//Complexité O(n)
void sequence_add_back(struct sequence *self, enum action action, int x, int y)
{
  struct sequence_node *curr = self->first;
  struct sequence_node *new = malloc(sizeof (struct sequence_node));
  assert(new != NULL);
  coord_set(&(new->target), x, y);
  new->action = action;
  new->next = NULL;

  if (curr == NULL)
  {
    self->first = new;
    self->current = self->first;
    return;
  }
  while (curr->next != NULL)
  {
    curr = curr->next;
  }
  curr->next = new;
}

void sequence_next(struct sequence *self)
{
  self->current = self->current->next;
  if (self->current == NULL)
  {
    self->current = self->first;
    fprintf(stderr, "Répétition de la séquence\n");
  }
}

void send_action(enum action action)
{
  switch (action) {
    case SHOOT :
    {
      printf("SHOOT\n");
      fprintf(stderr, "SHOOT\n");
    }
    break;
    case POLL :
    {
      printf("POLL\n");
      fprintf(stderr, "POLL\n");
    }
    break;
    case MOVE :
    {
      printf("MOVE\n");
      fprintf(stderr, "MOVE\n");
    }
    break;
  }
}

void send_coord_explicit(int x, int y)
{
  char abscisse = 'A' + x;
  printf("%c%d\n", abscisse, y);
  fprintf(stderr, "%c%d\n", abscisse, y);
}

void send_coord(struct coord *self)
{
  send_coord_explicit(self->x, self->y);
}

void send_coord_relative(struct coord *self, int x, int y)
{
  send_coord_explicit(self->x + x, self->y + y);
}

void set_mine(struct map *self, int x, int y)
{
  send_coord_explicit(x,y);
  map_set_mine(self, x, y);
}

/*
* Parcours la séquence pour rechercher des bateaux ennemis (phase de recherche)
* Pour chaque bateau ennemi repéré (par sonde ou par tir), parcours les cases voisines
* pour le détruire (phase de destruction)
* La séquence de recherche est supposée repérer l'ensemble des bateaux en une seule itération
* dans le cas où ceux ci ne bougent pas
*/
void process(struct sequence *sequence, struct info *info, struct map *map, char buffer[BUFSIZE])
{
  if (info->coord.y - info->N < 0){info->N = -1;}
  if (!map_shootable(map, info->coord.x, info->coord.y - info->N)){info->N = -1;}

  if (info->coord.x + info->E > 9){info->E = -1;}
  if (!map_shootable(map, info->coord.x + info->E, info->coord.y)){info->E = -1;}

  if (info->coord.y + info->S > 9){info->S = -1;}
  if (!map_shootable(map, info->coord.x, info->coord.y + info->S)){info->S = -1;}

  if (info->coord.x - info->W < 0){info->W = -1;}
  if (!map_shootable(map, info->coord.x - info->W, info->coord.y)){info->W = -1;}



  if (info->N + info->S + info->W + info->E == -4 && info->coord.x != -1)
  {
    info_init(info);
  }



  if (info->coord.x == -1 && info->coord.y == -1)
  {
    /*
    PHASE DE RECHERCHE
    */
    switch (sequence->current->action)
    {
      if (!map_shootable(map, sequence->current->target.x, sequence->current->target.y))
      {
        sequence_next(sequence);
        process(sequence, info, map, buffer);
      }

      case SHOOT:
      {
        send_action(SHOOT);
        send_coord(&(sequence->current->target));
        fgets(buffer, BUFSIZE, stdin);
        fprintf(stderr, "%s", buffer);
        if (strcmp(buffer, "MISS\n"))
        {
          coord_set(&(info->coord), sequence->current->target.x, sequence->current->target.y);
          info->center_shot = true;
          map_set_destroyed(map, info->coord.x, info->coord.y);
        }
        sequence_next(sequence);

      }
      break;

      case POLL:
      {
        send_action(POLL);
        send_coord(&(sequence->current->target));
        fgets(buffer, BUFSIZE, stdin);
        fprintf(stderr, "%s", buffer);
        if (strcmp(buffer ,"EMPTY\n"))
        {
          fgets(buffer, BUFSIZE, stdin);
          fprintf(stderr, "%s", buffer);
          info_init(info);
          coord_set(&(info->coord), (int) buffer[0] - 'A', (int) buffer[1] - '0');
          info->center_shot = false;
        }
        else
        {
          sequence_next(sequence);

        }
      }
      break;

      case MOVE :
      {
        send_action(MOVE);
        send_coord(&(sequence->current->target));
        sequence_next(sequence);

      }
      break;
    }

  }
  else
  {

    /*
    PHASE DE DESTRUCTION
    */
    if (!info->center_shot)
    {
      send_action(SHOOT);
      send_coord(&(info->coord));
      info->center_shot = true;
      fgets(buffer, BUFSIZE, stdin);
      fprintf(stderr, "%s", buffer);
      if (!strcmp(buffer, "HIT\n"))
      {
        map_set_destroyed(map, info->coord.x, info->coord.y);
      }
    }

    else if (info->N > -1)
    {
      send_action(SHOOT);
      send_coord_relative(&(info->coord), 0, -info->N);
      fgets(buffer, BUFSIZE, stdin);
      fprintf(stderr, "%s", buffer);
      if (!strcmp(buffer, "HIT\n"))
      {
        map_set_destroyed(map, info->coord.x, info->coord.y - info->N);
        info->N++;
        info->W = info->E = -1;
      }
      else
      {
        info->N = -1;
      }
    }
    else if (info->E > -1)
    {
      send_action(SHOOT);
      send_coord_relative(&(info->coord), +info->E, 0);
      fgets(buffer, BUFSIZE, stdin);
      fprintf(stderr, "%s", buffer);
      if (!strcmp(buffer, "HIT\n"))
      {
        map_set_destroyed(map, info->coord.x + info->E, info->coord.y);
        info->E++;
        info->N = info->S = -1;
      }
      else
      {
        info->E = -1;
      }
    }
    else if (info->S > -1)
    {
      send_action(SHOOT);
      send_coord_relative(&(info->coord), 0, +info->S);
      fgets(buffer, BUFSIZE, stdin);
      fprintf(stderr, "%s", buffer);
      if (!strcmp(buffer, "HIT\n"))
      {
        map_set_destroyed(map, info->coord.x, info->coord.y + info->S);
        info->S++;
        info->W = info->E = -1;
      }
      else
      {
        info->S = -1;
      }
    }
    else if (info->W > -1)
    {
      send_action(SHOOT);
      send_coord_relative(&(info->coord), -info->W, 0);
      fgets(buffer, BUFSIZE, stdin);
      fprintf(stderr, "%s", buffer);
      if (!strcmp(buffer, "HIT\n"))
      {
        map_set_destroyed(map, info->coord.x - info->W, info->coord.y);
        info->W++;
      }
      else
      {
        info->W = -1;
        info->N = info->S = -1;
      }
    }
  }

  fprintf(stderr, "Action ennemie : \n" );
  fgets(buffer, BUFSIZE, stdin);
  fprintf(stderr, "%s", buffer);
  if (strcmp(buffer, "NOTHING\n"))
  {
    fgets(buffer, BUFSIZE, stdin);
    fprintf(stderr, "%s", buffer);
  }
}
