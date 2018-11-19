#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb_privado.h"


// FUNCOES COMPLEMENTARES
void destroi_pos_ordem(node_t *no){
	if(no == NULL) return;
	
	destroi_pos_ordem(no->esquerda);
	destroi_pos_ordem(no->direita);
	free(no);
	no = NULL;
}


node_t *remove_no(node_t *atual){
	node_t *no1, *no2;
	if(atual->esquerda == NULL){
		no2 = atual->direita;
		free(atual);
		return no2;
	}
	no1 = atual;
	no2 = atual->esquerda;
	while(no2->direita != NULL){
		no1 = no2;
		no2 = no2->direita;
	}
	if(no1 != atual){
		no1->direita = no2->esquerda;
		no2->esquerda = atual->esquerda;
	}
	no2->direita = atual->direita;
	free(atual);
	return no2;
}


abb_h altura_arvore(node_t *no){
	if(!no) return -1;
	int esq, dir;
	
	esq = altura_arvore(no->esquerda);
	dir = altura_arvore(no->direita);
	
	if(esq > dir)
		altura = esq+1;
	else 
		altura = dir+1;
}
// TERMINO DAS FUNCOES COMPLENTARES

//coloque aqui a implementacao das operacoes do TDA generico arvore binaria de busca 

/**
 * Criar árvore binária de busca e a inicializa como arvore vazia.
 *
 * Pre: nenhuma
 * Pos: Retorna um ponteiro para uma arvore vazia se houver memoria disponivel
 *
 * @param imprimir um ponteiro para uma funcao de impressao dos dados armazenados dentro da arvore.
 * @param destruir fornece uma maneira de liberar dinamicamente os dados dentro da celula quando "abb_destroi" eh chamada.
 * Para uma arvore onde os dados nao devem ser liberados, esse ponteiro deve ser NULL.
 * @param compara  um ponteiro para funcao de comparacao entre dois dados armazenados na lista.
 * Deve retornar -1 se o primeiro eh menor que o segundo, 0 se forem iguais, ou 1 se o primeiro for maior que o segundo
 *
 * @return um ponteiro para uma arvore nova
 */
abb_t* abb_criar (void (*imprimir)(const void *data),void (*destruir)(void **data),int (*compara)(const void *key1, const void* key2)){
	if(!compara) return NULL; 
	abb_t *abb = (abb_t*)malloc(sizeof(abb_t));
	if(!abb) return NULL;
	abb->tamanho = 0;
	abb->raiz->esquerda = NULL;
	abb->raiz->direita = NULL;
	abb->destroi = destruir;
	abb->compara = compara;
	abb->imprime = imprimir;
	return abb;
}

/**
 * Criar árvore binária de busca e a inicializa com os valores do vetor.
 *
 * Pre: nenhuma
 * Pos: Retorna um ponteiro para uma arvore com os valores se houver memoria disponivel
 *
 * @param imprimir um ponteiro para uma funcao de impressao dos dados armazenados dentro da arvore.
 * @param destruir fornece uma maneira de liberar dinamicamente os dados dentro da celula quando "abb_destroi" eh chamada.
 * Para uma arvore onde os dados nao devem ser liberados, esse ponteiro deve ser NULL.
 * @param compara  um ponteiro para funcao de comparacao entre dois dados armazenados na lista.
 * Deve retornar -1 se o primeiro eh menor que o segundo, 0 se forem iguais, ou 1 se o primeiro for maior que o segundo
 *
 * @return um ponteiro para uma arvore nova
 */
abb_t* abb_criar_de_vetor (void* vetor, int tamanho_vetor, int tamanho_elemento,void (*imprimir)(const void *data),void (*destruir)(void **data),int (*compara)(const void *key1, const void* key2)){
	if(tamanho_vetor < 0 || !vetor || !imprimir || !destruir || !compara) return NULL;
	abb_t *abb = abb_criar(imprimir, destruir, compara);
	if(!abb) return NULL;
	
	int i = 0;
	
	for(; i<tamanho_vetor; i++)
	{	
		abb_insere(abb, vetor + i*tamanho_elemento);
	}
	
	return abb; 
	
}
/**
 * Destrói a árvore binária de busca.
 * Nenhuma operação é permitida após a função, a nao ser que a árvore seja criada novamente.
 * Destrói todos os elementos armazenados na árvore se o ponteiro "destruir" for válido.
 *
 * Pre: "arv" deve ser uma árvore válida criada previamente atraves da função de criação
 * Pos: os recursos da árvore foram liberados com sucesso e a ela tornou-se nula.
 *
 * @param arv ponteiro de ponterio para uma arvore válida a ser destruída.
 * @return SUCESSO se conseguiu destruir toda a árvore.
 *         INVALIDO se a árvore não for válida.
 */
codigo_erro abb_destroi    (abb_t** arv){
	if(!arv || !(*arv)->destroi)  return INVALIDO;
	node_t *atual = (*arv)->raiz;
	
	destroi_pos_ordem(atual);
	free(*arv);
	return SUCESSO;
}
	
	

/**
 * Verifica se a árvore está vazia.
 *
 * @param arv arvore para avaliação
 * @return  verdadeiro para árvore vazia
 *          falso caso contrario
 */
bool        abb_vazia       (const abb_t* arv){
	if(!arv) return NULL;
	if(arv->tamanho == 0) return 1;
	return 0; 
	
}

/**
 * Consulta o tamnho da árvore, em quantidades de itens inseridos e não repetidos.
 *
 * @param arv arvore para consulta.
 * @return número de itens e não repetidos na árvore, caso árvore for invalida retorna o valor -1.
 *
 */
long        abb_tamanho     (const abb_t* arv){
	if(!arv) return -1;
}

/**
 * Insere um item na árvore.
 *
 * @param arv arvore para a operacao
 * @param data dado compativel com a arvore para ser inserido
 * @return SUCESSO se conseguiu inserir na árvore.
 *         INVALIDO se a árvore não for válida.
 *         ESTADO_INVALIDO se a arvore nao possuir uma funcao de comparacao
 *         DUPLICADO se o dado a ser inserido já está presenta na árvore
 *
 */
codigo_erro abb_insere      (abb_t* arv, void* data){
	if(!arv) return INVALIDO;
	
	if(arv->compara == NULL) return ESTADO_INVALIDO;
	
	node_t *novo = (node_t*)malloc(sizeof(node_t));
	if(!novo) return INVALIDO; 
	
	novo->info = data;
	novo->esquerda = NULL;
	novo->direita = NULL;
	
	if(arv->raiz == NULL){
		arv->raiz = novo;	
	}
	else{
		node_t *atual = arv->raiz;
		node_t *ant = NULL;
		while(atual != NULL){
			ant = atual;
			
			if(arv->compara(data, atual->info) == 0){
				free(novo);
				return DUPLICADO; //sao iguais;
			}

			if(arv->compara(data, atual->info) <0)
				atual = atual->esquerda;
			else
				atual = atual->direita;
		}
		if(arv->compara(data, ant->info) >0)
			ant->direita = novo;
		else 
			ant->esquerda = novo;
	}
	arv->tamanho++;
	return SUCESSO;	
}

/**
 * Remove um item da árvore (se ele existir).
 *
 * @param arv arvore para a operacao
 * @param data informacao para remover
 * @return SUCESSO se existir o valor e remover ele
 * 		   UNDER_FLOW se arvore invalida ou vazia
 * 		   VALOR_INVALIDO se data nao existir
 * 		   INVALIDO para outra condicao encontrada
 */
codigo_erro abb_remove      (abb_t* arv, const void* data){
	if(!arv) return UNDER_FLOW;
	if(!data) return VALOR_INVALIDO;
	if(arv->raiz == NULL) return INVALIDO;
	node_t *atual = arv->raiz;
	node_t *ant = NULL;
	while(atual != NULL){
		if(arv->compara(data, atual->info) == 0){
			if(atual == arv->raiz)
			    arv->raiz = remove_no(atual);
			else{
			    
			     if(ant->direita == atual)
				    ant->direita = remove_no(atual);
		    	else 
		    	    ant->esquerda = remove_no(atual);
		    	    
			}
			return SUCESSO;
		}
		ant = atual;
		if(arv->compara(data, atual->info) < 0)
			atual = atual->direita;
		else 
		    atual = atual->esquerda;
		    
		return SUCESSO;
	}
}
			
	
		
	

/**
 * Consulta se um determinado valor pertence a arvore.
 *
 * @param arv arvore para a operacao
 * @param info valor a buscar
 *
 * @return verdadeiro para valor na arvore e falso caso contrario.
 */
bool        abb_busca_bin   (const abb_t* arv, void* info){
	if(!arv || !info) return 0;
	node_t *no;
	no = arv->raiz;
	if(!no) return 0;
	if(no->info == info) return 1;
	else{
		if(no->info > info)
			return abb_esq(no->esquerda);
		else
			return abb_dir(no->direita);
	}
}
	

/**
 * Consulta o no raiz da arvore.
 *
 * @param arv arvore para a operacao
 *
 * @return no raiz da arvore ou NULL caso arvore invalida ou vazia
 */
const node_t*     abb_raiz(const abb_t* arv){
	if(!arv || abb_vazia(arv) == 1) return NULL;
	return arv->raiz;
}

/**
 * Consulta a subarvore esquerda da arvore.
 *
 * @param raiz raiz da arvore para a operacao
 *
 * @return no raiz da subarvore esquerda do no raiz ou NULL caso a subarvore nao exista
 */
const node_t*     abb_esq(const node_t* raiz){
	if(!raiz) return NULL;
	
	if(raiz->esquerda == NULL) return NULL;
	return raiz->esquerda;
	
}

/**
 * Consulta a subarvore direita da arvore.
 *
 * @param raiz raiz da arvore para a operacao
 *
 * @return no raiz da subarvore direita do no raiz ou NULL caso a subarvore nao exista
 */
const node_t*     abb_dir(const node_t* raiz){
	if(!raiz) return NULL;
	
	if(raiz->direita == NULL) return NULL;
	return raiz->direita;
}

/**
 * Consulta a informacao contida no no.
 *
 * @param node no para a operacao
 *
 * @return informacao contida no no, NULL caso no seja invalido.
 */
const void* 	  abb_info(const node_t* node){
	if(!node || !node->info) return NULL;
	return node->info;
	
}
/**
 * Consulta se um determinado no e folha.
 * 
 * @param node no para a operacao
 *
 * @return verdadeiro se no for folha e falso caso contrario.
 *
 */
bool        abb_node_ehfolha(const node_t* node){
	if(!node) return 0;
	if(node->esquerda == NULL && node->direita == NULL) return 1;
	
}

/**
 * Consulta a altura da arvore
 *
 * @param arv arvore para a operacao
 * @param altura ponteiro para armazenar a altura da arvore como resultado da funcao
 *
 * @return SUCESSO se o calculo for realizado com sucesso e o valor estara armazenado no parametor altura
 * 		   INVALIDO caso a arvore seja invalida
 */
codigo_erro abb_altura(abb_t* arv, unsigned long *altura){
	if(!arv || abb_vazia(arv) == 1) return INVALIDO;
	*altura = altura_arvore(arv->raiz);
	
	return SUCESSO;
}




