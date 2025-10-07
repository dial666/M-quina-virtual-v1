#ifndef UTILS_H
#define UTILS_H

void terminarPrograma(char mensaje[]);
int tipoOperando(int operando);
int terminaCon(char *palabra, char *sufijo);
int empiezaCon(char *palabra, char *prefijo);
void mostrarArrStr(char *array[], int n);
void mostrarArrInt(int array[], int n);
void mostrarArrChar(char array[], int n);
void swap2Bytes(unsigned short *num);

#endif