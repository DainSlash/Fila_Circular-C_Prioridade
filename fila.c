#include "fila.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void queue_init(queue *q){
	q->start = q->end = q->size = 0;
}

bool queue_empty(queue q){
	return q.size == 0;
}

bool queue_full(queue q){
	return q.size == MAX_TAM;
}

bool queue_add(queue *q, t_data data){
	if(queue_full(*q)) return false;
	q->itens[q->end] = data;
	q->end = (q->end+1)%MAX_TAM;
	q->size++;
}

//funcao que vai realizar uma busca binaria O(logN) no vetor procurando a pos em que data pode ser inserida (evitando busca linear O(n)) 
int queue_insert_pos(queue q, t_data data){
	int imaginary_start = 0, imaginary_end = q.size-1, imaginary_mid; 
	
	
	//tratar os casos das pontas do vetor
	if(data <= q.itens[q.start]) return imaginary_start;
	if(data >= q.itens[q.end-1]) return imaginary_end+1;
	
	
	//realizar a busca binaria utilizando um indice imaginario para um vetor equivalente ao vetor real, e realiza uma busca binaria simples, porem ao inves de apenas procurar um elemento N, tambem procura a pos onde N eh:  X > N > Y
	while(imaginary_end >= imaginary_start){
		imaginary_mid = (imaginary_start + imaginary_end)/2;
		if((data != q.itens[(imaginary_mid+q.start)%MAX_TAM]) && !((data > q.itens[(imaginary_mid+q.start)%MAX_TAM]) && (data < q.itens[(imaginary_mid+q.start+1)%MAX_TAM]))){
			if(data > q.itens[(imaginary_mid+q.start)%MAX_TAM]) imaginary_start = (imaginary_mid+1)%MAX_TAM;
			else imaginary_end = (imaginary_mid-1)%MAX_TAM;
		}else{
		// >> IMPORTANTE <<, o retorno eh o da pos IMAGINARIA, sendo assim o retorno trata da pos NA FILA, e nao no vetor REAL da MEMORIA. Para conseguir o indice real, usa se imaginary_mid+q.start.
			return imaginary_mid+1 ;
		}
	}
	
	return -1;
}


bool queue_insert(queue *q, t_data data){
	if(queue_full(*q)) return false;
	if(queue_empty(*q)) return queue_add(q, data);

	int i, imaginary_pos = queue_insert_pos(*q, data), imaginary_start = 0, imaginary_end = q->size;
	
	
	if(abs(imaginary_pos-imaginary_start) <= abs(imaginary_pos-imaginary_end)){//se estiver mais proximo do inicio
		q->start = (q->start == 0) ? MAX_TAM-1 : q->start-1;
		//desolca o inicio para tras e puxa os elementos juntos ate pos, realizando o MININO de movimentos possivel, pior caso O(n/2)
		for(i=imaginary_start ; i <	 imaginary_pos ; i++) q->itens[(i+q->start)%MAX_TAM] = q->itens[((i+q->start+1)%MAX_TAM)];
	}else{//mais proximo do fim
		q->end = (q->end+1)%MAX_TAM;
		//desolca o final para frente e puxa os elementos juntos ate pos, realizando o MININO de movimentos possivel, pior caso O(n/2)
		for(i=imaginary_end ; i > imaginary_pos ; i--) q->itens[(i+q->start)%MAX_TAM] = q->itens[(i+q->start-1)%MAX_TAM];	
	}
	
	//finalmente insere o elemento na pos correta, connsiderando a pos REAL do vetor.
	q->itens[(imaginary_pos+q->start)%MAX_TAM] = data;
	q->size++;
}

bool queue_remove(queue *q, t_data * data){
	if(queue_empty(*q)) return false;
	*data = q->itens[q->start];
	q->start = (q->start+1)%MAX_TAM;
	q->size--;
}

void queue_print(queue q){
	int i, j;
	
	for(i = q.start, j=0 ; j < q.size ; j++, i++) printf("[%d]",q.itens[i%(MAX_TAM)]);

}
