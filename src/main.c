#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include "decimal.h"
#include "float.h"

/*Miguel de Sousa Batista 3A CC
21/08/24
1 iteração ~ 9pm 21/08

2 iteração ~ 10pm 22/08

3 iteração ~ 10am 23/08

4 iteração 25/08 ~ 21:30 pm
Resolvi usar listas encadeadas para essa tarefa para exercitar meus conhecimentos que também vão ser usados na cadeira de Algoritimos e estruturas de dados */

// Protótipos das funções
//Stack functions


//linked list used to create Stacks, Queues, and dynamic lists

//gcc src/*.c -I include -o programa




int main() {
    int option;
    int num;
    char signal;
    struct Node *top = NULL;
    float f;
    double d;

    do {
        printf("Calculadora Programador Didática\n");
        printf("Escolha uma das opções abaixo:\n");
        printf("1 - Converter base 10 para:\n");
        printf("   a) Base 2\n");
        printf("   b) Base 8\n");
        printf("   c) Base 16\n");
        printf("   d) Código BCD\n");
        printf("2 - Converter base 10 para base com sinal (16 bits) (Complemento a 2)\n");
        printf("3 - converter real em decimal para float e double, mostrando os respectivos bits de sinal , expoente, expoente com viés e fração \n");
        printf("0 - Sair\n");
        printf("Digite sua opção: ");
        scanf("%d", &option);

        if(option == 0) {
            printf("Saindo da calculadora...\n");
            break;
        }

        switch(option) {
            case 1:
                system("clear");
                printf("Digite um número em base 10: ");
                scanf("%d", &num);
                if(top) ClearNode(&top); //Caso não seja a primeira iteração

                DecimalToBaseX(num, 2, &top);
                printf("Base Binária:");
                PrintNode(top);
                printf("\n");

                printf("Numero reconvertido: %d", BinToDecimal(top));
                printf("\n");

                ClearNode(&top); //Vamos reutilizar a pilha

                printf("Base Octo: ");
                DecimalToBaseX(num, 8, &top);
                PrintNode(top);
                printf("\n");

                ClearNode(&top); //Vamos reutilizar a pilha novamente

                printf("Base Hexa: ");
                printf("[0][x]");
                DecimalToBaseX(num, 16, &top);
                PrintNode(top);
                printf("\n");

                ClearNode(&top); //Vamos reutilizar a pilha novamente

                printf("Base BCD: ");
                DecimalToBCD(num, &top);
                PrintNode(top);
                break;

            case 2:
                system("clear");
                printf("Digite um número em base 10 e o seu sinal (+ ou -) ex -10, +23: ");
                scanf(" %c%d", &signal, &num);
                ClearNode(&top);

                if(signal == '+'){
                    DecimalToBaseX(num, 2, &top); //base binaria
                    AddBits(16-length(top), &top);
                }
                else if(signal == '-'){
                    DecimalToBaseX(num, 2, &top); //base binaria
                    AddBits(16-length(top), &top);
                    int lastOnePos = LastDigitOneInBin(top);
                    TwosComplement(lastOnePos, &top);
                }
                else {
                    printf("Sinal inválido!");
                }

                printf("Numero convertido pra complemento a 2 16 bits\n");
                PrintNode(top);
                printf("\n");

                break;

            case 3:
                system("clear");
                printf("digite um numero decimal e o seu sinal (+ ou -) ex -10.60, +23.40:\n ");
                scanf(" %c%f", &signal, &f);
                d=f;

                ClearNode(&top);
                DecimalToBaseX((int)f, 2, &top);//convertemos a parte inteiro para binario
                float fraction = f - (int)f;

                int exp=FractionBin(fraction, &top, FLOAT_MANTISSA_BITS);//a partir da parte inteira adicionamos a parte fracionaria que vai compor a mantissa
                int fracaoConvertida=BinToDecimal(top);

                AddExponent(exp, 127, &top); //Adiciona o expoente
                AddSignal(signal, &top);

                printf("Float: %f \nExpoente(+127): %d\n Sinal: %c \nMantissa: %d\n", f, exp+FLOAT_EXPONENT_BIAS, signal, fracaoConvertida);

                PrintNode(top);


                printf("\n");
                //agora para double
                ClearNode(&top);
                DecimalToBaseX((int)d, 2, &top);//convertemos a parte inteiro para binario
                fraction = d - (int)d;

                exp=FractionBin(fraction, &top, DOUBLE_MANTISSA_BITS);//a partir da parte inteira adicionamos a parte fracionaria que vai compor a mantissa
                fracaoConvertida=BinToDecimal(top);

                AddExponent(exp, DOUBLE_EXPONENT_BIAS, &top); //Adiciona o expoente
                AddSignal(signal, &top);

                printf("Double: %f \nExpoente(+1023): %d\n Sinal: %c \nMantissa: %d\n", f, exp+DOUBLE_EXPONENT_BIAS, signal, fracaoConvertida);

                PrintNode(top);

                // Função para conversão de float e double ainda não implementada
                break; 

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        printf("\n");

    } while(option != 0);

    return 0;
}

// Corpo das funções

