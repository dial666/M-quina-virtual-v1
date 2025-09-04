#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define TAM_MEMORIA 16384
#define TAM_REGISTROS 32 
#define TAM_TABLA_SEGMENTOS 8
#define CANT_BYTES_TAM_CODIGO 2

void terminarPrograma(char mensaje[]);
int verificarNumOperacion(char primer_byte);
void mostrarArreglo(char arr[], int n);

void leerArchivoEntrada(char nombreArchivo[], char memoria[], int tablaSegmentos[], int registros[]);
void convertirArregloAInt(char arregloBytes[], int n, int *num);
void inicializarTablaSegmentos(int tamanoCodigo, int tablaSegmentos[]);
void inicializarPunterosInicioSegmentos(int tablaSegmentos[], int registros[]);

int main(int argc, char *argv[]) {
    int registros[TAM_REGISTROS]; //32 registros de 32 bits
    char memoria[TAM_MEMORIA];  //16 KiB
    int tablasegmentos[TAM_TABLA_SEGMENTOS]; //8 entradas de 32 bits

    leerArchivoEntrada("C:/Users/valen/OneDrive/Documentos/Facultad/Arquitectura/M-quina-virtual-v1/sample.vmx", memoria, tablasegmentos, registros);
    //ejecutarPrograma(memoria, registros, tablasegmentos);

    return 0;
}

void leerArchivoEntrada(char nombreArchivo[], char memoria[], int tablaSegmentos[], int registros[]) {
    FILE *archBin;
    int tamCodigo; //variable auxiliar para leer cada dos bytes
    char lineaCodigo, tamCodigoAux[CANT_BYTES_TAM_CODIGO], aux;
    int i;


    archBin = fopen(nombreArchivo, "rb");
    if (archBin == NULL)
        terminarPrograma("no se pudo abrir el archivo");
    else {
        //leer tamaño de codigo del archivo
        fseek(archBin, 6, SEEK_SET);
        i = 0;
        while (i < CANT_BYTES_TAM_CODIGO && fread(&aux, sizeof(aux), 1, archBin) == 1) {
            tamCodigoAux[i] = aux;
            i++;
        }

        if (i != CANT_BYTES_TAM_CODIGO)
            terminarPrograma("no se pudo leer el tamano de codigo");
            
        convertirArregloAInt(tamCodigoAux, CANT_BYTES_TAM_CODIGO, &tamCodigo);

        if (tamCodigo > TAM_MEMORIA)
            terminarPrograma("el tamamo del codigo supera al de la memoria");

        i = 0;
        while (fread(&lineaCodigo, sizeof(lineaCodigo), 1, archBin) == 1) {
            memoria[i] = lineaCodigo;
            i++;
        }

        if(i != tamCodigo)
            terminarPrograma("el tamano del codigo especificado en la cabecera no coincide con el tamano real");

        inicializarTablaSegmentos(tamCodigo, tablaSegmentos);
        inicializarPunterosInicioSegmentos(tablaSegmentos, registros);
        
        fclose(archBin);
    }
}

void inicializarTablaSegmentos(int tamanoCodigo, int tablaSegmentos[]) {
    int aux = 0;
    aux = aux | tamanoCodigo;
    tablaSegmentos[0] = aux;
    aux = aux << 16;
    aux = aux | (TAM_MEMORIA - tamanoCodigo);
    tablaSegmentos[1] = aux;
}

void inicializarPunterosInicioSegmentos(int tablaSegmentos[], int registros[]) {
    //inicialiar CS
    registros[26] = 0;
    //inicializar DS
    registros[27] = 0;
    registros[27] = registros[27] | 0x00010000;
    //inicializar IP = CS
    registros[3] = registros[26];
}

int verificarNumOperacion(char primer_byte){ //parametro = primer byte de instruccion, solo analiza ultimos 5 bits
    primer_byte &= 0b00011111;
    return (primer_byte <= 0x1F) && !(primer_byte > 0x08 && primer_byte < 0x0F);
}

void ejecutarPrograma(char memoria[], int registros[], int tablaSegmentos[]) {
    //ciclo de fetch-decode-execute
}

void terminarPrograma(char mensaje[]) {
    printf("%s\n", mensaje);
    exit(EXIT_FAILURE);
}

void convertirArregloAInt(char arregloBytes[], int n, int *num) {
    int i, aux;
    int cantBytesDesplazar = n - 1;

    *num = 0;
    for(i = 0; i < n; i++) {
        aux = arregloBytes[i];
        aux = aux << (cantBytesDesplazar * 8);
        *num = *num | aux;
        cantBytesDesplazar--;
    }
}


void mostrarArreglo(char arr[], int n) {
    int i = 0;
    for (; i < n; i++)
        printf("%d\n", arr[i]);
}