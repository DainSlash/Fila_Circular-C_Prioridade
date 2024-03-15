#ifndef _FILA_H
#define _FILA_H
#define MAX_TAM 50

#include <stdbool.h>

typedef int t_data;

typedef struct{
	t_data itens[MAX_TAM];
	unsigned int start, end, size;
} queue;

void queue_init(queue *);
bool queue_empty(queue);
bool queue_full(queue);
int queue_insert_pos(queue, t_data);
bool queue_insert(queue *, t_data);
bool queue_add(queue *, t_data);
bool queue_remove(queue *, t_data *);
void queue_print(queue);

#endif
