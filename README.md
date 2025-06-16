# 🟡 Pac-Man em C (Estrutura de Dados)

Este projeto é um jogo simples inspirado no clássico **Pac-Man**, desenvolvido em C como atividade da disciplina de **Estrutura de Dados**. O objetivo é coletar todos os pontos do labirinto enquanto foge de um fantasma que se movimenta aleatoriamente.

## 🎮 Como Jogar

- Use as teclas `W` (cima), `A` (esquerda), `S` (baixo), `D` (direita) para mover o Pac-Man (`P`).
- O objetivo é comer todos os pontos (`.`) do mapa.
- Se um fantasma (`F`) colidir com o Pac-Man, o jogo termina.
- Ao comer todos os pontos, o jogador vence!

---

## ⚙️ Requisitos

- Compilador C compatível com Windows (ex: Dev-C++, Code::Blocks)
- Bibliotecas padrão (`conio.h`, `windows.h`)
- **Não utiliza** bibliotecas gráficas externas (como SDL, OpenGL, etc.)

---

## 🛠️ Como Compilar

1. Abra o Code::Blocks ou Dev-C++
2. Crie um novo projeto ou arquivo e cole o código fonte disponível
3. Compile e execute

---

## 📌 Estruturas de Dados Utilizadas

### ✅ Fila (FIFO)
Utilizada para controlar a movimentação dos fantasmas. Cada movimento consiste em:

- Remover o fantasma da frente da fila
- Calcular novo movimento aleatório (se possível)
- Atualizar posição e reinserir o fantasma no final da fila

### ✅ Structs
- `Pacman`: guarda posição e pontuação do jogador
- `Fantasma`: cada nó da fila representa um fantasma
- `FilaFantasma`: controla a fila dos fantasmas (frente e traseira)

---

## 🔍 Lógica do Jogo

- O mapa é uma matriz de caracteres (`char labirinto[LINHAS][COLUNAS]`)
- A posição do Pac-Man e dos fantasmas é encontrada ao iniciar o jogo
- O jogo atualiza a cada ciclo:
  1. Imprime o mapa
  2. Move o Pac-Man conforme entrada do jogador
  3. Move os fantasmas aleatoriamente
  4. Verifica colisão ou vitória
- O jogo termina se o Pac-Man for pego ou coletar todos os pontos

---
