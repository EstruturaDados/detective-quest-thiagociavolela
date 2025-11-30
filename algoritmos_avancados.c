/*
    ============================================================================
                        DETECTIVE QUEST – NÍVEL NOVATO
                        Mapa da Mansão com Árvore Binária
    ============================================================================

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------------------------------------------------------
// STRUCT DA SALA
// -----------------------------------------------------------------------------
typedef struct Sala {
    char nome[40];
    struct Sala *esq;
    struct Sala *dir;
} Sala;

// -----------------------------------------------------------------------------
// FUNÇÕES
// -----------------------------------------------------------------------------
Sala* criarSala(const char* nome) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esq = NULL;
    nova->dir = NULL;
    return nova;
}

void explorarSalas(Sala* salaAtual) {
    char opcao;

    do {
        printf("\nVocê está em: %s\n", salaAtual->nome);
        printf("Para onde deseja ir?\n");
        printf("e - Ir para a esquerda\n");
        printf("d - Ir para a direita\n");
        printf("s - Sair da mansão\n");
        printf("Escolha: ");
        scanf(" %c", &opcao);

        if (opcao == 'e' && salaAtual->esq != NULL) {
            salaAtual = salaAtual->esq;
        }
        else if (opcao == 'd' && salaAtual->dir != NULL) {
            salaAtual = salaAtual->dir;
        }
        else if (opcao == 's') {
            printf("\nExploração encerrada.\n");
            return;
        }
        else {
            printf("Caminho inexistente!\n");
        }

    } while (1);
}

// -----------------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------------
int main() {

    // Criação fixa da árvore de salas
    Sala* hall = criarSala("Hall de Entrada");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* cozinha = criarSala("Cozinha");
    Sala* sotao = criarSala("Sótão");
    Sala* jardim = criarSala("Jardim");

    hall->esq = biblioteca;
    hall->dir = cozinha;
    biblioteca->esq = sotao;
    biblioteca->dir = jardim;

    printf("\n===== DETECTIVE QUEST – NÍVEL NOVATO =====\n");
    explorarSalas(hall);

    return 0;
}
