/*
    ============================================================================
                        DETECTIVE QUEST – NÍVEL AVENTUREIRO
                    Árvore de Busca para Armazenar Pistas (BST)
    ============================================================================

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------------------------------------------------------
// STRUCT DA PISTA (BST)
// -----------------------------------------------------------------------------
typedef struct Pista {
    char texto[80];
    struct Pista* esq;
    struct Pista* dir;
} Pista;

// -----------------------------------------------------------------------------
// FUNÇÕES DE ARVORE BST
// -----------------------------------------------------------------------------
Pista* criarPista(const char* texto) {
    Pista* nova = (Pista*)malloc(sizeof(Pista));
    strcpy(nova->texto, texto);
    nova->esq = NULL;
    nova->dir = NULL;
    return nova;
}

Pista* inserirBST(Pista* raiz, const char* texto) {
    if (raiz == NULL)
        return criarPista(texto);

    if (strcmp(texto, raiz->texto) < 0)
        raiz->esq = inserirBST(raiz->esq, texto);
    else
        raiz->dir = inserirBST(raiz->dir, texto);

    return raiz;
}

void listarEmOrdem(Pista* raiz) {
    if (raiz == NULL) return;
    listarEmOrdem(raiz->esq);
    printf("- %s\n", raiz->texto);
    listarEmOrdem(raiz->dir);
}

// -----------------------------------------------------------------------------
// SALAS
// -----------------------------------------------------------------------------
typedef struct Sala {
    char nome[40];
    char pista[80];
    struct Sala *esq, *dir;
} Sala;

Sala* criarSala(const char* nome, const char* pista) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esq = nova->dir = NULL;
    return nova;
}

// -----------------------------------------------------------------------------
// EXPLORAÇÃO COLETANDO PISTAS
// -----------------------------------------------------------------------------
void explorar(Sala* salaAtual, Pista** arvorePistas) {
    char op;

    do {
        printf("\nVocê está em: %s", salaAtual->nome);

        if (strlen(salaAtual->pista) > 0) {
            printf("\nPista encontrada: %s\n", salaAtual->pista);
            *arvorePistas = inserirBST(*arvorePistas, salaAtual->pista);
        }

        printf("\ne - esquerda | d - direita | p - listar pistas | s - sair\n");
        printf("Escolha: ");
        scanf(" %c", &op);

        if (op == 'e' && salaAtual->esq) salaAtual = salaAtual->esq;
        else if (op == 'd' && salaAtual->dir) salaAtual = salaAtual->dir;
        else if (op == 'p') {
            printf("\n===== PISTAS COLETADAS =====\n");
            listarEmOrdem(*arvorePistas);
        }
        else if (op == 's') {
            printf("\nSaindo da exploração...\n");
            return;
        }
        else printf("Opção inválida!\n");

    } while (1);
}

// -----------------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------------
int main() {
    printf("\n===== DETECTIVE QUEST – NÍVEL AVENTUREIRO =====\n");

    Pista* arvorePistas = NULL;

    // Criar árvore de salas com pistas
    Sala* hall = criarSala("Hall de Entrada", "Pegadas suspeitas");
    Sala* biblioteca = criarSala("Biblioteca", "Livro rasgado encontrado");
    Sala* cozinha = criarSala("Cozinha", "");
    Sala* sotao = criarSala("Sótão", "Manchas de tinta no chão");

    hall->esq = biblioteca;
    hall->dir = cozinha;
    biblioteca->esq = sotao;

    explorar(hall, &arvorePistas);

    return 0;
}
