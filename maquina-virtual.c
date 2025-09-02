#include <stdio.h>

#define TAM_MEMORIA 16384
#define TAM_REGISTROS 32 
#define TAM_TABLA_SEGMENTOS 8

int main(int argc, char *argv[]) {
    int registros[TAM_REGISTROS]; //32 registros de 32 bits
    char memoria[TAM_MEMORIA];  //16 KiB
    int tablasegmentos[TAM_TABLA_SEGMENTOS]; //8 entradas de 32 bits

    leerArchivoEntrada(argv[1], memoria, tablasegmentos, registros);
    ejecutarPrograma(memoria, registros, tablasegmentos);

    return 0;
}

void leerArchivoEntrada(char nombreArchivo[], char memoria[], int segmentos[], int registros[]) {
    FILE *archbin;
    char aux; //variable auxiliar para leer byte a byte

    archbin = fopen(nombreArchivo, "rb");
    if (archbin == NULL) {
        printf("no se pudo abrir el archivo %s\n", nombreArchivo);
    }
    else {
        //leer tamaño de codigo del archivo
        //cargar codigo en memoria si es que no la excede
        //inicializar tabla de segmentos
        //inicializar punteros de inicio de segmentos
        fclose(archbin);
    }
}

void inicializarTablaSegmentos(int tamanoCodigo, int tablaSegmentos[]) {
    //inicializar tabla de segmentos
}

void inicializarPunterosInicioSegmentos(int tablaSegmentos[], int registros[]) {
    //inicialiar DS, CS, IP
}

void ejecutarPrograma(char memoria[], int registros[], int tablaSegmentos[]) {
    //ciclo de fetch-decode-execute
}