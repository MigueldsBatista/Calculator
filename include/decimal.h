#ifndef __DECIMAL_H__
#define __DECIMAL_H__


struct Node;
//push to a stack
void push(int data, struct Node **top);

//pop from a stack
void pop(struct Node **top);
//return an N number to the power of E
int power(int base, int expoente);

//returns the length of a linked list
int length(struct Node *top);

void ClearNode(struct Node **top);
void PrintNode(struct Node *top);

//returns the value of a binary number stored in a stack as a number
int BinToDecimal(struct Node *top);

//converts a number to a base X 
void DecimalToBaseX(int numeroConvertido, int baseNumerica, struct Node **top);

//convert a binary number to X bits
void AddBits(int numeroBits, struct Node **top);

//converts a decimal number to BCD format
void DecimalToBCD(int numeroConvertido, struct Node **top);

//returns the position of the last digit one in a linked list
int LastDigitOneInBin(struct Node *top);

//converts a normal chain of bits to two's complement

void TwosComplement(int lastOnePos, struct Node**top);//converte um binario para sua versão negativa com complemento a 2
void InsertLast(float target, struct Node** start); 
void DeleteFirst(struct Node** start);


#endif
