#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da lista duplamente encadeada
typedef struct No {
    int valor;
    struct No *anterior;
    struct No *proximo;
} No;

// Estrutura da lista
typedef struct {
    No *inicio;
    No *fim;
    int tamanho;
} Lista;

// Protótipos das funções
Lista* criar_lista();
void liberar_lista(Lista *lista);
void inserir_inicio(Lista *lista, int valor);
void inserir_fim(Lista *lista, int valor);
void inserir_posicao(Lista *lista, int valor, int posicao);
void remover_posicao(Lista *lista, int posicao);
int buscar_valor(Lista *lista, int valor);
void listar_elementos(Lista *lista);
void menu();

// Função principal
int main() {
    Lista *lista = criar_lista();  // Retorna uma lista vazia se não houver problema na alocação dinâmica.
    int opcao, valor, posicao, resultado;

    do {
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Digite o valor a ser inserido no início: ");
                scanf("%d", &valor);
                inserir_inicio(lista, valor);
                break;

            case 2:
                printf("Digite o valor a ser inserido no fim: ");
                scanf("%d", &valor);
                inserir_fim(lista, valor);
                break;

            case 3:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                printf("Digite a posição (início = 1); (fim = %d): ", lista->tamanho + 1);
                scanf("%d", &posicao);
                inserir_posicao(lista, valor, posicao);
                break;

            case 4:
                printf("Digite a posição a ser removida (inicio = 1); (fim = %d): ", lista->tamanho);
                scanf("%d", &posicao);
                remover_posicao(lista, posicao);
                break;

            case 5:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                resultado = buscar_valor(lista, valor);
                if (resultado == -1) {
                    printf("Valor %d não encontrado na lista.\n", valor);
                } else {
                    printf("Valor %d encontrado na posicao %d.\n", valor, resultado);
                }
                break;

            case 6:
                listar_elementos(lista);
                break;

            case 0:
                printf("Encerrando programa...\n");
                break;

            default:
                printf("Opção invalida!\n");
        }

        printf("\n");
    } while(opcao != 0);  // Fim do bloco "do ... while".

    liberar_lista(lista);
    return 0;
} // Fim da função principal, main().

// Cria uma nova lista vazia
Lista* criar_lista() {
    Lista *lista = (Lista*)malloc(sizeof(Lista));
    if (lista == NULL) {
        printf("Erro ao alocar memória para a lista!\n");
        exit(1);
    }
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
    return lista;
} // Fim da função criar_lista().

// Libera toda a memória alocada para a lista
void liberar_lista(Lista *lista) {
    No *atual = lista->inicio;
    No *proximo;

    while (atual != NULL) {  // desaloca da memória todos o nós da lista.
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    free(lista);  // Desaloca a lista da memória.
}

// Insere um nó no início da lista
void inserir_inicio(Lista *lista, int valor) {
    No *novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("Erro ao alocar memória para o novo nó!\n");
        return;
    }

    novo_no->valor = valor;
    novo_no->anterior = NULL;
    novo_no->proximo = lista->inicio;

    if (lista->inicio == NULL) {
        // Lista vazia
        lista->inicio = novo_no;
        lista->fim = novo_no;
    } else {  // Lista cheia
        lista->inicio->anterior = novo_no;
        lista->inicio = novo_no;
    }

    lista->tamanho++;
    printf("Valor %d inserido no início da lista.\n", valor);
}  // Fim da função inserir_inicio().

// Insere um nó no final da lista
void inserir_fim(Lista *lista, int valor) {
    No *novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("Erro ao alocar memória para o novo nó!\n");
        return;
    }

    novo_no->valor = valor;
    novo_no->proximo = NULL;
    novo_no->anterior = lista->fim;

    if (lista->fim == NULL) {
        // Lista vazia
        lista->inicio = novo_no;
        lista->fim = novo_no;
    } else {
        lista->fim->proximo = novo_no;
        lista->fim = novo_no;
    }

    lista->tamanho++;
    printf("O valor %d foi inserido no fim da lista.\n", valor);
}  // Fim da função inserir_fim().

// Insere um nó em uma posição específica
void inserir_posicao(Lista *lista, int valor, int posicao) {
    if (posicao < 1 || posicao > lista->tamanho + 1) {
        printf("Posicao inválida! A lista tem %d elementos.\n", lista->tamanho);
        return;
    }

    if (posicao == 1) {
        inserir_inicio(lista, valor);
        return;
    }

    if (posicao == lista->tamanho + 1) {
        inserir_fim(lista, valor);
        return;
    }

    No *novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("Erro ao alocar memória para o novo nó!\n");
        return;
    }

    novo_no->valor = valor;

    // Encontrar a posição para inserção
    No *atual = lista->inicio;
    for (int i = 1; i < posicao - 1; i++) {
        atual = atual->proximo;
    }

    // Inserir o novo nó
    novo_no->proximo = atual->proximo;
    novo_no->anterior = atual;
    atual->proximo->anterior = novo_no;
    atual->proximo = novo_no;

    lista->tamanho++;
    printf("O valor %d foi inserido na posicao %d.\n", valor, posicao);
}  // Fim da função inserir_posicao().

// Remove um nó de uma posição específica
void remover_posicao(Lista *lista, int posicao) {
    if (lista->inicio == NULL) {
        printf("A lista está vazia! Não há nó para remover.\n");
        return;
    }

    if (posicao < 1 || posicao > lista->tamanho) {
        printf("Posicao inválida! A lista tem %d elementos.\n", lista->tamanho);
        return;
    }

    No *no_remover;

    if (posicao == 1) {
        // Remover do início
        no_remover = lista->inicio;
        lista->inicio = lista->inicio->proximo;

        if (lista->inicio != NULL) {
            lista->inicio->anterior = NULL;
        } else {
            lista->fim = NULL; // Lista ficou vazia
        }
    } else if (posicao == lista->tamanho) {
        // Remover do fim
        no_remover = lista->fim;
        lista->fim = lista->fim->anterior;
        lista->fim->proximo = NULL;
    } else {
        // Remover do meio
        no_remover = lista->inicio;
        for (int i = 1; i < posicao; i++) {
            no_remover = no_remover->proximo;
        }

        no_remover->anterior->proximo = no_remover->proximo;
        no_remover->proximo->anterior = no_remover->anterior;
    }

    int valor_removido = no_remover->valor;
    free(no_remover);
    lista->tamanho--;

    printf("O valor %d foi removido da posicao %d.\n", valor_removido, posicao);
}  // Fim da função remover_posicao().

// Busca um valor na lista e retorna sua posição
int buscar_valor(Lista *lista, int valor) {
    No *atual = lista->inicio;
    int posicao = 1;

    while (atual != NULL) {
        if (atual->valor == valor) {
            return posicao;
        }
        atual = atual->proximo;
        posicao++;
    }

    return -1; // Valor não encontrado
}  // Fim da função buscar_valor().

// Lista todos os elementos da lista com seus ponteiros
void listar_elementos(Lista *lista) {
    if (lista->inicio == NULL) {
        printf("A lista está vazia!\n");
        return;
    }

    printf("Lista (%d elementos):\n", lista->tamanho);
    printf("Pos | Valor | Anterior | Próximo\n");
    printf("----|-------|----------|--------\n");

    No *atual = lista->inicio;
    int posicao = 1;

    while (atual != NULL) {
        printf("%3d | %5d | ", posicao, atual->valor);

        if (atual->anterior == NULL) {
            printf("   NULL   | ");
        } else {
            printf("  %5d  | ", atual->anterior->valor);
        }

        if (atual->proximo == NULL) {
            printf("  NULL\n");
        } else {
            printf(" %5d\n", atual->proximo->valor);
        }

        atual = atual->proximo;
        posicao++;
    }
}

// Menu de opções
void menu() {
    printf("\n=== LISTA DUPLAMENTE ENCADEADA ===\n");
    printf("1. Inserir no início\n");
    printf("2. Inserir no fim\n");
    printf("3. Inserir em posição específica\n");
    printf("4. Remover de posição específica\n");
    printf("5. Buscar valor\n");
    printf("6. Listar elementos\n");
    printf("0. Sair\n");
}