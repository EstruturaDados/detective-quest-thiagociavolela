/*
    ============================================================================
                        DETECTIVE QUEST – NÍVEL MESTRE
            Hash Table de Suspeitos com Lista Encadeada de Pistas
    ============================================================================
    
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 5

// -----------------------------------------------------------------------------
// STRUCT DE LISTA DE PISTAS
// -----------------------------------------------------------------------------
typedef struct NoPista {
    char texto[80];
    struct NoPista* prox;
} NoPista;

// -----------------------------------------------------------------------------
// STRUCT DO SUSPEITO
// -----------------------------------------------------------------------------
typedef struct Suspeito {
    char nome[40];
    int contador;
    NoPista* pistas;
    struct Suspeito* prox;  // lista encadeada para colisões
} Suspeito;

// -----------------------------------------------------------------------------
// HASH
// -----------------------------------------------------------------------------
int funcaoHash(const char* nome) {
    return (nome[0] % TAM_HASH);
}

Suspeito* criarSuspeito(const char* nome) {
    Suspeito* s = (Suspeito*)malloc(sizeof(Suspeito));
    strcpy(s->nome, nome);
    s->contador = 0;
    s->pistas = NULL;
    s->prox = NULL;
    return s;
}

void inserirPistaHash(Suspeito* tabela[], const char* suspeito, const char* pista) {
    int indice = funcaoHash(suspeito);

    Suspeito* atual = tabela[indice];
    Suspeito* anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, suspeito) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        atual = criarSuspeito(suspeito);
        if (anterior == NULL)
            tabela[indice] = atual;
        else
            anterior->prox = atual;
    }

    NoPista* nova = (NoPista*)malloc(sizeof(NoPista));
    strcpy(nova->texto, pista);
    nova->prox = atual->pistas;
    atual->pistas = nova;

    atual->contador++;
}

void listarAssociacoes(Suspeito* tabela[]) {
    printf("\n===== SUSPEITOS E PISTAS =====\n");

    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito* s = tabela[i];

        while (s) {
            printf("\nSuspeito: %s (%d pistas)\n", s->nome, s->contador);

            NoPista* p = s->pistas;
            while (p) {
                printf(" - %s\n", p->texto);
                p = p->prox;
            }

            s = s->prox;
        }
    }
}

void suspeitoMaisProvavel(Suspeito* tabela[]) {
    Suspeito* maior = NULL;

    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito* s = tabela[i];
        while (s) {
            if (maior == NULL || s->contador > maior->contador)
                maior = s;
            s = s->prox;
        }
    }

    if (maior)
        printf("\n🎯 Suspeito mais provável: %s (%d pistas)\n",
               maior->nome, maior->contador);
    else
        printf("\nNenhuma pista registrada.\n");
}

// -----------------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------------
int main() {
    printf("\n===== DETECTIVE QUEST – NÍVEL MESTRE =====\n");

    Suspeito* tabela[TAM_HASH] = {0};

    inserirPistaHash(tabela, "Sr. Black", "Pegadas suspeitas");
    inserirPistaHash(tabela, "Sra. White", "Livro rasgado");
    inserirPistaHash(tabela, "Sr. Black", "Tinta no chão");
    inserirPistaHash(tabela, "Coronel Mustard", "Arma enferrujada");

    listarAssociacoes(tabela);
    suspeitoMaisProvavel(tabela);

    return 0;
}
