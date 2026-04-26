# Ticket-Priority-System

Um sistema de gerenciamento de filas desenvolvido em C++ via console, focado na manipulação de memória através de arrays estáticos para organizar atendimentos por níveis de prioridade.

## 🎯 Objetivo do Projeto
Este projeto foi desenvolvido para simular a lógica de um sistema real de chamadas, onde clientes recebem senhas (Tokens) e são classificados em três categorias de atendimento: Normal, Preferencial e Urgente.

## ⚙️ Funcionalidades
* **Emissão de Senhas:** Gera senhas sequenciais automáticas (Ex: A001, P001, U001).
* **Fila de Prioridades:** O algoritmo insere clientes na fila garantindo que prioridades mais altas ultrapassem as menores sem criar espaços vazios na memória.
* **Sistema de Chamada:** Retira o primeiro da fila, atualizando todas as posições subsequentes.
* **Cancelamento:** Permite remover uma senha específica do meio da fila reorganizando o array.
* **Estatísticas:** Exibe o número de clientes na espera e o total de atendidos.

## 🚀 Tecnologias e Conceitos Aplicados
* **Linguagem:** C++
* **Estruturas de Dados:** `struct`, Arrays estáticos.
* **Manipulação de Memória:** Realocação e deslocamento contíguo de índices.
* **Controle de Fluxo:** Tratamento do buffer de entrada (`cin.ignore`, `stringstream`) para prevenir bugs de digitação.
* **Interface (CLI):** Uso de códigos de escape ANSI para limpeza de tela nativa.

## 🛠️ Como executar
1. Clone este repositório.
2. Compile o arquivo utilizando o G++ no terminal:
   ```bash
   g++ sistema_senhas.cpp -o senhas
