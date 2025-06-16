#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define LINHAS 5
#define COLUNAS 20

char labirinto[LINHAS][COLUNAS + 1] = {
    "###################",
    "#P . . . . # . . F#",
    "# # # # . # . # # #",
    "# . . . . . . . . #",
    "###################"
};

typedef struct {
    int x, y;
    int pontos;
} Pacman;

typedef struct Fantasma {
    int x, y;
    struct Fantasma* prox;
} Fantasma;

typedef struct {
    Fantasma* frente;
    Fantasma* tras;
} FilaFantasma;

void enfileirarFantasma(FilaFantasma* fila, int x, int y) {
    Fantasma* novo = (Fantasma*)malloc(sizeof(Fantasma));
    novo->x = x;
    novo->y = y;
    novo->prox = NULL;
    if (fila->tras != NULL) {
        fila->tras->prox = novo;
    } else {
        fila->frente = novo;
    }
    fila->tras = novo;
}

Fantasma* desenfileirarFantasma(FilaFantasma* fila) {
    Fantasma* temp;
    if (fila->frente == NULL) return NULL;
    temp = fila->frente;
    fila->frente = fila->frente->prox;
    if (fila->frente == NULL) fila->tras = NULL;
    temp->prox = NULL;
    return temp;
}

void liberarFantasmas(FilaFantasma* fila) {
    Fantasma* temp;
    while ((temp = desenfileirarFantasma(fila)) != NULL) {
        free(temp);
    }
}

void imprimirLabirinto() {
    int i;
    for (i = 0; i < LINHAS; i++) {
        printf("%s\n", labirinto[i]);
    }
}

int contarPontosRestantes() {
    int count = 0;
    int i, j;
    for (i = 0; i < LINHAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            if (labirinto[i][j] == '.') {
                count++;
            }
        }
    }
    return count;
}

void moverPacman(Pacman* p, char direcao) {
    int novoX = p->x;
    int novoY = p->y;

    if (direcao == 'w') novoX--;
    else if (direcao == 's') novoX++;
    else if (direcao == 'a') novoY--;
    else if (direcao == 'd') novoY++;

    if (novoX >= 0 && novoX < LINHAS && novoY >= 0 && novoY < COLUNAS && labirinto[novoX][novoY] != '#') {
        if (labirinto[novoX][novoY] == '.') {
            p->pontos++;
        }

        labirinto[p->x][p->y] = ' ';
        p->x = novoX;
        p->y = novoY;
        labirinto[p->x][p->y] = 'P';
    }
}

void moverFantasma(FilaFantasma* fila) {
    Fantasma* f;
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    int direcao;
    int novoX, novoY;

    f = desenfileirarFantasma(fila);
    if (f == NULL) return;

    direcao = rand() % 4;
    novoX = f->x + dx[direcao];
    novoY = f->y + dy[direcao];

    if (novoX >= 0 && novoX < LINHAS && novoY >= 0 && novoY < COLUNAS) {
        if (labirinto[novoX][novoY] == ' ' || labirinto[novoX][novoY] == '.') {
            if (labirinto[novoX][novoY] != 'F') {
                labirinto[f->x][f->y] = ' ';
                f->x = novoX;
                f->y = novoY;
                labirinto[f->x][f->y] = 'F';
            }
        }
    }

    enfileirarFantasma(fila, f->x, f->y);
    free(f);
}

int verificarColisao(Pacman p, FilaFantasma* fila) {
    Fantasma* temp = fila->frente;
    while (temp != NULL) {
        if (temp->x == p.x && temp->y == p.y) {
            return 1;
        }
        temp = temp->prox;
    }
    return 0;
}

void localizarPersonagens(Pacman* p, FilaFantasma* fila) {
    int i, j;
    for (i = 0; i < LINHAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            if (labirinto[i][j] == 'P') {
                p->x = i;
                p->y = j;
                p->pontos = 0;
            } else if (labirinto[i][j] == 'F') {
                enfileirarFantasma(fila, i, j);
            }
        }
    }
}

int main() {
    Pacman pac;
    FilaFantasma fila = {NULL, NULL};

    localizarPersonagens(&pac, &fila);

    while (1) {
        system("cls");
        imprimirLabirinto();
        printf("\nPontos: %d\n", pac.pontos);
        printf("Movimente com W A S D\n");

        if (contarPontosRestantes() == 0) {
            printf("\nVocê venceu!\n");
            break;
        }

        if (_kbhit()) {
            char move = _getch();
            moverPacman(&pac, move);
        }

        moverFantasma(&fila);

        if (verificarColisao(pac, &fila)) {
            system("cls");
            imprimirLabirinto();
            printf("\nGame Over! Voce foi pego por um fantasma.\n");
            break;
        }

        Sleep(300);
    }

    liberarFantasmas(&fila);
    return 0;
}

