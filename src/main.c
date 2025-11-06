#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "inventory.h"
#include "utils.h"

/*
 * ============================================================================
 * FUNÇÕES HANDLER - Padrão de Design para Separação de Responsabilidades
 * ============================================================================
 * Cada handler encapsula a lógica de uma operação do menu, facilitando
 * manutenção e testes. O switch-case no main fica limpo e legível.
 */

static int get_challenge_level() {
    printf("\nEscolha o nível do desafio:\n1. Novato 2. Aventureiro 3. Mestre: ");
    int level = read_int_safe();

    if (level < 1 || level > 3) {
        printf("Nível inválido, iniciando como Novato (1).\n");
        level = 1;
    }

    return level;
}

static void show_main_menu(int level) {
    printf("\n===== MENU INVENTÁRIO (Nível: %d) =====\n", level);
    printf("1. Adicionar item\n");
    printf("2. Listar itens\n");
    printf("3. Remover item (por Nome)\n");

    // Funcionalidades desbloqueadas por nível
    if (level >= 2) printf("4. Buscar item (sequencial)\n");
    if (level == 3) {
        printf("6. Ordenar inventário\n");
        printf("7. Buscar item (binária)\n");
    }
    printf("0. Sair\nOpção: ");
}

// Gerencia estado da ordenação após adição de item
static void handle_add_item(Item *inv, int *used, int level, SortCriterion *sorted) {
    if (add_item(inv, used, level)) {
        *sorted = SORT_NONE;  // Adicionar novo item invalida a ordenação existente
    }
}

// Gerencia estado da ordenação após remoção de item
static void handle_remove_item(Item *inv, int *used, SortCriterion *sorted) {
    if (remove_item_by_name(inv, used)) {
        *sorted = SORT_NONE;  // Remover item invalida a ordenação existente
    }
}

// Busca sequencial O(n) - disponível a partir do nível 2
static void handle_search_seq(Item *inv, int used) {
    char search_name[ITEM_NAME_LEN];
    printf("Nome do item para buscar: ");
    read_str_safe(search_name, ITEM_NAME_LEN);
    search_item_by_name(inv, used, search_name);
}

// Atualiza o critério de ordenação atual do inventário
static void handle_sort_menu(Item *inv, int used, SortCriterion *sorted) {
    printf("Informe critério: 1=Nome, 2=Tipo, 3=Prioridade: ");
    int crit_int = read_int_safe();

    if (crit_int >= 1 && crit_int <= 3) {
        SortCriterion crit = (SortCriterion)crit_int;
        sort_inventory(inv, used, crit);
        *sorted = crit;  // Mantém rastreamento do estado de ordenação
    } else {
        printf("Critério inválido!\n");
    }
}

// Busca binária O(log n) - requer ordenação prévia por nome
static void handle_binary_search(Item *inv, int used, SortCriterion sorted) {
    // Pré-condição: array deve estar ordenado por nome
    if (sorted != SORT_NAME) {
        printf("\n[ERRO] Só é possível busca binária se o inventário estiver ordenado por NOME.\n");
        printf("Use a opção 6 para ordenar por Nome primeiro.\n");
        return;
    }

    char search_name[ITEM_NAME_LEN];
    printf("Nome do item para busca binária: ");
    read_str_safe(search_name, ITEM_NAME_LEN);
    binary_search_by_name(inv, used, search_name);
}

/*
 * ============================================================================
 * FUNÇÃO PRINCIPAL - Loop de Evento Baseado em Menu
 * ============================================================================
 */
int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // Estado da aplicação
    Item inventory[INVENTORY_SIZE];
    int used = 0;
    SortCriterion sortedCriterion = SORT_NONE;  // Rastreamento de ordenação
    int running = 1;
    int level = get_challenge_level();

    // Loop principal - padrão Event Loop
    while (running) {
        show_main_menu(level);
        int opt = read_int_safe();

        switch (opt) {
            case 1:
                handle_add_item(inventory, &used, level, &sortedCriterion);
                break;
            case 2:
                list_items(inventory, used);
                break;
            case 3:
                handle_remove_item(inventory, &used, &sortedCriterion);
                break;
            case 4:
                // Controle de acesso por nível
                if (level >= 2) handle_search_seq(inventory, used);
                else printf("Opção inválida para este nível.\n");
                break;
            case 5:
                // Opção descontinuada - mantida para compatibilidade
                printf("Opção inválida. Use '1' para adicionar.\n");
                break;
            case 6:
                if (level == 3) handle_sort_menu(inventory, used, &sortedCriterion);
                else printf("Opção inválida para este nível.\n");
                break;
            case 7:
                if (level == 3) handle_binary_search(inventory, used, sortedCriterion);
                else printf("Opção inválida para este nível.\n");
                break;
            case 0:
                running = 0;
                printf("Saindo... Até a próxima!\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    }

    return 0;
}
