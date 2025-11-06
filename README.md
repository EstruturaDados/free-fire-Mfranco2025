# 🎒 Desafio Código da Ilha — Edição Free Fire

> Implementação robusta e bem estruturada de um gerenciador de inventário com progressão de dificuldade, desenvolvido como projeto educacional para Análise e Desenvolvimento de Sistemas.

---

## 📋 Sumário Executivo

Este projeto implementa um **sistema de gerenciamento de inventário** com foco em boas práticas de engenharia de software. Combina operações clássicas de estrutura de dados (inserção, remoção, busca, ordenação) com validação rigorosa de entrada e arquitetura modular.

**Tecnologia**: C
**Objetivo Principal**: Demonstrar princípios de design, validação segura e algoritmos clássicos
**Níveis de Dificuldade**: Novato → Aventureiro → Mestre

---

## ✨ Destaques do Projeto

### Arquitetura Modular

A separação clara de responsabilidades facilita manutenção, testes e evolução:

| Módulo           | Responsabilidade             | Funções Principais              |
| ---------------- | ---------------------------- | ------------------------------- |
| **main.c**       | Orquestração de menu e fluxo | `main()`, handlers de operações |
| **inventory.c**  | Lógica de negócios           | CRUD, busca, ordenação          |
| **utils.c**      | I/O seguro e manipulação     | Leitura validada, normalização  |
| **validation.c** | Regras de negócio            | Validação de formato            |

### Funcionalidades por Nível

#### 🟢 Novato (Nível 1)

- Adicionar itens com validação
- Listar inventário
- Remover por nome
- Operações básicas sem complexidade algorítmica

#### 🟡 Aventureiro (Nível 2)

- Todas operações do Novato
- **Busca Sequencial** (O(n))
- Primeiro contato com análise de desempenho

#### 🔴 Mestre (Nível 3)

- Todas operações anteriores
- **Ordenação com Insertion Sort** (O(n²))
- **Busca Binária** (O(log n))
- Campo de prioridade para itens
- Análise comparativa de algoritmos

### Garantias de Qualidade

✓ **Validação em Camadas**: formato → capacidade → consistência
✓ **Prevenção de Overflow**: buffers dimensionados e verificados
✓ **Comparações Case-Insensitive**: normalização automática
✓ **Rastreamento de Estado**: mantém controle de ordenação
✓ **Tratamento de Pré-Condições**: busca binária valida ordenação prévia

---

## 📁 Estrutura do Projeto

```
projeto-inventario/
├── include/
│   ├── inventory.h       # Contrato de operações
│   ├── utils.h           # Interface de I/O
│   └── validation.h      # Interface de validação
├── src/
│   ├── main.c            # Ponto de entrada
│   ├── inventory.c       # Implementação de CRUD
│   ├── utils.c           # Implementação de I/O
│   └── validation.c      # Implementação de validação
├── build/
│   └── programa           # Executável gerado
└── README.md             # Este arquivo
```

### Convenções Utilizadas

- **Headers (.h)**: Definem contratos públicos, documentação de API
- **Implementação (.c)**: Contêm lógica, funções `static` para encapsulamento
- **Nomes**: Identificadores em inglês, comentários em português
- **Documentação**: Comentários de bloco explicam "por quê", não "o quê"

---

## 🧠 Decisões Arquiteturais

### 1. Separação de Responsabilidades (SoC)

Cada módulo tem uma única razão para mudar:

- **inventory**: Lógica de negócios muda
- **utils**: Formato de I/O muda
- **validation**: Regras de validação mudam
- **main**: Fluxo do usuário muda

### 2. Validação Centralizada

Todas as regras de formato em `validation.c`:

```
Rejeita:    "12 laranja"  (começa com número)
Rejeita:    "45"          (só números)
Rejeita:    "item@123"    (caracteres especiais)
Aceita:     "Kit Medico"  (letra + espaço)
Aceita:     "Mana-Potion" (letra + hífen)
```

### 3. Rastreamento de Estado de Ordenação

Mantém enum `SortCriterion` para validar pré-condição da busca binária:

```c
sort_inventory(inv, used, SORT_NAME);     // Estado: ordenado por nome
binary_search_by_name(inv, used, "item"); // OK: array está ordenado
```

### 4. Validação em Camadas

Progressão: vazio → tipo → formato → valores

```c
if (vazio)           return ERRO;  // Camada 1
if (!letra)          return ERRO;  // Camada 2
if (caractere_inválido) return ERRO; // Camada 3
return VÁLIDO;                     // Passou em todas
```

---

## 🔧 Compilação

### Requisitos

- GCC (ou compilador C compatível)
- Terminal/Shell
- Nenhuma dependência externa

### Compilar (Linux/macOS/WSL)

```bash
gcc src/main.c src/inventory.c src/utils.c src/validation.c \
    -Iinclude -o build/programa
```

**Explicação dos flags:**

- `src/*.c` - Todos os arquivos de implementação
- `-Iinclude` - Caminho dos headers
- `-o build/programa` - Nome e localização do executável

### Compilar com Warnings (Recomendado)

```bash
gcc -Wall -Wextra -std=c99 src/main.c src/inventory.c src/utils.c \
    src/validation.c -Iinclude -o build/programa
```

**Flags adicionais:**

- `-Wall -Wextra` - Ativa todos os warnings
- `-std=c99` - Define padrão C99

### Compilar com Debug

```bash
gcc -g -O0 -Wall -Wextra src/main.c src/inventory.c src/utils.c \
    src/validation.c -Iinclude -o build/programa
```

**Para usar com GDB:**

```bash
gdb ./build/programa
```

---

## ▶️ Execução

### Executar Programa

```bash
./build/programa
```

### Fluxo Interativo

1. **Escolha o Nível** (1-3)

   - Nível afeta funcionalidades disponíveis

2. **Menu Principal**

   ```
   1. Adicionar item
   2. Listar itens
   3. Remover item
   4. Buscar (sequencial) [Aventureiro+]
   6. Ordenar [Mestre]
   7. Buscar (binária) [Mestre]
   0. Sair
   ```

3. **Validação em Tempo Real**
   - Nome inválido? Programa pede nova entrada
   - Entrada não numérica? Detector automático
   - Inventário cheio? Mensagem clara

### Exemplo de Sessão

```
Escolha o nível do desafio:
1. Novato 2. Aventureiro 3. Mestre: 2

===== MENU INVENTÁRIO (Nível: 2) =====
1. Adicionar item
2. Listar itens
3. Remover item (por Nome)
4. Buscar item (sequencial)
0. Sair
Opção: 1

--- Cadastro de novo item ---
Nome do item: Kit Medico
Tipo do item: Consumivel
Quantidade: 5
Item cadastrado!
```

---

## 📊 Análise de Complexidade

### Operações Implementadas

| Operação             | Complexidade | Quando Usar                       |
| -------------------- | ------------ | --------------------------------- |
| **Adicionar**        | O(1)         | Sempre - acesso direto            |
| **Remover**          | O(n)         | Requer busca + deslocamento       |
| **Listar**           | O(n)         | Sempre - necessário visitar todos |
| **Busca Sequencial** | O(n)         | Array pequeno ou não ordenado     |
| **Insertion Sort**   | O(n²)        | Array pequeno (<1000 elementos)   |
| **Busca Binária**    | O(log n)     | Array grande e **pré-ordenado**   |

### Quando Cada Algoritmo é Ótimo

**Busca Sequencial (O(n))**

- ✓ Arrays pequenos (< 100 elementos)
- ✓ Array não ordenado
- ✓ Implementação simples

**Insertion Sort (O(n²))**

- ✓ Arrays pequenos (< 1000 elementos)
- ✓ Dados já parcialmente ordenados
- ✓ Estável e in-place

**Busca Binária (O(log n))**

- ✓ Arrays grandes (> 1000 elementos)
- ✓ Array **obrigatoriamente** ordenado
- ✗ Requer múltiplas comparações

---

## 🔍 Detalhes Técnicos Importantes

### Validação de Entrada

A função `read_int_safe()` usa estratégia sofisticada:

```c
sscanf(buffer, "%d %c", &value, &extra) == 1
// Retorna 1 = sucesso (só número)
// Retorna 2 ou 0 = falha (caracteres extras ou não numérico)
```

**Benefício**: Detecta entradas como "123abc" ou "12 34"

### Normalização para Case-Insensitive

Todas as buscas convertem para maiúsculas:

```c
str_to_upper(search_term);  // "Kit medico" → "KIT MEDICO"
// Comparação sempre com strings normalizadas
```

### Prevenção de Buffer Overflow

Limites rigorosos em todas as operações de string:

```c
#define ITEM_NAME_LEN 20  // Incluindo \0
strncpy(dest, src, ITEM_NAME_LEN-1);
dest[ITEM_NAME_LEN-1] = '\0';
```

### Cast para unsigned char

Protege contra caracteres estendidos:

```c
if (!isalpha((unsigned char)str[0]))  // Correto
// Evita comportamento indefinido com char < 0
```

---

## 📚 Conceitos Educacionais

### Padrões de Design Aplicados

1. **Handler Pattern**: Funções separadas para cada operação do menu
2. **Module Pattern**: Encapsulamento via `static` em nível de arquivo
3. **Strategy Pattern**: Múltiplos critérios de ordenação (enum)
4. **State Pattern**: Rastreamento de estado de ordenação

### Boas Práticas Demonstradas

- ✓ Documentação em 3 níveis: API, implementação, decisões
- ✓ Função única com responsabilidade clara (SRP)
- ✓ Encapsulamento: funções `static` não vazam detalhes
- ✓ Validação defensiva em camadas
- ✓ Evita magic numbers com `#define`
- ✓ Nomes descritivos (80 caracteres no máximo)

---

## 🧪 Testando o Projeto

### Casos de Teste Básicos

```bash
# Teste 1: Adicionar e listar
# Input: 1 → "kit medico" → "consumivel" → 5 → 2 → 0
# Esperado: Item aparece na listagem

# Teste 2: Validação de nome inválido
# Input: 1 → "123 item" (inválido)
# Esperado: Programa pede novo nome

# Teste 3: Busca binária sem ordenação
# Input: 3 → 7 (sem ordenar primeiro)
# Esperado: Aviso de não ordenado
```

### Casos de Borda

- String vazia como nome
- Caracteres especiais (#@$%)
- Números muito grandes
- Pressionar Ctrl+C durante leitura
- Removendo item que não existe
- Buscando em inventário vazio

---

## 🚀 Extensões Futuras

### Curto Prazo (Fácil)

- [ ] Salvar/carregar inventário de arquivo
- [ ] Limpar tela entre operações
- [ ] Colorir output (ANSI codes)
- [ ] Histórico de operações

### Médio Prazo (Moderado)

- [ ] Testes unitários com CUnit
- [ ] Makefile para automação
- [ ] Interface gráfica (SDL2)
- [ ] Suporte a banco de dados (SQLite)

### Longo Prazo (Desafiador)

- [ ] Replicação multiplayer (sockets)
- [ ] Sincronização com servidor
- [ ] Análise de performance (profiling)
- [ ] Versão em linguagem de script (Lua/Python)

---

## 📖 Referências de Estudo

### Algoritmos

- CORMEN et al. _Introduction to Algorithms_ (3rd ed.) - Capítulos 2 e 5
- **Online**: Visualgo.net - Algoritmos em ação

### Estruturas de Dados em C

- K&R _The C Programming Language_ (2nd ed.)
- KERNIGHAN & RITCHIE - Capítulo 6 (structs)

### Validação e Segurança

- CERT C Secure Coding Standards
- OWASP - Input Validation Guidelines

### Documentação

- Google C++ Style Guide (aplicável para C)
- Doxygen - Gerador de documentação automática

---

## 💡 Boas Práticas e Recomendações

### Durante o Desenvolvimento

1. Compile frequentemente com `-Wall -Wextra`
2. Teste cada função isoladamente antes de integrar
3. Mantenha funções pequenas (< 20 linhas idealmente)
4. Documente decisões não óbvias

### Antes de Enviar

1. Remova código de debug ou comente
2. Verifique memory leaks com Valgrind
3. Execute testes de borda
4. Revise comentários para clareza

### Manutenção Futura

1. Não modifique interfaces (.h) sem necessidade
2. Mantenha testes ao adicionar features
3. Documente bugs encontrados
4. Versione mudanças significativas

---

## 🤝 Contribuindo

Para melhorar este projeto:

1. **Identificar problema**: Teste e documente
2. **Forkar conceitual**: Entenda o design
3. **Implementar**: Mantenha estilo e modularidade
4. **Testar**: Valide casos normais e borda
5. **Documentar**: Explique decisões significativas

---

## 📄 Licença

Este projeto é fornecido como material educacional. Sinta-se livre para usar, modificar e distribuir.

---

## ❓ Perguntas Frequentes

**P: Por que usar `static` em algumas funções?**
R: Limita visibilidade ao arquivo, promovendo encapsulamento e prevenindo conflitos de nome global.

**P: Posso usar outra linguagem (C++, Python)?**
R: Sim! Os conceitos são transferíveis. Considere este projeto como baseline.

**P: Como adicionar novo critério de ordenação?**
R: Estenda o enum `SortCriterion`, implemente case em `sort_inventory()`, teste.

**P: Programa trava ao inserir?**
R: Verifique se há deadlock em `read_int_safe()`. Use Ctrl+C para sair.

**P: Como melhorar desempenho?**
R: Perfil com `gprof`, otimize loops quentes, considere estruturas melhores.

---

## 📞 Suporte e Dúvidas

Para questões sobre implementação:

1. Revise comentários no código
2. Consulte headers (.h) para interface pública
3. Compare com versão refatorada fornecida
4. Analise casos de teste

---

**Desenvolvido com 💻 e ❤️ para aprendizado em ADS**

_Última atualização: Novembro 2025_
