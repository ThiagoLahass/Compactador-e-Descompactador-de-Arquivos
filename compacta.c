#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"
#include "arvore.h"
#include "bitmap.h"

/* 
 * Função que le a frequencia de cada caractere
 * Pré-condição: arquivo de entrada valido
 * Pós-condição: frequencia lida
 * Input: File de entrada e o vetor de frequncia
 * Output: Nenhum
 */
void Le_frequencia_caracteres( FILE* arquivo_entrada, int vetor_frequencia[]);

/* 
 * Função que cria a lista de arvores a partir do vetor de frequencia
 * Pré-condição: vetor valido
 * Pós-condição: lista criada
 * Input: Vetor de frequencia dos caracteres
 * Output: Lista com as arvores de cada caractere
 */
Lista* Cria_lista_arvores( int vet[]);

/* 
 * Função que implementa o codigo de Huffmann
 * Pré-condição: lista valida
 * Pós-condição: arvore de Huffmann criada
 * Input: Lista de arvores
 * Output: Arvore otima criada
 */
Arv* Cria_arvore_otima ( Lista* lista );

/* 
 * Função que cria a tabela com os codigos em binario de cada caractere
 * Pré-condição: arvore valida
 * Pós-condição: tabela criada e retornada
 * Input: Ponteiro para a arvore otima
 * Output: tabela de codificacao(char**)
 */
char** Cria_tabela_codificacao( Arv* arvore_otima );

/* 
 * Função auxiliar na criacao da tabela de codificacao e que se utiliza de recursao
 * Pré-condição: tabela e arvores validas
 * Pós-condição: Nenhuma
 * Input: Tabela(char**), arvore, string contendo o codigo do caractere, e o tamanho maximo das codificacoes
 * Output: Nenhum
 */
void Recursao_para_criar_tabela( char** tabela, Arv* arv, char *codificacao, int tam_max );

/* 
 * Função que imprime a tabela de codificacao
 * Pré-condição: tabela valida
 * Pós-condição: Tabela impressa na saida padrao
 * Input: Tabela (char**)
 * Output: Nenhum
 */
void Imprime_tabela_codificacao(char** d);

/* 
 * Função que escreve os dados codificados no novo arquivo
 * Pré-condição: arquivos de entrada e saida validos, tabela de codificacao valida, e vetor valido
 * Pós-condição: Arquivo compactado gerado
 * Input: Files de entrada e saida, tabela de codificacao, e vetor de frequencia
 * Output: Nenhum
 */
void Gera_arquivo_de_saida ( FILE* arquivo_saida, FILE* arquivo_entrada, Arv* arvore_otima, char** tabela_codificacao, int vet_freq[] ); 

int main ( int argc, char * argv[] ) {

    // printf("%s\n", argv[1]);
    int vetor_frequencia[256], i = 0, j = 0;
    FILE* arquivo_entrada;
    Lista* lista_arv;
    Arv* arvore_otima;
    char **tabela_codificacao;
    char nome_arq_saida[50], nome_arq_entrada[50];
    char extensao[10];

    strcpy( nome_arq_entrada, argv[1]);
    //abre o arquivo de entrada para leitura
    arquivo_entrada = fopen( nome_arq_entrada, "r");
    if( !arquivo_entrada ){
        printf("Nao foi possivel ler o arquivo %s ! \n", argv[1] );
        return 1;
    }

    
    //cria nome do arquivo de saida
    sscanf(argv[1], "%[^.]%s", nome_arq_saida, extensao );
    strcat(nome_arq_saida, ".comp");

    FILE* arquivo_saida;
    //abre o arquivo de saida para escrita em binario
    arquivo_saida = fopen( nome_arq_saida, "wb");
    if( !arquivo_saida ){
        printf("Nao foi possivel abrir o arquivo %s ! \n", nome_arq_saida );
        return 1;
    }


    //verifica a frequencia de cada caractere
    Le_frequencia_caracteres( arquivo_entrada, vetor_frequencia );

    // for( i = 0; i < 256; i++ ){
    //     if( vetor_frequencia[i] != 0 ){
    //         printf("vet[%3d] = %c -> %d\n", i, i, vetor_frequencia[i]);
    //     }  
    // }

    //escrever o  vetor de frequencia no arquivo de saida e a extensao do arquivo
    fwrite( vetor_frequencia, sizeof(int), 256, arquivo_saida);
    fwrite( extensao, sizeof(char), 10, arquivo_saida);

    //cria a lista inicial com as arvores de cada caractere
    lista_arv = Cria_lista_arvores( vetor_frequencia );

    // lista_exibe( lista_arv );

    //utiliza o codigo de huffman para criar a arvore otima
    arvore_otima = Cria_arvore_otima( lista_arv );

    // printf("Arvore otima:\n");
    // arv_exibe( arvore_otima );

    //cria a tabela de codificacao
    tabela_codificacao = Cria_tabela_codificacao( arvore_otima );

    // Imprime_tabela_codificacao ( tabela_codificacao );

    //gera o arquivo compactado
    Gera_arquivo_de_saida( arquivo_saida, arquivo_entrada, arvore_otima, tabela_codificacao, vetor_frequencia );

    
    fclose( arquivo_entrada );
    fclose( arquivo_saida   );
    

    //libera toda a memoria alocada
    arv_libera( arvore_otima );
    lista_libera( lista_arv );
    for( i = 0; i < 256; i++ ) {
        free( tabela_codificacao[i]);
    }
    free( tabela_codificacao );

    return 0;
}


void Le_frequencia_caracteres( FILE* arquivo_entrada, int vetor_frequencia[]){
    
    int i = 0;
    for( i = 0; i < 256; i++ ){
        vetor_frequencia[i] = 0;        //seta como zero todas as posições do vetor
    }
    
    while( 1 ) {
        i = fgetc( arquivo_entrada);
        // printf("%d: %c\n", i, i);
        if( i != EOF )
            vetor_frequencia[i]++;
        else 
            break;
    }
}


Lista* Cria_lista_arvores( int vet[]) {
    int i = 0;
    Arv* a;
    Lista* lista;
    lista = lista_cria();

    for( i = 0; i < 256; i++ ){
        if( vet[i] != 0 ) {
            a = arv_cria(i, vet[i], NULL, NULL );
            lista_insereNoFinal( a, lista );
        }
    }

    lista_ordena( lista );

    return lista;
}


Arv* Cria_arvore_otima ( Lista* lista ) {
    Arv* T1, *T2, *Tr;
    int i = 0;
    while( ! lista_temSoUmaCel( lista ) ) {
        T1 = lista_retiraPrimeiro( lista );
        T2 = lista_retiraPrimeiro( lista );
        Tr = arv_cria( '+', ( arv_retornaFreq(T1) + arv_retornaFreq(T2) ) , T1, T2);
        lista_insereNoFinal( Tr, lista );
        lista_ordena(lista);
    }

    return lista_retornaPrimArv( lista );
}


char** Cria_tabela_codificacao( Arv* arvore_otima ) {
    char** tabela = (char**) calloc(256, sizeof( char*));
    int i = 0;
    for( i = 0; i < 256; i++ ) {
        tabela[i] = (char*) calloc( 1 + arv_altura(arvore_otima),sizeof(char)); //tamanho maximo das codificacoes é a altura da arvore + 1 (devido ao \0)
    }

    Recursao_para_criar_tabela( tabela, arvore_otima, "", 1 + arv_altura(arvore_otima));

    return tabela;
}


void Recursao_para_criar_tabela( char** tabela, Arv* arv, char *codificacao, int tam_max ) {
    if(arv_ehFolha( arv )){
        strcpy(tabela[arv_retornaLetra(arv)], codificacao);
    }
    else{
        char caminhoEsq[tam_max];
        char caminhoDir[tam_max];

        strcpy(caminhoDir, codificacao);
        strcat(caminhoDir, "1");

        strcpy(caminhoEsq, codificacao);
        strcat(caminhoEsq, "0");

        Recursao_para_criar_tabela( tabela, arv_retornaNoDireita(arv), caminhoDir, tam_max );
        Recursao_para_criar_tabela( tabela, arv_retornaNoEsquerdo(arv), caminhoEsq, tam_max);
    }
}

void Imprime_tabela_codificacao (char** d){
    int i;
    printf("\n\nTabela:\n");
    for(i=0;i<256;i++){
        printf("letra:%c -> caminho:%s\n",i,d[i]);
    }
    printf("\n");
}


void Gera_arquivo_de_saida ( FILE* arquivo_saida, FILE* arquivo_entrada, Arv* arvore_otima, char** tabela_codificacao, int vet_freq[] ){
    int i = 0, j = 0, tamanho_bitmap = 0;
    bitmap* bitmap;
    
    for( i = 0; i < 256; i++ ) {
        tamanho_bitmap += strlen(tabela_codificacao[i]) * vet_freq[i];
    }

    bitmap = bitmapInit( tamanho_bitmap );

    rewind(arquivo_entrada);

    int c = 0;
    while( 1 ){
        c = fgetc(arquivo_entrada);
        if( c == EOF ) break;
        j = strlen( tabela_codificacao[c] );
        for( i = 0; i < j; i++ ){
            bitmapAppendLeastSignificantBit(bitmap, tabela_codificacao[c][i]);
        }
    }
  
    // printf("\n\n'%s'", bitmapGetContents(bitmap));
    fwrite(bitmapGetContents(bitmap),sizeof(unsigned char),((tamanho_bitmap+7)/8),arquivo_saida);
    
    bitmapLibera( bitmap );
}