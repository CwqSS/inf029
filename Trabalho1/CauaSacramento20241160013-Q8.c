#include <stdio.h>
#include <stdlib.h>

#pragma region Header
void iniciarTabuleiro(int tabuleiro[10][10]);
void mostrarTabuleiro(int tabuleiro[10][10]);
void mostrarTabuleiroInimigo(int tabuleiro[10][10]);
int validarEntrada(char entrada[], int validarSentido);
int validarJogada(int tabuleiro[10][10], char entrada[], int tamBarco);
int posicionarBarco(int tabuleiro[10][10], char entrada[], int tamBarco);
void alocarTabuleiro(int tabuleiro[10][10], int qtdB1, int qtdB2, int qtdB3, int qtdB4);
int existeBarco(int tabuleiro[10][10]);
int opcoesJogador(int tabuleiroAtacante[10][10], int tabuleiroDefensor[10][10]);

void limparTela();
void limparBuffer();
void esperarEnter();
#pragma endregion

int main() {
    int qtdB4 = 0;
    int qtdB3 = 0;
    int qtdB2 = 2;
    int qtdB1 = 0;

    char iniciar = 0;
    char lerInstrucoes = '0';
    int temBarcoJ1 = 1, temBarcoJ2 = 1;

    int tabuleiroJ1[10][10];
    int tabuleiroJ2[10][10];

    iniciarTabuleiro(tabuleiroJ1);
    iniciarTabuleiro(tabuleiroJ2);

    limparTela();

    printf("Deseja ler as instrucoes? Se sim, digite 's'. Se nao, digite outra coisa.\n");
    scanf(" %c", &lerInstrucoes);
    limparBuffer();
    limparTela();

    if(lerInstrucoes == 's') {
        printf("INSTRUCOES");
        printf("\nO jogo eh jogado em turnos. Primeiro o jogador 1 aloca os barcos, depois o jogador 2.\n");
        printf("\nPara alocar o barco, informe a posicao inicial do seu barco e o sentido (ex: a2x, F4y).\n");
        printf("\nEscolha a linha : letras de 'A' a 'J';\n");
        printf("\nEscolha a coluna : numeros de 0 a 9;\n");
        printf("\nEscolha a coluna : 'x' para horizontal e 'y' para vertical.\n");
        printf("\nO jogador 1 faz a jogada primeiro, depois o jogador 2.\n");
        printf("\nPara escolher onde atirar, siga o mesmo procedimento para alocar um barco, sem o sentido (ex: A1, B3).\n");
        printf("\nLembre-se: voce pode atirar em um mesmo lugar mais de uma vez, logo, fique atento para nao cometer esse erro.\n");
        printf("\nBom jogo.\n");
        esperarEnter();
        limparTela();
    }

    puts("JOGADOR 1, PRONTO?\n");
    esperarEnter();
    limparTela();
    alocarTabuleiro(tabuleiroJ1, qtdB1, qtdB2, qtdB3, qtdB4);
    limparTela();

    
    puts("JOGADOR 2, PRONTO?\n");
    esperarEnter();
    limparTela();
    alocarTabuleiro(tabuleiroJ2, qtdB1, qtdB2, qtdB3, qtdB4);
    limparTela();
    

    printf("\nTODOS OS BARCOS POSICIONADOS\n");
    esperarEnter();

    int continuarJogando;
    do {
        continuarJogando = 0;
        limparTela();
        
        printf("\nJOGADOR 1, FACA SUA JOGADA\n");
        esperarEnter();
        continuarJogando = opcoesJogador(tabuleiroJ1, tabuleiroJ2);
        temBarcoJ2 = existeBarco(tabuleiroJ2);
        esperarEnter();
        
        limparTela();

        if(continuarJogando && temBarcoJ2){
            printf("\nJOGADOR 2, FACA SUA JOGADA\n");
            esperarEnter();
            continuarJogando = opcoesJogador(tabuleiroJ2, tabuleiroJ1);
            temBarcoJ1 = existeBarco(tabuleiroJ1);
            esperarEnter();
        }
    } while(temBarcoJ1 && temBarcoJ2 && continuarJogando);

    if(!temBarcoJ2) {
        printf("\nO jogador 1 ganhou este jogo!\n");
    }
    else if (!temBarcoJ1) {
        printf("\nO jogador 2 ganhou este jogo!\n");
    }

    printf("\nEncerrando...\n");

    esperarEnter();
}

#pragma region Implementação das funções
void iniciarTabuleiro(int tabuleiro[10][10]) {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

void mostrarTabuleiro(int tabuleiro[10][10]) {
    char linha = 'A';
    
    for(int i = 0; i < 10; i++)
        printf("--------");
    printf("\n");

    for(int i = 9; i > -1; i--) {
        printf("%c", linha + i);
        for(int j = 0; j < 10; j++) {
            if(tabuleiro[i][j] == 0) {
                printf("\t[ ]");
            }
            else if(tabuleiro[i][j] == 1) {
                printf("\t[N]");
            }
            else if(tabuleiro[i][j] == 2) {
                printf("\t[L]");
            }
            else if(tabuleiro[i][j] == 3) {
                printf("\t[X]");
            }
        }
        printf("\n\v");
    }

    for(int i = 0; i < 10; i++)
        printf("\t %d", i);

    printf("\n");
    for(int i = 0; i < 10; i++)
        printf("--------");
    printf("\n");
}

void mostrarTabuleiroInimigo(int tabuleiro[10][10]) {
    char linha = 'A';
    
    for(int i = 0; i < 10; i++)
            printf("--------");
        printf("\n");

    for(int i = 9; i > -1; i--) {
        printf("%c", linha + i);
        for(int j = 0; j < 10; j++) {
            if(tabuleiro[i][j] == 0 || tabuleiro[i][j] == 1) {
                printf("\t[ ]");
            }
            else if(tabuleiro[i][j] == 2) {
                printf("\t[O]");
            }
            else if(tabuleiro[i][j] == 3) {
                printf("\t[X]");
            }
        }
        printf("\n\v");
    }

    for(int i = 0; i < 10; i++)
        printf("\t %d", i);

    printf("\n");
    for(int i = 0; i < 10; i++)
            printf("--------");
    printf("\n");
}

int validarEntrada(char entrada[], int validarSentido) {
    int entradaValida = 1;

    entrada[3] = '\0';

    if(entrada[0] >= 'a' && entrada[0] <= 'j') 
        entrada[0] += 'A' - 'a';
    
    if(entrada[0] < 'A' || entrada[0] > 'J') 
        entradaValida = 0;

    if(entrada[1] < '0' || entrada[1] > '9') 
        entradaValida = 0;

    if(validarSentido) {
        if(entrada[2] == 'X' || entrada[2] == 'Y')
            entrada[2] += 'a' - 'A';

        if(entrada[2] != 'x' && entrada[2] != 'y')
            entradaValida = 0;
    }
    else {
        entrada[2] = '\0';
    }

    return entradaValida;
}

int validarJogada(int tabuleiro[10][10], char entrada[], int tamBarco) {
    int linha, coluna, sentido;
    int jogadaValida = 1;
    
    linha = entrada[0] - 'A';
    coluna = entrada[1] - '0';
    sentido = entrada[2] - 'x';

    if(sentido && linha + tamBarco - 1 >= 10) {
        jogadaValida = 0;
    }
    else if (!sentido && coluna + tamBarco - 1 >= 10) {
        jogadaValida = 0;
    }

    if(jogadaValida) {
        for(int i = linha, j = coluna; i < tamBarco + linha && j < tamBarco + coluna;) {
            if(tabuleiro[i][j] != 0)
                jogadaValida = 0;
            if(sentido)
                i = i + 1;
            else
                j = j + 1;
        }
    }

    return jogadaValida;
}

int posicionarBarco(int tabuleiro[10][10], char entrada[], int tamBarco) {
    int linha, coluna, sentido;
    linha = entrada[0] - 'A';
    coluna = entrada[1] - '0';
    sentido = entrada[2] - 'x';

    int i = linha;
    int j = coluna;
    while(i < linha + tamBarco && j < coluna + tamBarco) {
        tabuleiro[i][j] = 1;
        if(sentido)
            i = i + 1;
        else
            j = j + 1;
    }
}

void alocarTabuleiro(int tabuleiro[10][10], int qtdB1, int qtdB2, int qtdB3, int qtdB4) {
    int totalBarcos = qtdB1 + qtdB2 + qtdB3 + qtdB4;
    int barcosColocados = 0;
    int tamBarco, qtdTrocas = 0;

    if(qtdB4 > 0) { 
        tamBarco = 4;
    }
    else if(qtdB3 > 0) {
        tamBarco = 3;
    }
    else if(qtdB2 > 0) {
        tamBarco = 2;
    }
    else if(qtdB1 > 0) {
        tamBarco = 1;
    }

    char estouJogando;

    limparTela();
    mostrarTabuleiro(tabuleiro);
    esperarEnter();

    do {
        limparTela();

        int entradaValida, jogadaValida;
        char entrada[5];
        estouJogando = '0';


        printf("\nTamanho do barco: %d\n", tamBarco);
        printf("\nInforme a posicao inicial do seu barco e o sentido (ex: a2x, F4y): ");
        fgets(entrada, 5, stdin);
        setbuf(stdin,NULL);

        entradaValida = validarEntrada(entrada, 1);
        jogadaValida = validarJogada(tabuleiro, entrada, tamBarco);

        if(entradaValida && jogadaValida) {
            posicionarBarco(tabuleiro, entrada, tamBarco);
            mostrarTabuleiro(tabuleiro);
            printf("\nBarco alocado com sucesso\n");
            esperarEnter();
            barcosColocados += 1;
            if(barcosColocados == qtdB4) {
                tamBarco = tamBarco - 1;
            }
            if(barcosColocados == qtdB4 + qtdB3) {
                tamBarco = tamBarco - 1;
            }
            if(barcosColocados == qtdB4 + qtdB3 + qtdB2) {
                tamBarco = tamBarco - 1;
            }
        }
        else 
        {    
            limparTela();
            if(!entradaValida) {
                printf("\nEntrada invalida! Deseja continuar jogando? (s/n)\nR: ");
                while(estouJogando != 's' && estouJogando != 'n')
                    scanf(" %c", &estouJogando);
                if(estouJogando == 's')
                    limparBuffer();
            }
            else {
                printf("\nJogada invalida!\n");
                esperarEnter();
            }
        }
    } while(barcosColocados < totalBarcos && estouJogando != 'n');
}

void atacarPosicao(int tabuleiro[10][10], char entrada[]) {
    int linha, coluna;
    linha = entrada[0] - 'A';
    coluna = entrada[1] - '0';

    if(tabuleiro[linha][coluna] == 0) {
        tabuleiro[linha][coluna] = 3;
    }
    else if (tabuleiro[linha][coluna] == 1) {
        tabuleiro[linha][coluna] = 2;
    }
}

int opcoesJogador(int tabuleiroAtacante[10][10], int tabuleiroDefensor[10][10]) {
    char opcao;
    int atirou = -1;

    do {
        limparTela();
        opcao = '0';
        
        printf("\nMenu\n");
        printf("0 - Atirar\n");
        printf("1 - Ver meu tabuleiro\n");
        printf("2 - Ver tabuleiro Inimigo\n");
        printf("3 - Encerrar o jogo\n");


        scanf(" %c", &opcao);

        limparBuffer();
        limparTela();

        switch(opcao) {
            case '0': {
                char entrada[4];
                puts("Informe a posicao do ataque (ex: A1, B4): ");
                fgets(entrada, 4, stdin);
                if(validarEntrada(entrada, 0)) {
                    atacarPosicao(tabuleiroDefensor, entrada);
                    atirou = 1;
                }
                else {
                    printf("Entrada invalida.");
                    esperarEnter();
                }
                break;
            }
            case '1': {
                printf("\nMEU TABULEIRO\n");
                mostrarTabuleiro(tabuleiroAtacante);
                esperarEnter();
                break;
            }
            case '2': {
                printf("\nTABULEIRO INIMIGO\n");
                mostrarTabuleiroInimigo(tabuleiroDefensor);
                esperarEnter();
                break;
            }
            case '3': {
                char sair = '0';
                printf("Deseja mesmo encerrar o jogo? (s/n)\nR: ");
                while(sair != 's' && sair != 'n')
                    scanf(" %c", &sair);

                if(sair == 's')
                    atirou = 0;
                break;
            }
        }

    } while(atirou == -1);

    return atirou;
}

int existeBarco(int tabuleiro[10][10]) {
    int temBarco = 0;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if(tabuleiro[i][j] == 1) {
                temBarco = 1;
            }
        }
    }
    return temBarco;
}

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
#pragma endregion