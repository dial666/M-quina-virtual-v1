#include <stdio.h>
#include "mem_reg_io.h"
#include "constantes.h"
#include "utils.h"

void cargarLAR(int dirLogica, int registros[]){
    registros[LAR_INDEX] = dirLogica;
}

//valida que el indice de la tabla en la dirección lógica sea menor a 8 y que la tabla tenga un valor válido en esa posición
void verificarIndiceSegmento(int indiceSegmento, int tablaSegmentos[]) {
    if (!(indiceSegmento >= 0 && indiceSegmento < TAM_TABLA_SEGMENTOS && tablaSegmentos[indiceSegmento] > -1))
        terminarPrograma("se intentó acceder a un bloque de memoria inexistente");
}

void cargarMAR(int cantBytes, int registros[], int tablaSegmentos[]){
    int dirLogica = registros[LAR_INDEX];
    int offset = dirLogica & 0x0000FFFF;
    int segmentIndex = dirLogica >> 16;

    verificarIndiceSegmento(segmentIndex, tablaSegmentos);

    int dirBase = tablaSegmentos[segmentIndex] >> 16;
    int tamanioSegmento = tablaSegmentos[segmentIndex] & 0x0000FFFF;

    int dirFisica = dirBase + offset;
    printf("direccion fisica: %08x\n", dirFisica);
    printf("direccion base: %08x\n", dirBase);
    printf("direccion limite acceso %08x\n", dirFisica + cantBytes);
    printf("direccion limite segmento: %08x\n", dirBase + tamanioSegmento);
    if( (dirBase <= dirFisica) && ( (dirBase + tamanioSegmento) >= (dirFisica + cantBytes) ) ){
        registros[MAR_INDEX] = (cantBytes << 16) | ((dirFisica) & (0x0000FFFF)); //CREO QUE EL ULTIMO & ESTA DE MAS PERO REVISAR
        //printf("cantBytes: %X MAR2: %X\n",cantBytes, registros[MAR_INDEX]);
    }
    else
        terminarPrograma("segmentation fault");

}

void leerMemoria(char memoria[], int registros[]){
    
    int cantBytes = registros[MAR_INDEX] >> 16;
    int direccion = registros[MAR_INDEX] & 0x00FF;
    //printf("MAR: %X memoria[%d]: %X\n", registros[MAR_INDEX], direccion, memoria[direccion]);

    int valor = 0;
    for(int i = 0; i < cantBytes; i++){
        valor = (valor << 8) | (memoria[direccion + i] & 0x000000FF);  // no mantiene signo de valor leido
        //printf("valor %X i: %d\n", valor, i);
    }

    valor = valor << (32 - 8*cantBytes);  //restora signo
    valor = valor >> (32 - 8*cantBytes);
    registros[MBR_INDEX] = valor;
    //printf("MBR dsp: %X\n", registros[MBR_INDEX]);
    
}

void cargarMBR(int registros[], int valor){
    registros[MBR_INDEX] = valor;
}

void escribirMemoria(char memoria[], int registros[], int tablaSegmentos[]){
    int cantBytes = registros[MAR_INDEX] >> 16;
    int direccion = registros[MAR_INDEX] & 0x00FF;

    int valor = registros[MBR_INDEX];

    //printf("cantBytes: %X direccion:%X valor:%X\n", cantBytes, direccion, valor);
    for(int i = 1; i <= cantBytes; i++)
        memoria[direccion + cantBytes - i] = (valor << (32-i*8)) >> 24; //shiftea el byte que quiero escribir hasta el byte mas significativo y luego lo shiftea hasta el byte menos significativo
        //creo que el char trunca y toma el byte menos significativo del int, asi que tambien podria ser:
        //memoria[direccion + cantBytes - i] = valor >> (i*8-8);
    printf("memoria en %d: %d, %d, %d, %d\n", direccion, memoria[direccion], memoria[direccion+1], memoria[direccion+2], memoria[direccion+3]);

}

void store(char memoria[], int registros[], int tablaSegmentos[], int dirLogica, int cantBytes, int valor){
    cargarLAR(dirLogica, registros);
    cargarMAR(cantBytes, registros, tablaSegmentos);
    cargarMBR(registros, valor);
    escribirMemoria(memoria, registros, tablaSegmentos);
}

void escribirMemoriaRegistro(char memoria[], int registros[], int tablaSegmentos[], int operando, int valor){ //no se puede llamar con operando de tipo inmediato
    int tipo = (operando >> 24) & (0x00000003);
    int valor_logico = (operando << 8) >> 8;

    //printf("ESCRIBIR MEMORIA, operando:%X\n", operando);
    //printf("tipo: %X valor_logico:%X\n", tipo, valor_logico);
    if (tipo == 1)
        registros[valor_logico] = valor; //no contempla registro inexistente
    else if(tipo == 3){
        int registro = (valor_logico >> 16) & 0x1F;
        int offset = (valor_logico << 16) >> 16;

        int offsetRegistro = registro & 0xFFFF;
        if (offset + offsetRegistro > 0xFFFF)
            terminarPrograma("segmentation fault: offset supera rango permitido");

        int dirLogica = registros[registro] + offset;
        
        store(memoria, registros, tablaSegmentos, dirLogica, 4, valor); //!!!!!!!!!! deberia escribir 2?
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
    else
        terminarPrograma("Solo es posible escribir en un registro o direccion de memoria");
}