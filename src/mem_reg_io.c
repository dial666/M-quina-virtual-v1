#include <stdio.h>
#include "mem_reg_io.h"
#include "constantes.h"
#include "utils.h"

/**
 * @brief Carga en el LAR una dirección lógica.
 * 
 * @param dirLogica 
 * @param registros 
 */
void cargarLAR(int dirLogica, int registros[]){
    registros[LAR_INDEX] = dirLogica;
}


void verificarIndiceSegmento(int indiceSegmento, int tablaSegmentos[]) {
    if (!(indiceSegmento >= 0 && indiceSegmento < TAM_TABLA_SEGMENTOS && tablaSegmentos[indiceSegmento] > -1))
        terminarPrograma("se intentó acceder a un bloque de memoria inexistente");
}

int conseguirDirFisica(int dirLogica, int cantBytes, int tablaSegmentos[]) {
    int offset = dirLogica & 0x0000FFFF;
    int segmentIndex = dirLogica >> 16;

    verificarIndiceSegmento(segmentIndex, tablaSegmentos);

    int dirBase = tablaSegmentos[segmentIndex] >> 16 & 0x0000FFFF; //aplicamos mascara por si empieza con bit 1 la direccion fisica del inicio del segmento
    int tamanioSegmento = tablaSegmentos[segmentIndex] & 0x0000FFFF;

    int dirFisica = dirBase + offset;
    if( (dirBase <= dirFisica) && ( (dirBase + tamanioSegmento) >= (dirFisica + cantBytes) ) )
        return dirFisica;
    else
        terminarPrograma("segmentation fault");
}


void cargarMAR(int cantBytes, int registros[], int tablaSegmentos[]){
    int dirLogica = registros[LAR_INDEX];
 
    registros[MAR_INDEX] = (cantBytes << 16) | ((conseguirDirFisica(dirLogica, cantBytes, tablaSegmentos)) & (0x0000FFFF)); 
}

int leerMemoria(int cantBytes, int dirFisica, char memoria[]) {
    int valor = 0;
    int n = dirFisica + cantBytes;
    for(int i = dirFisica; i < n; i++){
        valor = (valor << 8) | (memoria[i] & 0x000000FF);  // no mantiene signo de valor leido
        //printf("valor %X i: %d\n", valor, i);
    }
    //printf("valor: %x\n", valor);
    valor = valor << (32 - 8*cantBytes);  //restora signo
    valor = valor >> (32 - 8*cantBytes);
    return valor;
}


void cargarMBR(int registros[], int valor){
    registros[MBR_INDEX] = valor;
}


void escribirMemoria(int cantBytes, int direccion, int valor, char memoria[]){
    for(int i = 1; i <= cantBytes; i++)
        memoria[direccion + cantBytes - i] = (valor << (32-i*8)) >> 24; //shiftea el byte que quiero escribir hasta el byte mas significativo y luego lo shiftea hasta el byte menos significativo
        //creo que el char trunca y toma el byte menos significativo del int, asi que tambien podria ser:
        //memoria[direccion + cantBytes - i] = valor >> (i*8-8);
}


void store(char memoria[], int registros[], int tablaSegmentos[], int dirLogica, int cantBytes, int valor){
    cargarLAR(dirLogica, registros);
    cargarMAR(cantBytes, registros, tablaSegmentos);
    cargarMBR(registros, valor);
    escribirMemoria(registros[MAR_INDEX] >> 16, registros[MAR_INDEX] & 0x0000FFFF, registros[MBR_INDEX], memoria);
}


void verificarIndiceRegistro(int indexReg) {
    if (!(indexReg>=0 && indexReg<=6 || indexReg>=10 && indexReg<=17 || indexReg==26 || indexReg==27))
        terminarPrograma("intento de acceso a un registro inexistente");
}


void escribirMemoriaRegistro(char memoria[], int registros[], int tablaSegmentos[], int operando, int valor) { 
    int tipo = tipoOperando(operando);
    int valor_logico = (operando << 8) >> 8;

    //printf("ESCRIBIR MEMORIA, operando:%X\n", operando);
    //printf("tipo: %X valor_logico:%X\n", tipo, valor_logico);
    if (tipo == 1) {
        verificarIndiceRegistro(valor_logico);
        registros[valor_logico] = valor; 
    }
    else if(tipo == 3){
        int reg = (valor_logico >> 16) & 0x1F;
        verificarIndiceRegistro(reg);
        int offset = (valor_logico << 16) >> 16;
        int dirLog = registros[reg] + offset;
        store(memoria, registros, tablaSegmentos, dirLog, 4, valor);
    }
    else
        terminarPrograma("Solo es posible escribir en un registro o direccion de memoria");
}


int OperandotoInmediato(int operando, char memoria[], int registros[], int tablaSegmentos[]){
    int tipo = tipoOperando(operando);
    int valor = (operando << 8) >> 8;
    ////printf("tipo: %X valor:%X\n", tipo, valor);
    if (tipo == 2)
        return valor;
    else if (tipo == 1) {
        verificarIndiceRegistro(valor);
        return registros[valor];
    }
    else if (tipo == 3){
        int registro = (valor >> 16) & 0x1F;
        verificarIndiceRegistro(registro);
        int offset = (valor << 16) >> 16;
       // printf("registro: %X offset:%X\n", registro, offset);
        int dirLogica = registros[registro]+ offset;
        //printf("dir logica: %x\n", dirLogica);
        fetch(memoria, registros, tablaSegmentos, dirLogica, 4);
        //printf("operandoToinmediato mbr: %x\n", registros[MBR_INDEX]);
        return registros[MBR_INDEX];
    }
    else
        terminarPrograma("Un operando de tipo ninguno no puede convertirse a un inmediato");

}


void fetch(char memoria[], int registros[], int tablaSegmentos[], int dirLogica, int cantBytes){
    cargarLAR(dirLogica, registros);
    cargarMAR(cantBytes, registros, tablaSegmentos);
    cargarMBR(registros, leerMemoria(registros[MAR_INDEX] >> 16, registros[MAR_INDEX] & 0x0000FFFF, memoria));
} 