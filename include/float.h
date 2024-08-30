#ifndef __FLOAT_H__
#define __FLOAT_H__

#define FLOAT_EXPONENT_BIAS 127
#define FLOAT_MANTISSA_BITS 23

#define DOUBLE_MANTISSA_BITS 52
#define DOUBLE_EXPONENT_BIAS 1023

struct Node;

void DeleteFirstFloat(struct Node** start);

void InsertLastFloat(float target, struct Node** start); // Note que o tipo `int` deve ser `float` para consistência

int Length(struct Node *top); //retorna o tamanho de uma lista dinamica

int FractionBin(float fracao, struct Node **top, int mantissaBits);

void AddExponent(int exp, int bias, struct Node **top);

void AddSignal(char signal, struct Node **top);

#endif // !1
