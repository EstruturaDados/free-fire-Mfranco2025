#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdio.h>

/*
 * ============================================================================
 * MÓDULO DE VALIDAÇÃO - Regras de Negócio
 * ============================================================================
 * Centraliza lógica de validação para facilitar manutenção
 */

/**
 * Valida formato de nome/tipo segundo regras de negócio
 *
 * Regras:
 * - Não pode ser vazio
 * - Deve começar com letra (a-z, A-Z)
 * - Pode conter apenas letras, espaços ou hífens
 *
 * @param str String a ser validada
 * @return 1 (true) se válido, 0 (false) se inválido
 */
int is_valid_name_format(const char *str);

#endif // VALIDATION_H
