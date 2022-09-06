#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct celula Celula;

struct celula{
  Arv* info;
  Celula* prox;
};

struct lista{
  Celula* primeiro;
  Celula* ultimo;
}; 


Lista* lista_cria(){
  Lista* lista = (Lista*)calloc(1, sizeof(Lista));
  return lista;
}


void lista_insereNoFinal(Arv* a, Lista* lista){
  Celula* celula_t = (Celula*)calloc(1, sizeof(Celula));
  celula_t->info = a;
  celula_t->prox = NULL;

  //lista vazia
  if(lista->primeiro == NULL && lista->ultimo == NULL){
    lista->primeiro = celula_t;
    lista->ultimo = celula_t;
    return ;
  }
  //lista com uma ou mais
  lista->ultimo->prox = celula_t;
  lista->ultimo = celula_t;
  return ;
}


void lista_retira(Lista* lista, int posicao){
  Celula* celula_aux;
  Celula* celula_aux_ant;
  celula_aux = lista->primeiro;
  
  if(posicao == 0){
    lista_retiraPrimeiro(lista);
    return ;
  }
    
  for(int i = 0; i < posicao ; i++){
    if( celula_aux->prox != NULL ) {
      celula_aux_ant = celula_aux;
      celula_aux = celula_aux->prox;
    }
  }
  
  if(celula_aux != NULL ){
    celula_aux_ant->prox = celula_aux->prox;
    free(celula_aux);
  }
  return ;
}


void lista_exibe( Lista* lista ){
    
  //caso1: lista vazia
  if(lista->primeiro == NULL && lista->ultimo == NULL){
  printf("\nLista vazia\n");
  return ;
  }
  //caso2: lista nao vazia
  Celula* celula_aux;
  celula_aux = lista->primeiro;
  printf("\n");
  while(celula_aux != NULL){
    arv_exibe(celula_aux->info);
    printf("\n");
    celula_aux = celula_aux->prox;
  }
  printf("\n");
  return ;
}


int lista_ehVazia(Lista* lista){
  if(lista->primeiro == NULL){
    return 1;
  }
  return 0;
}


Arv* lista_retiraPrimeiro(Lista* lista){
  //lista vazia 
  if(lista_ehVazia(lista)){
    return NULL;
  }
  Arv* a = lista->primeiro->info;
  
  //lista tem so um elemento 
  if(lista->primeiro == lista->ultimo){
    free(lista->primeiro);
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    return a;
  }
  //mais de um elemento
  Celula* celula_aux = lista->primeiro;
  lista->primeiro = lista->primeiro->prox;
  free(celula_aux);   
  return a;
}


Arv* lista_retiraUltimo(Lista* lista){
  //lista vazia 
  if(lista_ehVazia(lista)){
    return NULL;
  }
  Arv* a = lista->ultimo->info;
  //lista tem so um elemento 
  if(lista->primeiro == lista->ultimo){
    free(lista->ultimo);
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    return a;
  }

  //mais de um
  Celula* celula_aux = lista->primeiro;

  while(celula_aux->prox != lista->ultimo || celula_aux->prox != NULL){
    celula_aux = celula_aux->prox;
  }
  if(celula_aux->prox == lista->ultimo){
   celula_aux->prox = NULL;
   free(lista->ultimo);
   lista->ultimo = celula_aux;
  }
  return a;
}


void lista_libera(Lista* lista){

  if(lista_ehVazia(lista)) return ;

  Celula* celula_aux1 = lista->primeiro;
  Celula* celula_aux2 = lista->primeiro;
  
  while(celula_aux1 != NULL){
    celula_aux2 = celula_aux1->prox;
    free(celula_aux1);
    celula_aux1 = celula_aux2;
  }

  lista->primeiro = NULL;
  lista->ultimo = NULL;
  free(lista);
  return ;
}


void lista_ordena(Lista* lista){
  if(lista_ehVazia(lista)) return ;

  Celula* aux1 = lista->primeiro;
  Celula* aux2 = lista->primeiro;
  
  while(aux1 != NULL){
    aux2 = aux1;
    while(aux2 != NULL){
      if(_lista_EhParaTrocar( aux1->info, aux2->info )){
        Arv* a = aux2->info;
        aux2->info = aux1->info;
        aux1->info = a;
      }

      aux2 = aux2->prox;
    }

    aux1 = aux1->prox;
  }
}


int _lista_EhParaTrocar(Arv* a,Arv* b){
  if(arv_retornaFreq(a) > arv_retornaFreq(b)){
    return 1;
  }
  else{
    return 0;
  }
}


Arv* lista_retornaPrimArv( Lista *l ){
  if(!lista_ehVazia(l)) {
    return l->primeiro->info;
  }
  return NULL;
}


int lista_temSoUmaCel(Lista* l){
  if(l->primeiro == l->ultimo){
    return 1;
  }

  return 0;
}


