#include <stdio.h>
#include "constantes.h"
#include "disassembler.h"

void mostrarValorEnHexa(int valor, int n) {
    int i;
    for (i=0; i<n; i++)
        printf("%02X ", (valor >> ((n-1-i)*8)) & 0xFF);
}

void mostrarOperando(int operando, int tipoOperando) {
    if (tipoOperando==1)
        printf("%s  ", NOMBRE_REG[operando & 0x1F]);
    else
        if (tipoOperando==2)
            printf("%d  ", (operando << 16) >> 16);
        else
            if (tipoOperando==3) {
                printf("[%s", NOMBRE_REG[(operando >> 16) & 0x1F]);
                int offset = (operando << 16) >> 16;
                (offset>=0)? printf("+%d]  ", offset): printf("%d]  ", offset);
            }
}

void mostrarDisassembler(int instruccion, int tipo1, int tipo2, int registros[]) {
    printf("[%04X]: ", registros[IP_INDEX]);
    mostrarValorEnHexa(instruccion, 1);
    mostrarValorEnHexa(registros[OP1_INDEX], tipo1);
    mostrarValorEnHexa(registros[OP2_INDEX], tipo2);
    printf("| %s  ", MNEMONICOS[registros[OPC_INDEX]]);
    if (tipo2!=0) {
        mostrarOperando(registros[OP2_INDEX], tipo2);
        printf(",  ");
    }
    mostrarOperando(registros[OP1_INDEX], tipo1);
    printf("\n");
}
