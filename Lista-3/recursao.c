#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int fatorial_recursivo(int n) {
    if(n > 0) 
        return n * fatorial_recursivo(n - 1);
    else return 1;
}

int fibonacci_recursivo(int n) {
    if(n > 1)
        return fibonacci_recursivo(n - 1) + fibonacci_recursivo(n - 2);
    else if(n == 1)
        return 1;
    else if(n == 0)
        return 0;
    else return -1;
}

int inverter_recursivo(int n, int resultado) {
    if(n == 0)
        return resultado;
    else return inverter_recursivo(n / 10, resultado * 10 + n % 10);
}

int soma_vetor_recursivo(int * vetor, int tamanho) {
    if(tamanho > 0)
        return vetor[tamanho - 1] + soma_vetor_recursivo(vetor, tamanho - 1);
    else return 0;
}

int somatorio_recursivo(int n) {
    if(n > 0) 
        return somatorio_recursivo(n - 1) + n;
    else return 0;
}

int potencia_recursiva(int k, int n) {
    if(k == 0 && n == 0)
        return INT_MAX;
    else if(n == 0 || k == 1)
        return 1;
    else return k * potencia_recursiva(k, n - 1);
}

void inverte_vetor_recursivo(int * vetor, int tamanho) {
    if(tamanho > 0) {
        int aux = vetor[tamanho - 1];
        vetor[tamanho - 1] = vetor[0];
        vetor[0] = aux;
        return inverte_vetor_recursivo(vetor + 1, tamanho - 2);
    }
}

int mdc_recursivo(int x, int y) {
    if(y == 0)
        return x;
    else return mdc_recursivo(y, x % y);
}

int recorrencia_recursiva(int n, int k) {
    if(n == 0)
        return 0;
    else if(n % 10 == k)
        return 1 + recorrencia_recursiva(n / 10, k);
    else return recorrencia_recursiva(n / 10, k);
}

int multiplicacao_recursiva(int f1, int f2) {
    if(f2 == 0)
        return 0;
    else if(f2 > 0)
        return f1 + multiplicacao_recursiva(f1, f2 - 1);
    else if (f2 < 0)
        return multiplicacao_recursiva(f1, f2 + 1) - f1;
}

void printar_ordem_crescente(int n) {
    if(n >= 0) {
        printar_ordem_crescente(n - 1);
        printf("%d ", n);
    }
}

void printar_ordem_decrescente(int n) {
    if(n >= 0) {
        printf("%d ", n);
        printar_ordem_decrescente(n - 1);
    }
}

void printar_pares_ordem_crescente(int n) {
    if(n >= 0) {
        printar_pares_ordem_crescente(n - 1);
        if(n % 2 == 0)
            printf("%d ", n);
    }
}

void printar_pares_ordem_decrescente(int n) {
    if(n >= 0) {
        if(n % 2 == 0)
            printf("%d ", n);
        printar_pares_ordem_decrescente(n - 1);
    }
}

int fatorial_duplo(int n) {
    if(n > 0 && n % 2 == 1)
        return n * fatorial_duplo(n - 2);
    else return 1;
}

int fatorial_quadruplo_recursivo(int n) {
    if(n > 0)
        return (2 * n) * (2 * n - 1) * fatorial_quadruplo_recursivo(n - 1) / n; 
    else return 1;
}

int superfatorial_recursivo(int n) {
    if(n > 0)
        return fatorial_recursivo(n) * superfatorial_recursivo(n - 1);
    else return 1;
}

int hiperfatorial_recursivo(int n) {
    if(n > 0)
        return potencia_recursiva(n, n) * hiperfatorial_recursivo(n - 1);
    else return 1;
}

int fatorial_exponencial_recursivo(int n) {
    if(n > 0) 
        return potencia_recursiva(n, fatorial_exponencial_recursivo(n-1));
    else return 1;
}

int tribonacci_recursivo(int n) {
    if(n == 0 || n == 1)
        return 0;
    else if(n == 2)
        return 1;
    else return tribonacci_recursivo(n - 1) + tribonacci_recursivo(n - 2) + tribonacci_recursivo(n - 3);
}

int tetranacci_recursivo(int n) {
    if(n == 0 || n == 1 || n == 2)
        return 0;
    else if(n == 3)
        return 1;
    else return tetranacci_recursivo(n - 1) + tetranacci_recursivo(n - 2) + tetranacci_recursivo(n - 3) + tetranacci_recursivo(n - 4);
}

int padovan_recursivo(int n) {
    if(n < 0)
        return -1;
    else if(n >= 0 && n <= 2)
        return 1;
    else return padovan_recursivo(n - 2) + padovan_recursivo(n - 3); 
}

int pell_recursivo(int n) {
    if(n == 0)
        return 0;
    else if(n == 1)
        return 1;
    else if(n > 1) 
        return 2 * pell_recursivo(n - 1) + pell_recursivo(n - 2);
    else return -1;
}

int catalan_recursivo(int n) {
    if(n == 0)
        return 1;
    else return 2 * (2 * n - 1) / (n + 1) * catalan_recursivo(n - 1);
}


int main() {
    for(int i = 0; i < 12; i++)
        printf("%d ", catalan_recursivo(i));
    printf("\n");
}