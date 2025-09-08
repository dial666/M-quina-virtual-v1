#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define TAM_MEMORIA 16384
#define TAM_REGISTROS 32 
#define TAM_TABLA_SEGMENTOS 8
#define CANT_BYTES_TAM_CODIGO 2

#define CS_INDEX 26
#define DS_INDEX 27

#define CS_SEG_INDEX 0
#define DS_SEG_INDEX 1

#define LAR_INDEX 0
#define MAR_INDEX 1
#define MBR_INDEX 2
#define IP_INDEX 3
#define OPC_INDEX 4
#define OP1_INDEX 5
#define OP2_INDEX 6 

void terminarPrograma(char mensaje[]);
int verificarNumOperacion(char primer_byte);
void mostrarArreglo(char arr[], int n);

void leerArchivoEntrada(char nombreArchivo[], char memoria[], int tablaSegmentos[], int registros[]);
void convertirArregloAInt(char arregloBytes[], int n, int *num);
void inicializarTablaSegmentos(int tamanoCodigo, int tablaSegmentos[]);
void inicializarPunterosInicioSegmentos(int tablaSegmentos[], int registros[]);
void fetch(char memoria[], int registros[], int tablaSegmentos[], int dirLogica, int cantBytes);

void mv_mov(char memoria[], int registros[], int tablaSegmentos[]);
void mv_add(char memoria[], int registros[], int tablaSegmentos[]);
void mv_sub(char memoria[], int registros[], int tablaSegmentos[]);
void mv_mul(char memoria[], int registros[], int tablaSegmentos[]);
void mv_div(char memoria[], int registros[], int tablaSegmentos[]);
void mv_cmp(char memoria[], int registros[], int tablaSegmentos[]);
void mv_shl(char memoria[], int registros[], int tablaSegmentos[]);
void mv_shr(char memoria[], int registros[], int tablaSegmentos[]);
void mv_sar(char memoria[], int registros[], int tablaSegmentos[]);
void mv_and(char memoria[], int registros[], int tablaSegmentos[]);
void mv_or(char memoria[], int registros[], int tablaSegmentos[]);
void mv_xor(char memoria[], int registros[], int tablaSegmentos[]);
void mv_swap(char memoria[], int registros[], int tablaSegmentos[]);
void mv_ldl(char memoria[], int registros[], int tablaSegmentos[]);
void mv_ldh(char memoria[], int registros[], int tablaSegmentos[]);
void mv_rnd(char memoria[], int registros[], int tablaSegmentos[]);
void mv_sys(char memoria[], int registros[], int tablaSegmentos[]);
void mv_jmp(char memoria[], int registros[], int tablaSegmentos[]);
void mv_jz(char memoria[], int registros[], int tablaSegmentos[]);
void mv_jp(char memoria[], int registros[], int tablaSegmentos[]);
void mv_jn(char memoria[], int registros[], int tablaSegmentos[]);
void mv_jnz(char memoria[], int registros[], int tablaSegmentos[]);
void mv_jnp(char memoria[], int registros[], int tablaSegmentos[]);
void mv_jnn(char memoria[], int registros[], int tablaSegmentos[]);
void mv_not(char memoria[], int registros[], int tablaSegmentos[]);
void mv_stop(char memoria[], int registros[], int tablaSegmentos[]);
void mv_vacio(char memoria[], int registros[], int tablaSegmentos[]);

int main(int argc, char *argv[]) {
    int registros[TAM_REGISTROS]; //32 registros de 32 bits
    char memoria[TAM_MEMORIA];  //16 KiB
    int tablasegmentos[TAM_TABLA_SEGMENTOS]; //8 entradas de 32 bits

    void (*operaciones[32])(char[], int[], int[]); //array de funciones

    operaciones[0x00] = &mv_sys;
    operaciones[0x01] = &mv_jmp;
    operaciones[0x02] = &mv_jz;
    operaciones[0x03] = &mv_jp;
    operaciones[0x04] = &mv_jn;
    operaciones[0x05] = &mv_jnz;
    operaciones[0x06] = &mv_jnp;
    operaciones[0x07] = &mv_jnn;
    operaciones[0x08] = &mv_not;
    operaciones[0x09] = &mv_vacio;
    operaciones[0x0A] = &mv_vacio;
    operaciones[0x0B] = &mv_vacio;
    operaciones[0x0C] = &mv_vacio;
    operaciones[0x0D] = &mv_vacio;
    operaciones[0x0E] = &mv_vacio;
    operaciones[0x0F] = &mv_stop;
    operaciones[0x10] = &mv_mov;
    operaciones[0x11] = &mv_add;
    operaciones[0x12] = &mv_sub;
    operaciones[0x13] = &mv_mul;
    operaciones[0x14] = &mv_div;
    operaciones[0x15] = &mv_cmp;
    operaciones[0x16] = &mv_shl;
    operaciones[0x17] = &mv_shr;
    operaciones[0x18] = &mv_sar;
    operaciones[0x19] = &mv_and;
    operaciones[0x1A] = &mv_or;
    operaciones[0x1B] = &mv_xor;
    operaciones[0x1C] = &mv_swap;
    operaciones[0x1D] = &mv_ldl;
    operaciones[0x1E] = &mv_ldh;
    operaciones[0x1F] = &mv_rnd;

    leerArchivoEntrada("C:/Users/Matu/Desktop/Facultad/2025/Arqui/MV/Repo/M-quina-virtual-v1/sample.vmx", memoria, tablasegmentos, registros);
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
    tablaSegmentos[CS_SEG_INDEX] = aux;
    aux = aux << 16;
    aux = aux | (TAM_MEMORIA - tamanoCodigo);
    tablaSegmentos[DS_SEG_INDEX] = aux;
}

void inicializarPunterosInicioSegmentos(int tablaSegmentos[], int registros[]) {
    //inicialiar CS
    registros[CS_INDEX] = 0;
    //inicializar DS
    registros[DS_INDEX] = 0;
    registros[DS_INDEX] = registros[DS_INDEX] | 0x00010000;
    //inicializar IP = CS
    registros[IP_INDEX] = registros[CS_INDEX];
}

void intercambiarVar(int * a, int * b){
    *a = (*a) ^ (*b);
    *b = (*a) ^ (*b);
    *a = (*a) ^ (*b);
}

int verificarNumOperacion(char primer_byte){ //parametro = primer byte de instruccion, solo analiza ultimos 5 bits
    primer_byte &= 0b00011111;
    return (primer_byte <= 0x1F) && !(primer_byte > 0x08 && primer_byte < 0x0F);
}

void cargarLAR(int dirLogica, int registros[]){
    registros[LAR_INDEX] = dirLogica;
}

void cargarMAR(int cantBytes, int registros[], int tablaSegmentos[]){
    registros[MAR_INDEX] = cantBytes << 16;
    int dirLogica = registros[LAR_INDEX];
    int offset = dirLogica & 0x00001111;
    int segmentIndex = dirLogica >> 16;

    int dirBase = tablaSegmentos[segmentIndex] >> 16;
    int tamanioSegmento = tablaSegmentos[segmentIndex] & 0x00001111;

    int dirFisica = dirBase + offset;

    if( (dirBase <= dirFisica) && ( (dirBase + tamanioSegmento) >= (dirFisica + cantBytes) ) )
        registros[MAR_INDEX] = (cantBytes << 16) & dirFisica;
    else
        terminarPrograma("segmentation fault");

}

void leerMemoria(char memoria[], int registros[]){
    int cantBytes = registros[MAR_INDEX] >> 16;
    int direccion = registros[MAR_INDEX] & 0x0011;

    registros[MBR_INDEX] = 0;
    for(int i = 0; i < cantBytes; i++)
        registros[MBR_INDEX] = (registros[MBR_INDEX] << 8) & memoria[direccion + i];
}


void fetchInstruccion(char memoria[], int registros[], int tablaSegmentos[]){
    /*cargarLAR(registros[IP_INDEX], registros);
    cargarMAR(1, registros, tablaSegmentos);
    leerMemoria(memoria, registros, tablaSegmentos);*/
    fetch(memoria, registros, tablaSegmentos, registros[IP_INDEX], 1);
}

/*leerOpA(char memoria[], int registros[], int tablaSegmentos[], int tipo){ 
    
    registros[OP1_INDEX] =

}*/
void fetch(char memoria[], int registros[], int tablaSegmentos[], int dirLogica, int cantBytes){
    cargarLAR(dirLogica, registros);
    cargarMAR(cantBytes, registros, tablaSegmentos);
    leerMemoria(memoria, registros);
}

void decodeInstruccion(char memoria[], int registros[], int tablaSegmentos[]){ //IP todavia apunta a inicio de instruccion
    int instruccion = registros[IP_INDEX];
    int tipo1 = (instruccion >> 6) /*(y como es SAR:)*/ & 0b11;
    int tipo2 = (instruccion >> 4) & 0b11;

    registros[OPC_INDEX] = instruccion & 0b00011111;

    fetch(memoria, registros, tablaSegmentos, registros[IP_INDEX] + 1, tipo1);
    registros[OP1_INDEX] = registros[MBR_INDEX];
    if(tipo2 == 0){
        registros[OP1_INDEX] = registros[MBR_INDEX];
        registros[OP2_INDEX] = 0;
    }else{
        registros[OP2_INDEX] = registros[MBR_INDEX];
        fetch(memoria, registros, tablaSegmentos, registros[IP_INDEX] + 1 + tipo1, tipo1);
        registros[OP1_INDEX] = registros[MBR_INDEX];
    }

    registros[OP1_INDEX] = registros[OP1_INDEX] & 0x00111111;
    registros[OP2_INDEX] = registros[OP2_INDEX] & 0x00111111;

    registros[IP_INDEX] += 1 + tipo1 + tipo2;    
    //leerOpA(memoria, registros, tablaSegmentos, instruccion >> 6);


}

void ejecutarPrograma(char memoria[], int registros[], int tablaSegmentos[]) {
    //ciclo de fetch-decode-execute
    fetchInstruccion(memoria, registros, tablaSegmentos);
    decodeInstruccion(memoria, registros, tablaSegmentos);
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



void mv_mov(char memoria[], int registros[], int tablaSegmentos[]){
        
}
void mv_add(char memoria[], int registros[], int tablaSegmentos[]){

}
void mv_sub(char memoria[], int registros[], int tablaSegmentos[]){

}
void mv_mul(char memoria[], int registros[], int tablaSegmentos[]){

}
void mv_div(char memoria[], int registros[], int tablaSegmentos[]){

}
void mv_cmp(char memoria[], int registros[], int tablaSegmentos[]){

}
void mv_shl(char memoria[], int registros[], int tablaSegmentos[]){

}
void mv_shr(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_sar(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_and(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_or(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_xor(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_swap(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_ldl(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_ldh(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_rnd(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_sys(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_jmp(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_jz(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_jp(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_jn(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_jnz(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_jnp(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_jnn(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_not(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_stop(char memoria[], int registros[], int tablaSegmentos[]){
    
}
void mv_vacio(char memoria[], int registros[], int tablaSegmentos[]){
    
};