#include "decimal.h"
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next; 
};

void push(int data, struct Node **top) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node)); // aloca memória para o novo nó
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}


int power(int base, int expoente){
    int resultado = 1;
    for (int i = 0; i < expoente; i++) {
        resultado = resultado * base;
    }
    return resultado;
}

void pop(struct Node **top){
    struct Node *delete = *top;
    (*top) = (*top)->next;
    free(delete);
}

void ClearNode(struct Node **top){
    while(*top){
        pop(top);
    }
}

void PrintNode(struct Node *top){
    while(top){
        if(top->data > 9){
            top->data = 'A' + (top->data - 10); //Conversão pra considerar os casos hexadecimais
            printf("[%c]", top->data);
        }
        else {
            printf("[%d]", top->data);
        }
        top = top->next;
    }
}

int length(struct Node *top) { //retorna o tamanho de uma lista dinamica
    int len = 0;

    
    while(top) {
        len++;
        top = top->next;
    }
    return len;
}


int BinToDecimal(struct Node *top){
    int len = length(top);
    int resultado = 0;

    while (top) {
        resultado = resultado + (top->data * power(2, --len));
        top = top->next;
    }
    return resultado;
}

void DecimalToBaseX(int numeroConvertido, int baseNumerica, struct Node **top) { //converte um numero decimal para uma base determinada pelo usuario e joga o valor na Pilha top
    int restoDiv;

    while(numeroConvertido != 0) {
        restoDiv = numeroConvertido % baseNumerica;
        numeroConvertido = numeroConvertido / baseNumerica;
        push(restoDiv, top);
    }
}

void AddBits(int numeroBits, struct Node **top) { //função que recebe uma pilha binaria e converte para a quantidade de bits desejada pra representação

    for(int i = 0; i < numeroBits; i++) {
        push(0, top);
    }
}

void DecimalToBCD(int numeroConvertido, struct Node **top) { //Recebe um numero decimal e retorna o numero em Binary Coded Decimal
    int digito = 0;
    int len;
    struct Node *temp=NULL;
    while(numeroConvertido != 0) {
        digito = numeroConvertido % 10;

        if(digito==0){
            AddBits(4, top);
        }
   
        else{
            DecimalToBaseX(digito, 2, top); //base binaria
            DecimalToBaseX(digito, 2, &temp);

            len=length(temp);//len of the current bit

            AddBits(4-len, top);

            ClearNode(&temp);
        }

        numeroConvertido = numeroConvertido / 10;
    }
}

int LastDigitOneInBin(struct Node *top) {
    int len = 0;
    int lastDigitOnePos = -1;
    while (top) {
        len++;
        if (top->data == 1) {
            lastDigitOnePos = len;
        }
        top = top->next;
    }
    return lastDigitOnePos;
}
void TwosComplement(int lastOnePos, struct Node**top) { //converte um binario para sua versão negativa com complemento a 2
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


void InsertLast(float target, struct Node** start){
    struct Node *newNode;
    struct Node *temp1;
    newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->data=target;
    newNode->next=NULL;//sempre vai ser null ja que estamos inserindo no final!!
    temp1=*start;//vamos para inicio da lista
    while(temp1->next) {
        temp1=temp1->next;
    }   temp1->next=newNode;
}

void DeleteFirst(struct Node** start) {
    if (*start != NULL) {  // Verifica se a lista não está vazia
        struct Node* temp = *start;  // Armazena o ponteiro para o nó inicial
        *start = (*start)->next;  // Atualiza o ponteiro inicial para o próximo nó
        free(temp);  // Libera a memória do nó inicial
    }
}
