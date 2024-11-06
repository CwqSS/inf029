#include <stdio.h>
#include <stdlib.h>

#pragma region Header
void limparTela();
void limparBuffer();
void esperarEnter();
void imprimirJogo(char jogo[3][3]);
int validarEntrada(char jogada[]);
int validarJogada(char jogo[3][3], char jogada[]);
void efetuarJogada(char jogo[3][3], char jogada[], int jogador);
int resultadoDoJogo(char jogo[3][3], int jogadasFeitas);
#pragma endregion

int main() {
    char jogo[3][3] = {"   ", "   ", "   "};
    char jogada[3];
    char opcao;

    int entradaInvalida = 0;

    int vencedor = -1;
    int jogadorDaVez;
    int jogadaValida, entradaValida;
    int jogadasFeitas = 0;

    do {
        // Setando valores
        jogadorDaVez = (jogadasFeitas % 2 == 0) ? 1 : 2;
        jogadaValida = 0;
        entradaValida = 0;
        opcao = '0';
        // fim

        limparTela();

        // Mostra o estado atual do jogo da velha e pede o input do jogador
        imprimirJogo(jogo);
        printf("\nJogador %d informe a sua jogada: ", jogadorDaVez);
        fgets(jogada, 3, stdin);
        // fim

        // Valida se a entrada é valida;
        entradaValida = validarEntrada(jogada);
        if(entradaValida) {
            // Se for, valida se a jogada é valida
            jogadaValida = validarJogada(jogo, jogada);
            if(!jogadaValida) {
                printf("\nJogada invalida!\n");
                esperarEnter();
                entradaValida = 0;
            }
            // fim
        }
        else {
            if(entradaInvalida) {
                limparBuffer();
                entradaInvalida = 0;
            }
            else{
                entradaInvalida = 1;
            }
            printf("\nEntrada invalida!\n");
            printf("\nDeseja continuar jogando (s/n)?\n");
            while(opcao != 's' && opcao != 'n') {
                opcao = getchar();
                if(opcao >= 'A' && opcao <= 'Z')
                    opcao = opcao - 'A' + 'a';
            }
        }
        // fim
        
        limparBuffer();
        
        // Se a jogada for valida e o jogador não desistiu de jogar
        // efetuamos a jogada na matriz e aumentamos o número de
        // jogadas feitas 
        if(jogadaValida && opcao != 'n') {
            efetuarJogada(jogo, jogada, jogadorDaVez);
            jogadasFeitas++;
            // Se há a possibilidade de ter um vencedor, 
            // varremos toda a matriz em busca de uma sequência
            // de 3 chars iguais (desde que sejam X e O)
            if(jogadasFeitas > 2) {
                vencedor = resultadoDoJogo(jogo, jogadasFeitas);
            }
        }
    } while(jogadasFeitas < 9 && opcao != 'n' && vencedor == -1);

    if(opcao != 'n') {
        limparTela();
        
        imprimirJogo(jogo);

        switch(vencedor) {
            case 0: {
                printf("\nJOGO EMPATADO\n");
                printf("\nNenhum dos jogadores venceu o jogo! A vencedora eh a velha!\n");
                break;
            }
            case 1: {
                printf("\nJOGADOR 1 LEVOU A MELHOR!\n");
                printf("\nO jogador 1 eh o vencedor!\n");
                break;
            }
            case 2: {
                printf("\nJOGADOR 2 LEVOU A MELHOR!\n");
                printf("\nO jogador 2 eh o vencedor!\n");
                break;
            }
        }
    }

    printf("\nEncerrando...\n");
    return 1;
}

#pragma region Implementação das funções
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void limparBuffer() {
    int ch;
    do {
        ch = getchar();
    } while(ch != '\n' && ch != EOF);
}

void esperarEnter() {
    printf("\nAperte ENTER para continuar!\n");
    int ch;
    do {
        ch = getchar();
    } while(ch != 10);
}

void imprimirJogo(char jogo[3][3]) {
    printf("\n\tJOGO DA VELHA\n");
    printf("\v\t 1   2   3 ");
    printf("\n\vA\t %c | %c | %c ", jogo[0][0], jogo[0][1], jogo[0][2]);
    printf("\n\t-----------\n");
    printf("B\t %c | %c | %c ", jogo[1][0], jogo[1][1], jogo[1][2]);
    printf("\n\t-----------\n");
    printf("C\t %c | %c | %c ", jogo[2][0], jogo[2][1], jogo[2][2]);
    printf("\n");
}

int validarEntrada(char entrada[]) {
    int entradaValida = 0;
    
    if(entrada[0] >= 'a' && entrada[0] <= 'z')
        entrada[0] = entrada[0] - 'a' + 'A';

    if(entrada[0] >= 'A' && entrada[0] <= 'C' 
    && entrada[1] >= '1' && entrada[1] <= '3')
        entradaValida = 1;

    return entradaValida;
}

int validarJogada(char jogo[3][3], char jogada[]) {
    int jogadaValida = 0;
    int linha, coluna;

    linha = jogada[0] - 'A';
    coluna = jogada[1] - '1';

    if(jogo[linha][coluna] != 'X' && jogo[linha][coluna] != 'O') {
        jogadaValida = 1;
    }

    return jogadaValida;
}

void efetuarJogada(char jogo[3][3], char jogada[], int jogador) {
    int linha, coluna;
    char marcacao = ' ';

    if(jogador == 1) {
        marcacao = 'X';
    }
    else if (jogador == 2) {
        marcacao = 'O';
    }

    linha = jogada[0] - 'A';
    coluna = jogada[1] - '1';

    jogo[linha][coluna] = marcacao;

    return;
}

int resultadoDoJogo(char jogo[3][3], int jogadasFeitas) {
    int resultado = -1;
    int jogadasAlinhadasJ1 = 0, J1 = 'X';
    int jogadasAlinhadasJ2 = 0, J2 = 'O';
    int i, j;
    char anterior = jogo[0][0];



    for(i = 0;  i < 3 && resultado == -1; i++) {
        for(j = 0; j < 3; j++) {
            if(anterior != jogo[i][j]) {
                jogadasAlinhadasJ1 = 0;
                jogadasAlinhadasJ2 = 0;
            }
            if(jogo[i][j] == J1) {
                anterior = jogo[i][j];
                jogadasAlinhadasJ1 += 1;
            }
            else if(jogo[i][j] == J2) {
                anterior = jogo[i][j];
                jogadasAlinhadasJ2 += 1;
            }
        }
        if(jogadasAlinhadasJ1 == 3)
            resultado = 1;
        else if(jogadasAlinhadasJ2 == 3) {
            resultado = 2;
        }
    }

    for(j = 0;  j < 3 && resultado == -1; j++) {
        for(i = 0; i < 3; i++) {
            if(anterior != jogo[i][j]) {
                jogadasAlinhadasJ1 = 0;
                jogadasAlinhadasJ2 = 0;
            }
            if(jogo[i][j] == J1) {
                anterior = jogo[i][j];
                jogadasAlinhadasJ1 += 1;
            }
            else if(jogo[i][j] == J2) {
                anterior = jogo[i][j];
                jogadasAlinhadasJ2 += 1;
            }
        }
        if(jogadasAlinhadasJ1 == 3)
            resultado = 1;
        else if(jogadasAlinhadasJ2 == 3) {
            resultado = 2;
        }
    }

    for(i = 0;  i < 3 && resultado == -1; i++) {
        if(anterior != jogo[i][i]) {
            jogadasAlinhadasJ1 = 0;
            jogadasAlinhadasJ2 = 0;
        }
        if(jogo[i][i] == J1) {
            anterior = jogo[i][i];
            jogadasAlinhadasJ1 += 1;
        }
        else if(jogo[i][i] == J2) {
            anterior = jogo[i][i];
            jogadasAlinhadasJ2 += 1;

        }
        if(jogadasAlinhadasJ1 == 3)
            resultado = 1;
        else if(jogadasAlinhadasJ2 == 3) {
            resultado = 2;
        }
    }

    for(j = 0, i = 2;  j < 3 && resultado == -1; j++, i--) {

        if(anterior != jogo[i][j]) {
            jogadasAlinhadasJ1 = 0;
            jogadasAlinhadasJ2 = 0;
        }
        if(jogo[i][j] == J1) {
            anterior = jogo[i][j];
            jogadasAlinhadasJ1 += 1;
        }
        else if(jogo[i][j] == J2) {
            anterior = jogo[i][j];
            jogadasAlinhadasJ2 += 1;
        }
        if(jogadasAlinhadasJ1 == 3)
            resultado = 1;
        else if(jogadasAlinhadasJ2 == 3) {
            resultado = 2;
        }
    }

    if(resultado == -1 && jogadasFeitas == 9) {
        resultado = 0;
    }

    // resultado == -1 : jogo em andamento;
    // resultado ==  0 : jogo empatado;
    // resultado ==  1 : jogador 1 venceu o jogo;
    // resultado ==  2 : jogador 2 venceu o jogo;

    return resultado;
}
#pragma endregion