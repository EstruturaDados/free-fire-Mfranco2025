#ifndef INVENTORY_H
#define INVENTORY_H

// Constantes de configuração do sistema
#define INVENTORY_SIZE 10
#define ITEM_NAME_LEN 20
#define ITEM_TYPE_LEN 15

/*
 * ============================================================================
 * TIPOS DE DADOS E ENUMERAÇÕES
 * ============================================================================
 */

/**
 * Critérios de ordenação disponíveis para o inventário
 * SORT_NONE indica que o array não está ordenado ou perdeu ordenação
 */
typedef enum {
    SORT_NONE = 0,
    SORT_NAME = 1,
    SORT_TYPE = 2,
    SORT_PRIORITY = 3
} SortCriterion;

/**
 * Estrutura que representa um item do inventário
 * Campos variam conforme nível de desafio escolhido
 */
typedef struct {
    char name[ITEM_NAME_LEN];
    char type[ITEM_TYPE_LEN];
    int quantity;
    int priority;  // Disponível apenas no nível Mestre
} Item;

/*
 * ============================================================================
 * INTERFACE PÚBLICA - Protótipos das Funções
 * ============================================================================
 * Estas funções formam a API do módulo inventory
 */

/**
 * Adiciona novo item ao inventário com validação
 * @return 1 se adicionado com sucesso, 0 se falhou
 */
int add_item(Item *inventory, int *used, int level);

/**
 * Lista todos os itens do inventário com formatação
 */
void list_items(const Item *inventory, int used);

/**
 * Remove item por nome (busca case-insensitive)
 * @return 1 se removido com sucesso, 0 se não encontrado
 */
int remove_item_by_name(Item *inventory, int *used);

/**
 * Busca sequencial case-insensitive - O(n)
 */
void search_item_by_name(const Item *inventory, int used, const char *name);

/**
 * Ordena inventário usando Insertion Sort - O(n²)
 */
void sort_inventory(Item *inventory, int used, SortCriterion crit);

/**
 * Busca binária case-insensitive - O(log n)
 * PRÉ-CONDIÇÃO: array deve estar ordenado por nome
 * @return Índice do item ou -1 se não encontrado
 */
int binary_search_by_name(const Item *inventory, int used, const char *name);

#endif // INVENTORY_H
