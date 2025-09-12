#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void terminarPrograma(char mensaje[]) {
    printf("%s\n", mensaje);
    exit(EXIT_FAILURE);
}

int tipoOperando(int operando){
    return (operando >> 24) & (0x00000003);
}