#include "command.h"

#include <string.h>

void sequence_create(struct sequence *self)
{
  self->first = self->current = NULL;
};

void sequence_add_back(struct sequence *self, enum action action, int x, int y)
{
  struct sequence_node *curr = self->first;
  struct sequence_node *new = malloc(sizeof (struct sequence_node));
  new->target = malloc(sizeof(struct coord));
  coord_set(new->target, x, y);
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

//TODO Ajouter code devant chaque sortie d'erreur pour grep

void process(struct sequence *sequence, struct position_info *info, struct map *map, char buffer[BUFSIZE])
{
  if (sequence->current == NULL){sequence->current = sequence->first;}
  if (info->coord->y - info->N < 0){info->N = -1;}
  if (info->coord->x + info->E > 9){info->E = -1;}
  if (info->coord->y + info->S > 9){info->S = -1;}
  if (info->coord->x - info->W < 0){info->W = -1;}
  if (!map_shootable(map, info->coord->x, info->coord->y - info->N)){fprintf(stderr, "interruption recherche nord \n");info->N = -1;}
  if (!map_shootable(map, info->coord->x, info->coord->y + info->S)){fprintf(stderr, "interruption recherche sud  \n");info->S = -1;}
  if (!map_shootable(map, info->coord->x - info->E, info->coord->y)){fprintf(stderr, "interruption recherche est  \n");info->E = -1;}
  if (!map_shootable(map, info->coord->x + info->W, info->coord->y)){fprintf(stderr, "interruption recherche ouest\n");info->W = -1;}
  if (info->N == -1 && info->S == -1 && info->E == -1 && info->W == -1)
  {
    position_info_init(info);
    fprintf(stderr, "Fin de procédure de destruction\n");
  }
//TODO Véfifier efficacité map_shootable

  if (info->coord->x == -1 && info->coord->y == -1)
  {
    switch (sequence->current->action)
    {
      case SHOOT:
      {
        printf("SHOOT\n");
        fprintf(stderr, "SHOOT ");
        send_coord(sequence->current->target);
        fgets(buffer, BUFSIZE, stdin);
        fprintf(stderr, "%s", buffer);
        if (strcmp(buffer, "MISS\n"))
        {
          coord_set(info->coord, sequence->current->target->x, sequence->current->target->y);
          info->center_shot = true;
          fprintf(stderr, "Démarrage de la procédure de destruction\n");
        }
        sequence->current = sequence->current->next;
      }
      break;

      case POLL:
      {
        printf("POLL\n");
        fprintf(stderr, "POLL ");
        send_coord(sequence->current->target);
        fgets(buffer, BUFSIZE, stdin);
        fprintf(stderr, "%s", buffer);
        if (strcmp(buffer ,"EMPTY\n"))
        {
          fgets(buffer, BUFSIZE, stdin);
          fprintf(stderr, "%s", buffer);
          coord_set(info->coord, (int) buffer[0] - 'A', (int) buffer[1] - '0');
          info->center_shot = false;
          fprintf(stderr, "Démarrage de la procédure de destruction\n");
        }
        else
        {
          sequence->current = sequence->current->next;
        }
      }
      break;

      case MOVE :
      {
        printf("MOVE\n");
        fprintf(stderr, "MOVE ");
        send_coord(sequence->current->target);
        sequence->current = sequence->current->next;
      }
      break;
    }

  }
  else
  {
    if (info->N + info->S + info->W + info->E == -4){fprintf(stderr, "=======\n" );}

    fprintf(stderr, "%d %d %d %d\n",info->N, info->S, info->E, info->W);
    if (!info->center_shot)
    {
      printf("SHOOT\n");
      send_coord(info->coord);
      info->center_shot = true;
      fgets(buffer, BUFSIZE, stdin);
      fprintf(stderr, "%s", buffer);
    }

    else if (info->N > -1)
    {
      printf("SHOOT\n");
      send_coord_relative(info->coord, 0, -info->N);
      fgets(buffer, BUFSIZE, stdin);
      fprintf(stderr, "%s", buffer);
      if (!strcmp(buffer, "HIT\n"))
      {
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
      printf("SHOOT\n");
      send_coord_relative(info->coord, +info->E, 0);
      fgets(buffer, BUFSIZE, stdin);
      fprintf(stderr, "%s", buffer);
      if (!strcmp(buffer, "HIT\n"))
      {
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
      printf("SHOOT\n");
      send_coord_relative(info->coord, 0, +info->S);
      fgets(buffer, BUFSIZE, stdin);
      fprintf(stderr, "%s", buffer);
      if (!strcmp(buffer, "HIT\n"))
      {
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
      printf("SHOOT\n");
      send_coord_relative(info->coord, -info->W, 0);
      fgets(buffer, BUFSIZE, stdin);
      fprintf(stderr, "%s", buffer);
      if (!strcmp(buffer, "HIT\n"))
      {
        info->W++;
      }
      else
      {
        info->W = -1;
      }
    }
    else
    {
      fprintf(stderr, "Error\n");
      printf("SHOOT\n");
      printf("A0\n");
    }
  }

  fprintf(stderr, "Informations de l'ennemi : \n" );
  fgets(buffer, BUFSIZE, stdin);
  fprintf(stderr, "%s", buffer);
  if (strcmp(buffer, "NOTHING\n"))
  {
    fgets(buffer, BUFSIZE, stdin);
    fprintf(stderr, "%s", buffer);
  }
}
