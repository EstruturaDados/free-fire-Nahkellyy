#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#define MAX_ITENS 10

// -----------------------------------------------------------
// Struct Item: representa um item da mochila
// -----------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
int buscarItem(Item mochila[], int total, char nomeBuscado[]);

int main() {
    Item mochila[MAX_ITENS];  
    int totalItens = 0;       
    int opcao;

    do {
        printf("\n===== SISTEMA DE INVENTÁRIO DA ILHA =====\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // limpa buffer do ENTER

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;

            case 2:
                removerItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;

            case 3:
                listarItens(mochila, totalItens);
                break;

            case 4: {
                char nomePesquisa[30];
                printf("Digite o nome do item que deseja buscar: ");
                fgets(nomePesquisa, sizeof(nomePesquisa), stdin);
                nomePesquisa[strcspn(nomePesquisa, "\n")] = '\0';

                int pos = buscarItem(mochila, totalItens, nomePesquisa);
                if (pos != -1) {
                    printf("\nItem encontrado!\n");
                    printf("Nome: %s\n", mochila[pos].nome);
                    printf("Tipo: %s\n", mochila[pos].tipo);
                    printf("Quantidade: %d\n", mochila[pos].quantidade);
                } else {
                    printf("\nItem não encontrado.\n");
                }
                break;
            }

            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
// inserirItem(): cadastra um novo item na mochila
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\nA mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n=== Inserir Novo Item ===\n");

    printf("Nome do item: ");
    fgets(mochila[*total].nome, sizeof(mochila[*total].nome), stdin);
    mochila[*total].nome[strcspn(mochila[*total].nome, "\n")] = '\0';

    printf("Tipo do item (arma, munição, cura): ");
    fgets(mochila[*total].tipo, sizeof(mochila[*total].tipo), stdin);
    mochila[*total].tipo[strcspn(mochila[*total].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    getchar();

    (*total)++;

    printf("\nItem inserido com sucesso!\n");
}
// removerItem(): exclui item pelo nome 
void removerItem(Item mochila[], int *total) {
    char nomeRemover[30];
    printf("\n=== Remover Item ===\n");
    printf("Digite o nome do item a remover: ");

    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int pos = buscarItem(mochila, *total, nomeRemover);

    if (pos == -1) {
        printf("Item não encontrado!\n");
        return;
    }

    // Desloca itens para preencher o vazio
    for (int i = pos; i < *total - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*total)--;

    printf("Item removido com sucesso!\n");
}
// listarItens(): mostra os itens cadastrados
void listarItens(Item mochila[], int total) {
    printf("\n===== Itens na Mochila (%d/%d) =====\n", total, MAX_ITENS);

    if (total == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}
// buscarItem(): faz busca sequencial por nome
int buscarItem(Item mochila[], int total, char nomeBuscado[]) {
    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBuscado) == 0) {
            return i;
        }
    }
    return -1;
}


// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
