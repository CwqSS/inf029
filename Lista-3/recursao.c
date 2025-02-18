#include <stdio.h>
#include <stdlib.h>

int fatorial_recusirvo(int n) {
    if (n < 0)
        return -1;
    if(n == 0)
        return 1;
    else return n * fatorial_recusirvo(n - 1);
}

int fibonacci_recursivo(int n) {
    if(n < 1)
        return -1;
    if(n == 1)
        return 0;
    else if(n == 2)
        return 1;
    else return fibonacci_recursivo(n - 1) + fibonacci_recursivo(n - 2);
}

// int inverterNumero_recursivo(int n) {
//     if(n / 10 == 0)
//         return n;
//     else return  inverterNumero_recursivo(n / 10);
// }

int somaElementos_recursivo(int * vetor, int tam) {
    if(tam == 0)
        return 0;
    else return vetor[tam - 1] + somaElementos_recursivo(vetor, tam - 1);
}

float exponencial_recursivo(int k, int n) {
    if(n == 0)
        return 1;
    else if(n > 0)
        return k * exponencial_recursivo(k, n - 1);
    else return (1.0 / k) * exponencial_recursivo(k, n + 1);
}

void inverteVetorInteiro_recursivo(int * vetor, int tam) {
    if(tam > 0) {
        int aux = vetor[0];
        vetor[0] = vetor[tam - 1];
        vetor[tam - 1] = aux;
        return inverteVetorInteiro_recursivo(vetor + 1, tam - 2);
    }
}

// int mdc_recursivo(int x, int y) {
//     if(y == 0) 
//         return x;
//     else return mdc_recursivo(y, x % y);
// }

int main() {

}