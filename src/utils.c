#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void terminarPrograma(char mensaje[]) {
    printf("%s\n", mensaje);
    exit(EXIT_FAILURE);
}

int tipoOperando(int operando){
    return (operando >> 24) & (0x00000003);
}

int terminaCon(char *palabra, char *sufijo) {
    if (palabra == NULL || sufijo == NULL)
        return 0;

    int tamPalabra = strlen(palabra);
    int tamSufijo = strlen(sufijo);
    
    if (tamSufijo > tamPalabra)
        return 0;

    return strcmp(palabra + tamPalabra - tamSufijo, sufijo) == 0;
}

int empiezaCon(char *palabra, char *prefijo) {
    if (palabra == NULL || prefijo == NULL)
        return 0;

    int tamPrefijo = strlen(prefijo);

    return strncmp(palabra, prefijo, tamPrefijo) == 0;
}

void mostrarArrStr(char *array[], int n) {
    for (int i = 0; i < n; i++)
        printf("%s\n", array[i]);
}

void mostrarArrInt(int array[], int n) {
    for (int i = 0; i < n; i++)
        printf("[%d]: %08X\n", i, array[i]);
}

void mostrarArrChar(char array[], int n) {
    for (int i = 0; i < n; i++)
        printf("[%d]: %02X\n", i, array[i]);
}

void swap2Bytes(unsigned short *num) {
    int res;
    res = (*num) >> 8;
    res |= (*num) << 8;
    *num = res;
}
