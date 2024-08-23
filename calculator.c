#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
/*Miguel de Sousa Batista 3A CC
21/08/24
1 iteração ~ 9pm 21/08

2 iteração ~ 10pm 22/08
Resolvi usar listas encadeadas para essa tarefa para exercitar meus conhecimentos que também vão ser usados na cadeira de Algoritimos e estruturas de dados */


struct Stack {
    int data;
    struct Stack* next; // ponteiro para a próxima estrutura
};


void push (int data, struct Stack **top) {
    struct Stack *newNode = (struct Stack*)malloc(sizeof(struct Stack)); // aloca memória para o novo nó
    newNode->data=data;
    newNode->next=*top;
    *top=newNode;

}

int power(int base, int expoente){
    int resultado=1;
    for (size_t i = 0; i < expoente; i++)
    {
        resultado=resultado*base;
    }
    return resultado;
}

void pop(struct Stack **top){
    struct Stack *delete=*top;
    (*top)=(*top)->next;
    free(delete);
}

void ClearStack(struct Stack **top){
    while(*top){
        pop(top);
    }
}
void PrintStack(struct Stack *top){
    struct Stack *walk=top;
    while(walk){
    if(
        walk->data==67|| //'A'
        walk->data==68|| //'B'
        walk->data==69|| //'C'
        walk->data==70|| //'D'
        walk->data==71||// 'E'
        walk->data==72)// 'F'
    {
        printf("[%c]", walk->data);
    } 
    else {
    printf("[%d]", walk->data);
    }
    walk=walk->next;   

    }
}

int BinToDecimal(struct Stack *top){
struct Stack *walk = (struct Stack*)malloc(sizeof(struct Stack)); // aloca memória para o novo nó
walk=top;
int len=0;
int resultado=0;

while(walk){
    len++;
    walk=walk->next;

    
}
walk=top;
while (walk)
{
resultado=resultado+(walk->data*power(2, --len));
walk=walk->next;
}
return resultado;

}

void DecimalToBin(int numeroConvertido, struct Stack **top){
    int restoDiv;
    while(numeroConvertido!=0){
        restoDiv=numeroConvertido%2;
        numeroConvertido=numeroConvertido/2;
        push(restoDiv, top);

    }
}

void DecimalToOcto(int numeroConvertido, struct Stack **top){
    int restoDiv;
    while(numeroConvertido!=0){
        restoDiv=numeroConvertido%8;
        numeroConvertido=numeroConvertido/8;
        push(restoDiv, top);
    }
}
void DecimalToHex(int numeroConvertido, struct Stack **top){
    int restoDiv;
    while(numeroConvertido!=0){
        restoDiv=numeroConvertido%16;
        if(restoDiv>=10){
            restoDiv='A'+restoDiv-10;//Conversão pro caractere Alfabético
        }
        numeroConvertido=numeroConvertido/16;
        push(restoDiv, top);
    }
}
void DecimalToBCD(int numeroConvertido, struct Stack **top){
    int digito=0;
    while(numeroConvertido!=0){
        digito=numeroConvertido%10;
        DecimalToBin(digito, top);
        printf("digito atual [%d]\n", digito);
        numeroConvertido=numeroConvertido/10;

    }
}
int main() {
    int option;
    int num;
    struct Stack *top=NULL;
    do {
        printf("Calculadora Programador Didática\n");
        printf("Escolha uma das opções abaixo:\n");
        printf("1 - Converter base 10 para:\n");
        printf("   a) Base 2\n");
        printf("   b) Base 8\n");
        printf("   c) Base 16\n");
        printf("   d) Código BCD\n");
        printf("2 - Converter base 10 para base com sinal (16 bits) (Complemento a 2)\n");
        printf("3 - Converter número real em decimal para float e double\n");
        printf("0 - Sair\n");
        printf("Digite sua opção: ");
        scanf("%d", &option);

        if(option == 0) {
            printf("Saindo da calculadora...\n");
            break;
        }

        printf("Digite um número em base 10: ");
        scanf("%d", &num);

        switch(option) {
            case 1:
                if(top) ClearStack(&top);//Caso não seja a primeira iteração

                system("clear");
                DecimalToBin(num, &top);
                printf("Base Binária:");
                PrintStack(top);
                printf("\n");
    
                printf("Numero reconvertido: %d", BinToDecimal(top));
                printf("\n");

                ClearStack(&top);//Vamos reutilizar a pilha

                printf("Base Octo: ");
                DecimalToOcto(num, &top);
                PrintStack(top);
                printf("\n");

                ClearStack(&top);//Vamos reutilizar a pilha novamente

                printf("Base Hexa: ");
                printf("[0][x]");
                DecimalToHex(num, &top);
                PrintStack(top);
                printf("\n");

                ClearStack(&top);//Vamos reutilizar a pilha novamente

                printf("Base BCD: ");
                DecimalToBCD(num, &top);
                PrintStack(top);
                break;

            /*case 2:
                printf("Converter base 10 para base com sinal (Complemento a 2, 16 bits)\n");
                break;

            case 3:
                printf("Converter número real em decimal para float e double\n");
                break; */

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        printf("\n");

    } while(option != 0);

    return 0;
}

