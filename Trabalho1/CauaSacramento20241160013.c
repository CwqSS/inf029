// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Cauã will Quadros Silva do Sacramento
//  email: cauawillqssacramento@gmail.com
//  Matrícula: 20241160013
//  Semestre: 2024.2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "CauaSacramento20241160013.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>

DataQuebrada quebraData(char data[]);

#pragma region Test_Functions
/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}
#pragma endregion

#pragma region First_Question
/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */

int q1(char data[])
{
    int datavalida = 1;
    //quebrar a string data em strings sDia, sMes, sAno
    int dia = 0, mes = 0, ano = 0;

    int tamString, qtdCaracteres;

    qtdCaracteres = 0;
    for(tamString = 0; data[tamString] != '/'; tamString++) {
        if(data[tamString] >= '0' && data[tamString] <= '9') {
            dia =  dia * 10 + data[tamString] - '0';
            qtdCaracteres = qtdCaracteres + 1;
        }
        else {
            datavalida = 0;
        }
    }

    if(qtdCaracteres > 2) {
        datavalida = 0;
    }

    qtdCaracteres = 0;
    for(tamString = tamString + 1; data[tamString] != '/' && datavalida; tamString++) {
        if(data[tamString] >= '0' && data[tamString] <= '9') {
            mes = mes * 10 + data[tamString] - '0';
            qtdCaracteres = qtdCaracteres + 1;
        }
        else {
            datavalida = 0;
        }
    }
    
    if(qtdCaracteres > 2) {
        datavalida = 0;
    }

    qtdCaracteres = 0;
    for(tamString = tamString + 1; data[tamString] && datavalida; tamString++) {
        if(data[tamString] >= '0' && data[tamString] <= '9') {
            ano = ano * 10 + data[tamString] - '0';
            qtdCaracteres = qtdCaracteres + 1;
        }
        else {
            datavalida = 0;
        }
    }

    if(qtdCaracteres == 2) {
        ano += 2000;
    }
    else if(qtdCaracteres != 4) {
        datavalida = 0;
    }

    int anoBissexto = 0;

    if(ano % 4 == 0) {
        if(ano % 100 != 0) {
            anoBissexto = 1;
        }
        else if(ano % 400) {
            anoBissexto = 1;
        }
    }

    if(mes > 0 && mes < 13 && dia > 0 && dia < 32) {
        if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30){
            datavalida = 0;
        }
        else if(mes == 2 && !anoBissexto && dia > 28) {
            datavalida = 0;
        }
    }
    else {
        datavalida = 0;
    }

    return datavalida;
}
#pragma endregion

#pragma region Second_Question
/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{
    //calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;

    if (q1(datainicial) == 0) {
        dma.retorno = 2;
        return dma;
    }
    else if (q1(datafinal) == 0) {
        dma.retorno = 3;
        return dma;
    } 
    else {
        //verifique se a data final não é menor que a data inicial
        int diaI = 0, mesI = 0, anoI = 0, totalDiasI = 0;
        int diaF = 0, mesF = 0, anoF = 0, totalDiasF = 0;
        int i, j, qtdCaracteres, ehAnoBissextoI, ehAnoBissextoF;

        for(i = 0; datainicial[i] != '/'; i++) {
            diaI = diaI * 10 + datainicial[i] - '0';
        }
        i += 1;

        for(i; datainicial[i] != '/'; i++) {
            mesI = mesI * 10 + datainicial[i] - '0';
        }
        i += 1;

        qtdCaracteres = 0;
        for(i; datainicial[i]; i++) {
            anoI = anoI * 10 + datainicial[i] - '0';
        }

        if(qtdCaracteres == 2)
            anoI += 2000;

        for(i = 0; datafinal[i] != '/'; i++) {
            diaF = diaF * 10 + datafinal[i] - '0';
        }
        i += 1;

        for(i; datafinal[i] != '/'; i++) {
            mesF = mesF * 10 + datafinal[i] - '0';
        }
        i += 1;

        qtdCaracteres = 0;
        for(i; datafinal[i]; i++) {
            anoF = anoF * 10 + datafinal[i] - '0';
            qtdCaracteres += 1;
        }
        
        if(qtdCaracteres == 2) 
            anoF += 2000;
        
        if((anoI > anoF) || (anoI == anoF && mesI > mesF) || (anoI == anoF && mesI == mesF && diaI > diaF)) {
            dma.retorno = 4;
            return dma;
        }

        // Lógica para cálculo de total de dias
        for(i = 0; i < anoI; i++) {
            int qtdDias = 365; 
            if(i % 4 == 0) {
                if(i % 100 != 0 || i % 400 == 0) {
                    qtdDias = 366;
                }
            }
            totalDiasI += qtdDias;
        }

        ehAnoBissextoI = 0;
        if(anoI % 4 == 0) {
            if(anoI % 100 != 0 || anoI % 400 == 0) {
                ehAnoBissextoI = 1;
            }
        }

        for(j = 0; j < mesI; j++) {
            int qtdDias = 31;
            if(j == 4 || j == 6 || j == 9 || j == 11)
                qtdDias = 30;
            else if(j == 2) {
                qtdDias = 28;
                if(ehAnoBissextoI)
                    qtdDias = 29;
            }
            totalDiasI += qtdDias;
        }

        totalDiasI += diaI;

        // Lógica para cálculo de total de dias
        for(i = 0; i < anoF; i++) {
            int qtdDias = 365; 
            if(i % 4 == 0) {
                if(i % 100 != 0 || i % 400 == 0) {
                    qtdDias = 366;
                }
            }
            totalDiasF += qtdDias;
        }

        ehAnoBissextoF = 0;
        if(anoF % 4 == 0) {
            if(anoF % 100 != 0 || anoF % 400 == 0) {
                ehAnoBissextoF = 1;
            }
        }

        for(j = 0; j < mesF; j++) {
            int qtdDias = 31;
            if(j == 4 || j == 6 || j == 9 || j == 11)
                qtdDias = 30;
            else if(j == 2) {
                qtdDias = 28;
                if(ehAnoBissextoF)
                    qtdDias = 29;
            }
            totalDiasF += qtdDias;
        }

        totalDiasF += diaF;
        
        //calcule a distancia entre as datas
        int distancia = totalDiasF - totalDiasI;
        dma.qtdAnos = 0;
        dma.qtdMeses = 0;
        dma.qtdDias = 0;

        dma.qtdAnos = distancia / 365;
        distancia = distancia % 365;

        dma.qtdMeses = distancia / 30;
        distancia = distancia % 30;

        if(mesI == 1 || mesI == 3 || mesI == 5 || mesI == 7 || mesI == 8 || mesI == 10 || mesI == 12) {
            if (dma.qtdMeses > 0 && distancia >= 0) {
                dma.qtdMeses -= 1;
                distancia += 30;
                dma.qtdMeses = distancia / 31;
                distancia = distancia % 31;
            }
        }
        
        dma.qtdDias = distancia;

        if(ehAnoBissextoI && dma.qtdAnos == 1 && dma.qtdDias >= 1) {
            dma.qtdDias -= 1;
        }

        //se tudo der certo
        dma.retorno = 1;
        return dma;
    }
    
}
#pragma endregion

#pragma region Third_Question
/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
*/
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;

    for(int i = 0; texto[i]; i = i + 1) {
        int c1 = texto[i];
        int c2 = c;

        // if(c1 == 'á' || c1 == 'à' || c1 == 'â' || c1 == 'ä' || c1 == 'ã') {
        //     c1 = 'a';
        // }
        // else if (c1 == 'é' || c1 == 'è' || c1 == 'ê' || c1  == 'ë') {
        //     c1 = 'e';
        // }
        // else if (c1 == 'í' || c1 == 'ì' || c1 == 'î' || c1 == 'ï') {
        //     c1 = 'i'
        // }
        // else if(c1 == 'ó' || c1 == 'ò' || c1 == 'ô' || c1 == 'ö' || c1 == 'õ') {
        //     c1 = 'o';
        // }
        // else if(c1 == 'ú' || c1 == 'ù' || c1 == 'û' || c1 == 'ü') {
        //     c1 = 'u'
        // }
        // else if(c1 = 'ç') {
        //     c1 = 'c';
        // }
        // else if(c1 == 'Á' || c1 == 'À' || c1 == 'Â' || c1 == 'Ä' || c1 == 'Ã') {
        //     c1 = 'A';
        // }
        // else if (c1 == 'É' || c1 == 'È' || c1 == 'Ê' || c1  == 'Ë') {
        //     c1 = 'E';
        // }
        // else if (c1 == 'Í' || c1 == 'Ì' || c1 == 'Î' || c1 == 'Ï') {
        //     c1 = 'I'
        // }
        // else if(c1 == 'Ó' || c1 == 'Ò' || c1 == 'Ô' || c1 == 'Ö' || c1 == 'Õ') {
        //     c1 = 'O';
        // }
        // else if(c1 == 'Ú' || c1 == 'Ù' || c1 == 'Û' || c1 == 'Ü') {
        //     c1 = 'U'
        // }
        // else if(c1 = 'Ç') {
        //     c1 = 'C';
        // }

        if(!isCaseSensitive) {
            if(c1 >= 'a' && c1 <= 'z') {
                c1 = c1 - 'a' + 'A';
            }
            if(c2 >= 'a' && c2 <= 'z') {
                c2 = c2 - 'a' + 'A';
            }
        }

        if(c1 == c2) {
            qtdOcorrencias += 1;
        }
    }

    return qtdOcorrencias;
}
#pragma endregion

#pragma region Fourth_Question
/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;
    int indice = 0;

    for(int i = 0; strTexto[i]; i++) {
        int j = 0;
        if(strTexto[i] == strBusca[j]) {
            int k = i;
            while(strTexto[k] == strBusca[j])  {
                k = k + 1;
                j = j + 1;
            }
            if(strBusca[j] == '\0') {
                posicoes[indice] = i + 1;
                indice += 1;
                posicoes[indice] = k;
                indice += 1;
                qtdOcorrencias += 1;
                i += j - 1; 
            }
        }
    }

    return qtdOcorrencias;
}
#pragma endregion

#pragma region Fifth_Question
/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
    int aux = 0;

    while(num > 0) {
        aux = num % 10 + aux * 10;
        num = num / 10;
    }
    num = aux;

    return num;
}
#pragma endregion

#pragma region Sixth_Question
/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0;
    int qtdDigitos = 1;
    int aux = numerobusca;

    while(aux / 10 > 0) {
        aux /= 10;
        qtdDigitos += 1;
    }

    int moduloBusca = 1;
    for(int i = 0; i < qtdDigitos; i++)
        moduloBusca = moduloBusca * 10;

    do {
        int resto = numerobase % moduloBusca;
        if(resto == numerobusca) {
            qtdOcorrencias += 1;
            numerobase = numerobase / moduloBusca;
        }
        else {
            numerobase = numerobase / 10;
        }
    } while(numerobase > 0);

    return qtdOcorrencias;
}
#pragma endregion

DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
        return dq;
    }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}
