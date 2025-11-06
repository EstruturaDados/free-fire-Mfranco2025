#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "inventory.h"
#include "utils.h"
#include "validation.h"

/*
 * ============================================================================
 * FUNÇÕES PRIVADAS (STATIC) - Encapsulamento no Nível de Arquivo
 * ============================================================================
 * Funções static são visíveis apenas neste arquivo, promovendo encapsulamento.
 * Não precisam estar no .h pois são detalhes de implementação.
 */

/**
 * Busca linear case-insensitive pelo nome do item
 * Complexidade: O(n) onde n = número de itens no inventário
 *
 * @return Índice do item encontrado ou -1 se não existir
 */
static int find_item_by_name_index(const Item *inventory, int used, const char *name) {
    // Normalização: converte busca para uppercase para comparação case-insensitive
    char name_upper[ITEM_NAME_LEN];
    strncpy(name_upper, name, ITEM_NAME_LEN-1);
    name_upper[ITEM_NAME_LEN-1] = '\0';
    str_to_upper(name_upper);

    for (int i = 0; i < used; i++) {
        char item_name_upper[ITEM_NAME_LEN];
        strncpy(item_name_upper, inventory[i].name, ITEM_NAME_LEN-1);
        item_name_upper[ITEM_NAME_LEN-1] = '\0';
        str_to_upper(item_name_upper);

        if (strcmp(item_name_upper, name_upper) == 0) {
            return i;
        }
    }

    return -1;
}

/*
 * ============================================================================
 * FUNÇÕES PÚBLICAS - Interface Definida no Header
 * ============================================================================
 */

/**
 * Adiciona item ao inventário com validação em múltiplas camadas
 * A validação é progressiva: capacidade -> formato -> valores
 */
int add_item(Item *inventory, int *used, int level) {
    // Validação de capacidade
    if (*used >= INVENTORY_SIZE) {
        printf("Inventário cheio! Remova itens para adicionar mais.\n");
        return 0;
    }

    Item *newItem = &inventory[*used];
    printf("\n--- Cadastro de novo item ---");

    // Validação de formato do nome usando módulo externo
    while (1) {
        printf("\nNome do item: ");
        read_str_safe(newItem->name, ITEM_NAME_LEN);

        if (is_valid_name_format(newItem->name)) {
            break;
        } else {
            printf("[ERRO] Nome inválido! Deve começar com letra (sem números ou símbolos).\n");
        }
    }

    // Validação de formato do tipo (reutiliza mesma função)
    while (1) {
        printf("Tipo do item: ");
        read_str_safe(newItem->type, ITEM_TYPE_LEN);

        if (is_valid_name_format(newItem->type)) {
            break;
        } else {
            printf("[ERRO] Tipo inválido! Deve começar com letra (sem números ou símbolos).\n");
        }
    }

    printf("Quantidade: ");
    newItem->quantity = read_int_safe();

    // Campo prioridade disponível apenas no nível Mestre
    if (level == 3) {
        printf("Prioridade (1-5): ");
        int pr = read_int_safe();
        if (pr < 1 || pr > 5) {
            printf("Prioridade inválida, definindo como 1.\n");
            pr = 1;
        }
        newItem->priority = pr;
    } else {
        newItem->priority = 0;
    }

    (*used)++;
    printf("Item cadastrado!\n");
    return 1;
}

/**
 * Lista todos os itens com formatação adaptativa
 * Exibe coluna de prioridade apenas se algum item tiver prioridade > 0
 */
void list_items(const Item *inventory, int used) {
    printf("\n======== INVENTÁRIO DA MOCHILA (Itens: %d/%d) ========\n", used, INVENTORY_SIZE);

    // Detecta se algum item tem prioridade definida
    int has_priority = 0;
    for(int i=0; i<used; i++)
        if (inventory[i].priority > 0) has_priority = 1;

    // Formatação condicional baseada em dados presentes
    if(has_priority) {
        printf("%-3s | %-18s | %-12s | %-5s | %s\n", "ID", "Nome", "Tipo", "Qtde", "Prio");
        printf("----------------------------------------------------------\n");
        for (int i = 0; i < used; i++) {
            printf("%-3d | %-18s | %-12s | %-5d | %d\n",
                   i+1, inventory[i].name, inventory[i].type,
                   inventory[i].quantity, inventory[i].priority);
        }
    } else {
        printf("%-3s | %-18s | %-12s | %-8s\n", "ID", "Nome", "Tipo", "Qtde");
        printf("-----------------------------------------------------\n");
        for (int i = 0; i < used; i++) {
            printf("%-3d | %-18s | %-12s | %-8d\n",
                   i+1, inventory[i].name, inventory[i].type, inventory[i].quantity);
        }
    }
    printf("----------------------------------------------------------\n");
}

/**
 * Remove item por nome e reorganiza o array
 * Utiliza realocação por deslocamento - O(n) no pior caso
 */
int remove_item_by_name(Item *inventory, int *used) {
    if (*used == 0) {
        printf("Inventário vazio, nada para remover.\n");
        return 0;
    }

    char name_to_remove[ITEM_NAME_LEN];
    printf("Digite o NOME do item a remover: ");
    read_str_safe(name_to_remove, ITEM_NAME_LEN);

    int index = find_item_by_name_index(inventory, *used, name_to_remove);
    if (index == -1) {
        printf("Item '%s' não encontrado.\n", name_to_remove);
        return 0;
    }

    // Realocação: desloca elementos para preencher o espaço
    for (int i = index; i < *used - 1; i++) {
        inventory[i] = inventory[i + 1];
    }

    (*used)--;
    printf("Item '%s' removido com sucesso!\n", name_to_remove);
    return 1;
}

/**
 * Busca sequencial case-insensitive - O(n)
 * Adequada para arrays não ordenados
 */
void search_item_by_name(const Item *inventory, int used, const char *name) {
    int index = find_item_by_name_index(inventory, used, name);

    if (index != -1) {
        const Item *item = &inventory[index];
        printf("\nEncontrado! ID %d\n", index + 1);
        printf("Nome: %s | Tipo: %s | Qtde: %d | Prioridade: %d\n",
               item->name, item->type, item->quantity, item->priority);
    } else {
        printf("\nItem '%s' não encontrado no inventário.\n", name);
    }
}

/**
 * Insertion Sort com múltiplos critérios de ordenação
 * Complexidade: O(n²) - eficiente para arrays pequenos
 * Vantagens: estável, in-place, eficiente para dados quase ordenados
 *
 * @param crit Critério de ordenação (nome, tipo ou prioridade)
 */
void sort_inventory(Item *inventory, int used, SortCriterion crit) {
    int comparisons = 0;

    // Insertion Sort: insere cada elemento na posição correta do subarray ordenado
    for (int i = 1; i < used; i++) {
        Item temp = inventory[i];
        int j = i - 1;

        while (j >= 0) {
            int cmp = 0;
            comparisons++;

            // Estratégia de comparação baseada no critério
            if (crit == SORT_NAME) cmp = strcmp(inventory[j].name, temp.name);
            else if (crit == SORT_TYPE) cmp = strcmp(inventory[j].type, temp.type);
            else if (crit == SORT_PRIORITY) cmp = inventory[j].priority - temp.priority;

            if (cmp > 0) {
                inventory[j + 1] = inventory[j];
                j--;
            } else {
                break;
            }
        }
        inventory[j + 1] = temp;
    }

    printf("Inventário ordenado! Comparações realizadas: %d\n", comparisons);
}

/**
 * Binary Search (Busca Binária) - O(log n)
 * PRÉ-CONDIÇÃO: Array DEVE estar ordenado por nome
 *
 * Funciona dividindo o espaço de busca pela metade a cada iteração.
 * Muito mais eficiente que busca linear para arrays grandes.
 *
 * @return Índice do item encontrado ou -1 se não existir
 */
int binary_search_by_name(const Item *inventory, int used, const char *name) {
    int comparisons = 0;
    int left = 0, right = used - 1;

    // Normalização do termo de busca
    char target_upper[ITEM_NAME_LEN];
    strncpy(target_upper, name, ITEM_NAME_LEN-1);
    target_upper[ITEM_NAME_LEN-1] = '\0';
    str_to_upper(target_upper);

    while (left <= right) {
        int mid = left + (right - left) / 2;  // Previne overflow em (left+right)/2

        char mid_name_upper[ITEM_NAME_LEN];
        strncpy(mid_name_upper, inventory[mid].name, ITEM_NAME_LEN-1);
        mid_name_upper[ITEM_NAME_LEN-1] = '\0';
        str_to_upper(mid_name_upper);

        comparisons++;
        int cmp = strcmp(mid_name_upper, target_upper);

        if (cmp == 0) {
            printf("\nEncontrado com busca binária! ID %d. Comparações: %d\n",
                   mid + 1, comparisons);
            printf("Nome: %s | Tipo: %s | Qtde: %d | Prioridade: %d\n",
                   inventory[mid].name, inventory[mid].type,
                   inventory[mid].quantity, inventory[mid].priority);
            return mid;
        } else if (cmp < 0) {
            left = mid + 1;   // Buscar na metade direita
        } else {
            right = mid - 1;  // Buscar na metade esquerda
        }
    }

    printf("\nBusca binária: Item '%s' não encontrado. Comparações: %d\n", name, comparisons);
    return -1;
}
