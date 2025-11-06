#include "validation.h"
#include <ctype.h>

/*
 * ============================================================================
 * MÓDULO DE VALIDAÇÃO - Regras de Negócio Centralizadas
 * ============================================================================
 * Centraliza lógica de validação para facilitar manutenção e reutilização.
 * Validações em camadas aumentam legibilidade e facilitam debug.
 */

/**
 * Valida formato de nome/tipo segundo regras de negócio
 *
 * Regras implementadas (validação em camadas):
 * 1. String não pode ser vazia
 * 2. Primeiro caractere DEVE ser letra (a-z, A-Z)
 * 3. Caracteres subsequentes podem ser: letras, espaços ou hífens
 *
 * Esta abordagem previne entradas como "12 laranja" ou "45" que causavam bugs.
 *
 * Nota sobre unsigned char cast:
 * - isalpha() espera int com valor de unsigned char ou EOF
 * - Cast para unsigned char previne comportamento indefinido com char negativos
 *   (caracteres com valor > 127 em sistemas com char signed)
 *
 * @param str String a ser validada
 * @return 1 se válido, 0 se inválido
 */
int is_valid_name_format(const char *str) {
    // Camada 1: Validação de string vazia
    if (str[0] == '\0') {
        printf("[DEBUG] Falha Regra 1: Vazio\n");
        return 0;
    }

    // Camada 2: Validação do primeiro caractere (deve ser letra)
    if (!isalpha((unsigned char)str[0])) {
        printf("[DEBUG] Falha Regra 2: Não começa com letra\n");
        return 0;
    }

    // Camada 3: Validação dos demais caracteres
    for (int i = 1; str[i]; i++) {
        if (!isalpha((unsigned char)str[i]) && str[i] != ' ' && str[i] != '-') {
            printf("[DEBUG] Falha Regra 3: Caractere inválido '%c'\n", str[i]);
            return 0;
        }
    }

    // Todas as regras foram satisfeitas
    return 1;
}
