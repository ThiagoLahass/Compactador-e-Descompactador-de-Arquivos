#include "arvore.h"

typedef struct lista Lista;

/* 
 * Função que aloca ponteiro para lista 
 * Pré-condição: Nenhum
 * Pós-condição: ponteiro para lista alocado 
 * Input: Nenhum
 * Output: Ponteiro para lista
 */
Lista* lista_cria();

/* 
 * Função que insere uma celula no final da lista 
 * Pré-condição: lista e árvore diferentes de NULL
 * Pós-condição: celula alocada, árvore atribuida a ela, e celula inserida ao final da lista 
 * Input: ponteiro para árvore e ponteiro para lista
 * Output: Nenhum
 */
void lista_insereNoFinal(Arv* a,Lista* lista);

/* 
 * Função que retira a celula da posição passada
 * Pré-condição: lista diferente de NULL e posição válida
 * Pós-condição: celula da posição da lista retirada  
 * Input: ponteiro para lista, posição da celula (int)
 * Output: Nenhum
 */
void lista_retira(Lista* lista, int posicao);

/* 
 * Função que imprime a lista  
 * Pré-condição: lista diferente de NULL
 * Pós-condição: lista imprimida 
 * Input: ponteiro para lista
 * Output: Nenhum
 */
void lista_exibe(Lista* lista);

/* 
 * Função que retorna se a lista é vazia (1) ou  não(0)
 * Pré-condição: lista diferente de NULL
 * Pós-condição: Nenhum 
 * Input: ponteiro para lista
 * Output: 1 para lista vazia e 0 para lista não vazia
 */
int lista_ehVazia(Lista* lista);

/* 
 * Função que retira a primeira celula da lista e retorna a árvore dessa celula
 * Pré-condição: lista diferente de NULL 
 * Pós-condição: celula desalocada e árvore retornada, lista atualizada, árvore não é desalocada, para arv só com unica celula a lista é liberada 
 * Input: ponteiro para lista
 * Output: ponteiro para árvore ou NULL em caso de lista vazia
 */
Arv* lista_retiraPrimeiro(Lista* lista);

/* 
 * Função que retira a ultima celula da lista e retorna a árvore dessa celula
 * Pré-condição: lista existente 
 * Pós-condição: celula desalocada e árvore retornada, lista atualizada, árvore não é desalocada 
 * Input: ponteiro para lista
 * Output: ponteiro para árvore ou NULL em caso de lista vazia
 */
Arv* lista_retiraUltimo(Lista* lista);

/* 
 * Função que libera lista (sem liberar as arvores)
 * Pré-condição: lista válida
 * Pós-condição: celulas desalocadas, lista desalocada, árvore não é desalocada 
 * Input: ponteiro para lista
 * Output: Nenhum
 */
void lista_libera(Lista* lista);

/* 
 * Função que ordena lista da menor para maior frequencia
 * Pré-condição: lista válida
 * Pós-condição: celulas ordenada, lista com posições atualizadas 
 * Input: ponteiro para lista
 * Output: Nenhum
 */
void lista_ordena(Lista* lista);

/* 
 * Função auxiliar para função ordena
 * Pré-condição: árvores existentes
 * Pós-condição: nenhuma 
 * Input: ponteiro para duas árvores
 * Output: 1 para frequência da (Arv a) maior que a freq da (Arv b) e 0 para o contrário
 */
int _lista_EhParaTrocar(Arv* a,Arv* b);

/* 
 * Função que verifica se a lista tem apenas uma celula
 * Pré-condição: lista válida
 * Pós-condição: nenhuma 
 * Input: ponteiro para lista
 * Output: 1 caso haja so uma celula na lista e 0 caso contrario
 */
int lista_temSoUmaCel(Lista* l);

/* 
 * Função que retorna a primeira arvore da lista
 * Pré-condição: lista válida
 * Pós-condição: nenhuma
 * Input: ponteiro para lista
 * Output: ponteiro para arvore (arv*)
 */
Arv* lista_retornaPrimArv(Lista *l);


