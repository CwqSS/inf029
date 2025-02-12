#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

array * vetorPrincipal[TAM];

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    int retorno = 0;
    int sem_espaco;
    int sem_espaco_array;
    int indice = posicao - 1;

    // a posicao pode já existir estrutura auxiliar
    if(vetorPrincipal[indice] != NULL)
    {
        retorno = JA_TEM_ESTRUTURA_AUXILIAR;
    }
    // se posição é um valor inválido {entre 1 e 10}
    else if(indice < 0 || indice > 9)
    {
        retorno = POSICAO_INVALIDA;
    }
    // o tamanho nao pode ser menor que 1
    else if(tamanho < 1)
    {
        retorno = TAMANHO_INVALIDO;
    }
    // o tamanho ser muito grande
    else 
    {
        array * teste_0 = malloc(sizeof(array));
        
        if(teste_0 != NULL)
            teste_0->valores = malloc(sizeof(int) * tamanho);
        if(teste_0 == NULL || teste_0->valores == NULL)
            retorno = SEM_ESPACO_DE_MEMORIA;
        free(teste_0);
        free(teste_0->valores);
    }
    // deu tudo certo, crie
    if (retorno == 0)
    {
        array * nova_estrutura = malloc(sizeof(array));
        nova_estrutura->valores = malloc(sizeof(int) * tamanho);
        nova_estrutura->tamanho = tamanho;
        nova_estrutura->topo = 0;
        vetorPrincipal[indice] = nova_estrutura;
        retorno = -1;
    }

    return retorno;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int temEspaco = 0;
    int posicao_invalida = 0;
    int indice = posicao - 1;

    if(indice < 0 || indice > 9)
        posicao_invalida = 1;

    if (posicao_invalida)
        retorno = POSICAO_INVALIDA;
    else
    {
        // testar se existe a estrutura auxiliar
        array * estrutura = vetorPrincipal[indice];
        if(estrutura != NULL)
            existeEstruturaAuxiliar = 1;
        if (existeEstruturaAuxiliar)
        {
            if(estrutura->topo < estrutura->tamanho)
                temEspaco = 1;
            if (temEspaco)
            {
                //insere
                estrutura->valores[estrutura->topo] = valor; 
                estrutura->topo = estrutura->topo + 1; 
                retorno = SUCESSO;
            }
            else
            {
                retorno = SEM_ESPACO;
            }
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }

    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    int retorno = SUCESSO;
    int indice = posicao - 1;
    array * aux = vetorPrincipal[indice];

    if(indice < 0 || indice > 9)
        retorno = POSICAO_INVALIDA;
    else if(aux == NULL)
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else if(aux->topo == 0)
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    else
    {
        aux->topo = aux->topo - 1;
    }
    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    int retorno = SUCESSO;
    int indice = posicao - 1;
    array * aux = vetorPrincipal[indice];

    if(indice < 0 || indice > 9)
        retorno = POSICAO_INVALIDA;
    else if(aux == NULL)
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else if(aux->topo == 0)
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    else {
        int achou = 0;
        int index = -1;
        for(int i = 0; i < aux->topo && !achou; i++)
            if(valor == aux->valores[i]) {
                achou = 1;
                index = i;
            }
        if(!achou){
            retorno = NUMERO_INEXISTENTE;
        }
        else {
            for(int i = index; i < aux->topo - 1; i++)
                aux->valores[i] = aux->valores[i + 1];
            aux->topo = aux->topo - 1;
        }
    }
    return retorno;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno = 0;
    int indice = posicao - 1;
    array * aux = vetorPrincipal[indice];

    if(indice < 0 || indice > 9)
        retorno = POSICAO_INVALIDA;
    else if(aux == NULL)
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else {
        for(int i = 0; i < aux->topo; i++)
            vetorAux[i] = aux->valores[i];
        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno = 0;
    retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);
    if(retorno == SUCESSO) {
        array * aux = vetorPrincipal[posicao - 1];
        insertion_sort(vetorAux, aux->topo);
    }
    
    return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = 0;
    int qtdValores = 0;
    for(int i = 0; i < TAM; i++) {
        if(vetorPrincipal[i] != NULL) {
            qtdValores = qtdValores + vetorPrincipal[i]->topo;
        }
    }
    if(qtdValores == 0) {
        retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }
    else {
        int k = 0;
        for(int i = 0; i < TAM; i++) {
            array * aux = vetorPrincipal[i];
            if(aux != NULL) {
                for(int j = 0; j < aux->topo; j++)
                    vetorAux[k++] = aux->valores[j];
            }
        }
        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = 0;
    int qtdValores = 0;
    retorno = getDadosDeTodasEstruturasAuxiliares(vetorAux);
    if(retorno == SUCESSO) {
        for(int i = 0; i < TAM; i++) {
            if(vetorPrincipal[i] != NULL) {
                qtdValores += vetorPrincipal[i]->topo;
            }
        }
        insertion_sort(vetorAux, qtdValores);
    }
    return retorno;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    int retorno = 0;

    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        retorno = POSICAO_INVALIDA;
    else if(vetorPrincipal[posicao - 1] == NULL)
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else if(vetorPrincipal[posicao - 1]->tamanho + novoTamanho < 1)
        retorno = NOVO_TAMANHO_INVALIDO;
    else
    {
        int tamanhoResultante = vetorPrincipal[posicao - 1]->tamanho + novoTamanho;
        array * teste_0 = malloc(sizeof(array));
        if(teste_0 != NULL)
            teste_0->valores = malloc(sizeof(int) * tamanhoResultante);
        if(teste_0 == NULL || teste_0->valores == NULL)
            retorno = SEM_ESPACO_DE_MEMORIA;
        free(teste_0);
        free(teste_0->valores);
    }

    if(retorno == 0) {
        array * old_array = vetorPrincipal[posicao - 1];
        array * new_array = malloc(sizeof(array));
        int tamanhoResultante = old_array->tamanho + novoTamanho;
        new_array->valores = malloc(sizeof(int) * tamanhoResultante);
        new_array->tamanho = tamanhoResultante;
        copyIntArray(old_array->valores, new_array->valores, old_array->topo);
        
        if(tamanhoResultante >= old_array->tamanho)
            new_array->topo = old_array->topo;
        else if(tamanhoResultante < old_array->topo)
            new_array->topo = old_array->topo + novoTamanho;
        
        free(old_array->valores);
        free(old_array);

        vetorPrincipal[posicao - 1] = new_array;
        retorno = SUCESSO;
    }
    return retorno;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    int retorno = 0;

    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        retorno = POSICAO_INVALIDA;
    else if(vetorPrincipal[posicao - 1] == NULL)
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else if(vetorPrincipal[posicao - 1]->topo == 0)
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    else
        retorno = vetorPrincipal[posicao - 1]->topo;
    return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    No * head = malloc(sizeof(No));
    head->prox = NULL;

    for(int i = 0; i < TAM; i++)
    {
        if(vetorPrincipal[i] != NULL)
        {
            for(int j = 0; j < vetorPrincipal[i]->topo; j++)
            {
                No * new = malloc(sizeof(No));
                new->conteudo = vetorPrincipal[i]->valores[j];
                new->prox = NULL;

                if(head->prox == NULL)
                {
                    head->prox = new;
                }
                else
                {
                    No * last = head;
                    while(last->prox != NULL) last = last->prox;
                    last->prox = new;
                }
            }
        }
    }

    return head;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    No * last = inicio->prox;
    int i = 0;
    while(last != NULL)
    {
        vetorAux[i] = last->conteudo;
        last = last->prox;
        i = i + 1;  
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    No * remove = *inicio, *prox;

    while(remove != NULL)
    {
        prox = remove->prox;
        free(remove);
        remove = prox;
    }

    *inicio = NULL;
    return;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
    FILE * fp;
    int i;

    fp = fopen("db.txt", "r");

    for(i = 0; i < TAM; i++)
            vetorPrincipal[i] = NULL;

    if(fp == NULL) 
        return;

    int posicao, tamanho, topo;
    int numeroNaLinha;

    // Estava usando feof(fp) como condição de parada, mas não estava funcionando para leitura (ele lia uma vez a mais do deveria ler)
    // Não entendendo o motivo, perguntei ao GPT o erro, e ele disse que era o fato de que o feof() só pararia quando chegasse ao final,
    // mas que no arquivo provalvelmente não estava chegando.

    // Apesar dos pesares, a verificação foi sugerida pelo chat GPT, e eu a adotei. Não havia pensado nessa forma antes.
    while(fscanf(fp, "%d %d %d", &posicao, &tamanho, &topo) == 3) {
        // printf("\nSeção %d completa\n", posicao);
        // printf("posicao: %d tamanho: %d topo: %d valores: ", posicao, tamanho, topo);

        array * estrutura = malloc(sizeof(array));
        estrutura->valores = malloc(sizeof(int) * tamanho);

        for(i = 0; i < topo; i++) {
            fscanf(fp,"%d ", &numeroNaLinha);
            estrutura->valores[i] = numeroNaLinha;
            // printf("%d ", numeroNaLinha);
        }
        // printf("\n");
        
        estrutura->tamanho = tamanho;
        estrutura->topo = topo;
        vetorPrincipal[posicao] = estrutura;
    }

    fclose(fp);
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
    FILE * fp = fopen("db.txt", "w");


    // Dado que não é explícito que trabalhamos com pilha,
    // irei acessar todos os valores do array independentemente do topo.

    array * atual;

    for(int i = 0; i < 10; i++) {
        if(vetorPrincipal[i] != NULL) {
            atual = vetorPrincipal[i];
            fprintf(fp, "%d ", i);
            fprintf(fp, "%d ", atual->tamanho);
            fprintf(fp, "%d ", atual->topo);
            for(int j = 0; j < atual->topo; j++) {
                fprintf(fp, "%d ", atual->valores[j]);
            }
            fprintf(fp, "\n");
        }
    }


    for(int i = 0; i < TAM; i++) {
        if(vetorPrincipal[i] != NULL)
            free(vetorPrincipal[i]->valores);
    }
}

void insertion_sort(int * vetorAux, int size) {
    for(int j = 1; j < size; j++) {
            int i = j - 1;
            int key = vetorAux[j];
            while(i > -1 && vetorAux[i] > key) {
                vetorAux[i + 1] = vetorAux[i];
                i = i - 1;
            }
            vetorAux[i + 1] = key;
        }
}

void copyIntArray(int * arrayP, int * arrayS, int size) {
    for(int i = 0; i < size; i++)
        arrayS[i] = arrayP[i];
}