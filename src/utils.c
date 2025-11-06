#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

/*
 * ============================================================================
 * MÓDULO DE UTILITÁRIOS - Funções Auxiliares Reutilizáveis
 * ============================================================================
 * Centraliza operações comuns de I/O e manipulação de strings,
 * promovendo reuso de código e consistência na validação de entrada.
 */

/**
 * Limpa o buffer de entrada após leitura
 * Previne que caracteres residuais (como \n) afetem próximas leituras
 */
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Leitura robusta de inteiros com validação completa
 *
 * Estratégia de validação:
 * 1. Usa fgets para ler linha inteira (evita buffer overflow)
 * 2. sscanf com formato "%d %c" detecta caracteres extras após o número
 * 3. Se sscanf retorna 1, só há um inteiro válido
 * 4. Se retorna 2, há caracteres inválidos após o número
 *
 * @return Inteiro validado (>= 0) ou -1 em caso de EOF
 */
int read_int_safe() {
    char buffer[MAX_INPUT_BUFFER];
    int value;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char extra;

        // Detecta entrada vazia (usuário apenas pressionou Enter)
        if (buffer[0] == '\n') {
            printf("[ERRO] Entrada inválida. Digite um número inteiro: ");
            continue;
        }

        // sscanf com %c extra detecta lixo após o número
        // Retorna 1 = sucesso (só int), 2 = falha (tem char extra)
        if (sscanf(buffer, "%d %c", &value, &extra) == 1) {
            if (value >= 0) {
                return value;
            } else {
                printf("[ERRO] Digite um número positivo: ");
            }
        } else {
            printf("[ERRO] Entrada inválida. Digite um número inteiro: ");
        }
    }

    return -1;  // EOF detectado
}

/**
 * Leitura segura de strings com remoção de newline
 *
 * fgets captura o \n no final da string. strcspn localiza e substitui
 * o \n por \0, garantindo string corretamente terminada.
 *
 * @param str Buffer de destino
 * @param maxlen Tamanho máximo do buffer (incluindo \0)
 */
void read_str_safe(char *str, int maxlen) {
    if (fgets(str, maxlen, stdin)) {
        str[strcspn(str, "\n")] = '\0';  // Remove o newline capturado
    } else {
        str[0] = '\0';  // EOF ou erro: retorna string vazia
    }
}

/**
 * Conversão in-place para maiúsculas
 * Utilizada para comparações case-insensitive
 *
 * Modifica a string original - use uma cópia se precisar preservar o original
 */
void str_to_upper(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}
