#ifndef UTILS_H
#define UTILS_H

// Tamanho máximo do buffer de entrada
#define MAX_INPUT_BUFFER 100

/*
 * ============================================================================
 * UTILITÁRIOS DE I/O E MANIPULAÇÃO DE STRINGS
 * ============================================================================
 * Funções auxiliares para entrada segura e manipulação de dados
 */

/**
 * Limpa buffer de entrada para prevenir bugs de leitura
 */
void clear_input_buffer();

/**
 * Lê inteiro com validação robusta (detecta caracteres extras)
 * @return Inteiro validado ou -1 em EOF
 */
int read_int_safe();

/**
 * Lê string com remoção automática de newline
 * @param str Buffer de destino
 * @param maxlen Tamanho máximo (incluindo \0)
 */
void read_str_safe(char *str, int maxlen);

/**
 * Converte string para maiúsculas (in-place)
 * Usada para comparações case-insensitive
 */
void str_to_upper(char *str);

#endif // UTILS_H
