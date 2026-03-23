#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 50

typedef struct tipoFilme {
    char titulo[TAM];
    int anoProducao;
    float bilheteria;
    struct tipoFilme *prox; //aponta para o próximo tipoFilme
    struct tipoFilme *ant; //aponta para o anterior tipoFilme
} TFilme;

typedef struct tipoLista {
     TFilme *inicio;
     TFilme *fim;
    int total;
} TLista;

TLista lista;

void inicializa(TLista *L);
void insere(TLista *L);
void listar(TLista L);
int menu();
void exclui(TLista *L);
void reordenarPorAno(TLista *L);


int main(){
    int opcao;

    inicializa(&lista);

    do{
        opcao = menu();

        switch(opcao){
            case 1:  insere(&lista); break;
            case 2: listar(lista); break; 
            case 3: exclui(&lista); break;       
        }//switch
        
    } while (opcao != 0);

}

//=========| Funçõesd |=================================================================

void inicializa(TLista *L){
    L->inicio = NULL;
    L->fim = NULL;
    L->total = 0;
}

//=======================================================================================
void insere(TLista *L){
    TFilme *novo, *atual, *anterior = NULL;
    int inserido = 0;

    novo = (TFilme *)malloc(sizeof(TFilme));

    printf("\n\n\t=====| INSERE FILME |=====\n\n");
    printf("Informe TITULO: ");
    while (getchar() != '\n');
    fgets(novo->titulo, TAM, stdin);

    printf("\n\nANO DE PRODUCAO: ");
    scanf("%d", &novo->anoProducao);

    printf("\n\nBILHETERIA: ");
    scanf("%f", &novo->bilheteria);

    novo->prox = NULL;
    novo->ant = NULL;

    atual = L->inicio;
    while( atual != NULL){
        if(strcmp(atual->titulo, novo->titulo) == 1){
            novo->prox = atual;
            novo->ant = atual->ant;
            atual->ant = novo;

            if (anterior != NULL) anterior->prox = novo;

            if(atual == L->inicio){
                //insere novo registro no início da Lista.
                L->inicio = novo;
            }

            inserido = 1;
            break;
        }

        anterior = atual;
        atual = atual->prox;
    }//while

    if(L->inicio == NULL){
        //Lista encontra-se VAZIA: inserir como primeiro registro
        L->inicio = novo;
        L->fim = novo;
    } else if (inserido == 0){
        //inserir novo registro no fim da Lista;
        TFilme *ultimo = L->fim;
        ultimo->prox = novo;
        novo->ant = ultimo;
        L->fim = novo;
    }//if


    L->total++;

}
//========================================================================================

void listar(TLista L) {
    TFilme *atual = L.inicio;
    int cont = 0;
    printf("\n\n\t=====| Lista de Filmes |=====\n\n");

    while(atual != NULL){
        printf("\t(%d) - %s (%d) %.2f\n", ++cont, atual->titulo, atual->anoProducao, atual->bilheteria);
        atual = atual->prox;
    }//while

    printf("\n\n");
    getchar();
}

//===========================================================================================
int menu(){
    int opcao;

    printf("\n\n\n\t\t=====| MENU |======\n\n");
    printf("\t0 - Sair (Encerrar Aplicacao)\n\n");
    printf("\t1 - INSERIR Filme.\n");
    printf("\t2 - LISTAR Filmes.\n");
    printf("\t3 - EXCLUIR Filme Especifico.\n");
    printf("\t4 - REORDENAR Filme por ANO DE PRODUCAO.\n");

    printf("\n\tInforme OPCAO desejada: ");
    scanf("%d", &opcao);

    if((opcao < 0) || (opcao > 4)){
        printf("\n\n\tERRO: Opcao INVALIDA! Tente Novamente.\n\n");
        getchar();
    }//if

    return opcao;
}

//=============================================================================================
void exclui(TLista *L){
    TFilme *atual, *anterior;
     char titulo[TAM];

    printf("\n\n\t\t=====| EXCLUSAO |======\n\n");
    printf("\tInforme TITULO a ser EXCLUIDO: ");
    while (getchar() != '\n');
    fgets(titulo, TAM, stdin);


    atual = L->inicio;
    anterior = NULL;

    while(atual != NULL){
        if(strcmp(atual->titulo, titulo) == 0){
            //Filme encontrado

            if(anterior == NULL) {
                //atual é o primeiro FILME da Lista
                L->inicio = atual->prox;
                if (L->inicio != NULL) {
                    L->inicio->ant = NULL;
                }

            } else {
                anterior->prox = atual->prox; //atual é o FILME do meio ou do fim da Lista
                
                if (atual->prox != NULL) {
                    atual->prox->ant = anterior;
                }
            }//if

            free(atual);

            if(anterior != NULL){
                if(anterior->prox == NULL){
                   L->fim = anterior;
                }
            }

            if(L->inicio == NULL){
                L->fim = NULL;
            }//if

            L->total--;

            break;
        }

        anterior = atual;
        atual = atual->prox;

    }//while

    printf("\n\n\tFILME excluido com SUCESSO!\n\n");
    getchar();

}
//=============================================================================================
void reordenarPorAno(TLista *L){
    TFilme *fixo, *movel;

    char titulo[TAM];
    int ano;
    float bilheteria;

    printf("\n\n\t\t=====| REORDENAR POR ANO DE PRODUCAO |=====\n\n");

    fixo = L->inicio;

    while(fixo != NULL){
        printf("\n\tFIXANDO: %s (%d).", fixo->titulo, fixo->anoProducao);

        movel = fixo->prox;
        while(movel != NULL){
            printf("\n\tCOMPARANDO com %s (%d) ... ", movel->titulo, movel->anoProducao);

            if(movel->anoProducao < fixo->anoProducao){
                printf("TROCAR.");
                strcpy(titulo, fixo->titulo);
                ano = fixo->anoProducao;
                bilheteria = fixo->bilheteria;

                strcpy(fixo->titulo, movel->titulo);
                fixo->anoProducao = movel->anoProducao;
                fixo->bilheteria = movel->bilheteria;

                strcpy(movel->titulo, titulo);
                movel->anoProducao = ano;
                movel->bilheteria = bilheteria;

                printf("\n\tNOVO FIXO: %s (%d).", fixo->titulo, fixo->anoProducao);
            } else {
                printf("MANTER.");
            }

            movel = movel->prox;
        }
        fixo = fixo->prox;
    }

    printf("\n\n\t FIM da REORDENACAO ....");
}





