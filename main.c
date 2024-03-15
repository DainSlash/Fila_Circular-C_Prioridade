#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	int n, i;
	
	
	queue q, q2;
	queue_init(&q);
	queue_init(&q2);
	

	srand(408);	
	for(i=0;i<MAX_TAM;i++) queue_add(&q, rand()%100); //Adicionado de qualquer jeito
	for(i=0;i<MAX_TAM;i++) queue_insert(&q2, rand()%100); //Adicionado com prioridade do menor para o maior.
	printf("\nOrdem aleatoria: \n");
	queue_print(q);
	printf("\nOrdenada: \n");
	queue_print(q2);	
	return 0;
}
