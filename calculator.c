#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
/*Miguel de Sousa Batista 3A CC
21/08/24
1 iteração ~ 9pm 21/08

2 iteração ~ 10pm 22/08

3 iteração ~ 10am 23/08

4 iteração 25/08 ~ 21:30 pm
Resolvi usar listas encadeadas para essa tarefa para exercitar meus conhecimentos que também vão ser usados na cadeira de Algoritimos e estruturas de dados */

//o que eu preciso pra reverter uma lista?
/* 
Vamos supor a lista 2 -> 3 -> 4
                    3 -> 2 -> 4
                    3 -> 4 -> 2

talvez enquanto a head seja diferente de nulo
eu continue fazendo as inversoes
current=head=2 


*/
struct Node {
    int data;
    struct Node* next; // ponteiro para a próxima estrutura
};


void push (int data, struct Node **top) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node)); // aloca memória para o novo nó
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

void pop(struct Node **top){
    struct Node *delete=*top;
    (*top)=(*top)->next;
    free(delete);
}

void ClearNode(struct Node **top){
    while(*top){
        pop(top);
    }
}
void PrintNode(struct Node *top){
    while(top){

    if(top->data>9){
        top->data='A'+(top->data-10);//Conversão pra considerar os casos hexadecimais
        printf("[%c]", top->data);
    }
    else {
    printf("[%d]", top->data);
    }
    top=top->next;   
} 
}

int length(struct Node *top){//retorna o tamanho de uma lista dinamica
int len=1;

while(top){
    len++;
    top=top->next;
}
return len;

} 
int BinToDecimal(struct Node *top){

struct Node *walk=top;

int len=length(top);

int resultado=0;

while (walk)
{
resultado=resultado+(walk->data*power(2, --len));
walk=walk->next;
}
return resultado;

}
void DecimalToBaseX(int numeroConvertido,int baseNumerica, struct Node **top){//converte um numero decimal para uma base determinada pelo usuario e joga o valor na Pilha top
    int restoDiv;

    while(numeroConvertido!=0){
        restoDiv=numeroConvertido%baseNumerica;
        numeroConvertido=numeroConvertido/baseNumerica;
        push(restoDiv, top);

    }
}

void ConvertBinToXbits(int numeroBits, struct Node **top){//função que recebe uma pilha binaria e converte para a quantidade de bits desejada pra representação

numeroBits=numeroBits-length(*top);//ex o numero tem 4 bits e precisa ser representado em 16, ou seja precisamos add 12 bits

for(int i=0;i<numeroBits;i++){
push(0, top);
}

}
void DecimalToBCD(int numeroConvertido, struct Node **top){//Recebe um numero decimal e retorna o numero em Binary Coded Decimal
    int digito=0;
    while(numeroConvertido!=0){
        digito=numeroConvertido%10;
        DecimalToBaseX(digito,2, top);//base binaria
        ConvertBinToXbits(4, top);

        numeroConvertido=numeroConvertido/10;
        
    }
}

int LastDigitOneInBin(struct Node *top){//retorna a posição do ultimo valor 1 em uma lista para que eu consiga converter um bin para negativo com complemento a 2
    int len=0;
    int lastDigitOnePos=-1;
    while(top){
        len++;
        if(top->data==1){
            lastDigitOnePos=len;
        }
        top=top->next;
    }
    return lastDigitOnePos;
}
void BinToSignedBin(int lastOnePos, struct Node**top){//converte um binario para sua versão negativa com complemento a 2
    struct Node *walk = *top;
    int len = 1;

    // A função percorre a lista e inverte os bits antes da posição do último bit 1
    while (walk) {
        if (len < lastOnePos) {
            if (walk->data == 0) {
                walk->data = 1;
            } else if (walk->data == 1) {
                walk->data = 0;
            }
        }
        len++;
        walk = walk->next;
    }
}


int main() {
    int option;
    int num;
    char signal;
    struct Node *top=NULL;
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
                if(top) ClearNode(&top);//Caso não seja a primeira iteração

                DecimalToBaseX(num,2, &top);
                printf("Base Binária:");
                PrintNode(top);
                printf("\n");
    
                printf("Numero reconvertido: %d", BinToDecimal(top));
                printf("\n");

                ClearNode(&top);//Vamos reutilizar a pilha

                printf("Base Octo: ");
                DecimalToBaseX(num,8, &top);
                PrintNode(top);
                printf("\n");

                ClearNode(&top);//Vamos reutilizar a pilha novamente

                printf("Base Hexa: ");
                printf("[0][x]");
                DecimalToBaseX(num,16, &top);
                PrintNode(top);
                printf("\n");

                ClearNode(&top);//Vamos reutilizar a pilha novamente

                printf("Base BCD: ");
                DecimalToBCD(num, &top);
                PrintNode(top);
                break;

            case 2:
                system("clear");
                printf("Digite um número em base 10 e o seu sinal (+ ou -) ex -10, +23: ");
                scanf(" %c%d", &signal, &num);
                ClearNode(&top);

                if(signal=='+'){
                    DecimalToBaseX(num,2, &top);//base binaria
                    ConvertBinToXbits(16, &top);
                }
                else if(signal=='-'){
                    DecimalToBaseX(num,2, &top);//base binaria
                    ConvertBinToXbits(16, &top);                    
                    int lastOnePos= LastDigitOneInBin(top);
                    BinToSignedBin(lastOnePos, &top);
                }
                else printf("Sinal inválido!");

                printf("Numero convertido pra complemento a 2  16 bits\n");
                PrintNode(top);
                printf("\n");

                break;

            case 3:
                printf("Converter número real em decimal para float e double\n");


                break; 

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        printf("\n");

    } while(option != 0);

    return 0;
}

