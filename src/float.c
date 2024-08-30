#include "float.h"
#include <stdio.h>
#include <stdlib.h>
#include "decimal.h"


struct Node {
    int data;
    struct Node* next; 
};

int FractionBin(float fracao, struct Node **top, int mantissaBits) {
    DeleteFirst(top);//Deixamos aqui so a parte fracionaria
    int len = Length(*top); 
    for (int i = 0; i < mantissaBits - len; i++) {

        fracao = fracao * 2;
        if (fracao >= 1) {
            fracao = fracao - 1; // Subtrair 1 para manter apenas a parte fracionária
            InsertLast(1, top);  // Corrigido: usar o valor 1

            // Checa se o fracao é zero após a subtração
            if (fracao == 0) {
                // Preenche o resto com zeros até atingir 23 bits
                AddBits(mantissaBits - Length(*top), top);
                return len; // Retorna o expoente aqui para sair da função corretamente
            }
        } else {
            InsertLast(0, top);  // Insere o valor 0
        }

        // Atualiza a fração para a próxima iteração
    }

    return len;
}

int Length(struct Node *top) { 
    int len = 0;
    
    while (top) {
        len++;
        top = top->next;
    }
    return len;
}




void AddExponent(int exp, int bias, struct Node **top){
    DecimalToBaseX(exp+bias, 2, top);
}

void AddSignal(char signal, struct Node **top) {
    if (signal == '+') {
        push(0, top);
    } else if (signal == '-') {
        push(1, top);
    } else {
        printf("Sinal inválido!");
    }
}