#include"arvore.h"
#include<stdlib.h>
#include<string.h>

struct arv{
    unsigned char letra;
    int freq;
    Arv* esq;
    Arv* dir;
};



Arv* arv_criavazia (void){
    return NULL;
}


Arv* arv_cria (unsigned char l,int freq, Arv* e, Arv* d){
    Arv* a = (Arv*)calloc(1,sizeof(Arv));
    a->dir = d;
    a->esq = e;
    a->letra = l;
    a->freq = freq;

    return a;
}


unsigned char arv_retornaLetra(Arv* a){
    return a->letra;
}


int arv_retornaFreq(Arv* a){
    return a->freq;
}


Arv* arv_libera (Arv* a){
    if(!arv_vazia(a)){
        arv_libera(a->esq);
        arv_libera(a->dir);
        free(a);
    }
    return NULL;
}


int arv_vazia (Arv* a){
    if(a == NULL) {
        return 1;
    }

    return 0;
}


int arv_pertence (Arv* a,unsigned char l){

    if(arv_vazia(a)){
        return 0;
    }
    else if(a->letra == l || arv_pertence(a->esq,l) ||arv_pertence(a->dir,l)) {
        return 1;
    }

    return 0;
}


void arv_exibe (Arv* a){
    printf("<");
    if(!arv_vazia(a)){
            printf("%c (%d):%d",a->letra, a->letra,a->freq);
        arv_exibe(a->esq);
        arv_exibe(a->dir);
    }
    printf(">");
}


int arv_folhas (Arv* a){
    int soma = 0;
    if(!arv_vazia(a)){
        soma += arv_folhas(a->esq);
        soma += arv_folhas(a->dir);
     
        if( arv_vazia(a->dir) && arv_vazia(a->esq) ){
            return (soma+1);
        }
    
        return soma;
    }
    else{
        return 0;
    }
}


int arv_altura (Arv* a){
    if(arv_vazia(a)){
        return 0;
    }
    else{
        int x = 0 , y = 0;
        x = arv_altura(a->esq);
        y = arv_altura(a->dir);
        if(x > y){
            return (x+1);
        }
        else{
            return (y+1);
        }
    }
}


int arv_ehFolha(Arv* a){
    if( arv_vazia(a->dir) && arv_vazia(a->esq) ){
        return 1;
    }
    else{
        return 0;
    }
}


Arv* arv_retornaNoDireita(Arv* a){
    return a->dir;
}


Arv* arv_retornaNoEsquerdo(Arv* a){
    return a->esq;
}
