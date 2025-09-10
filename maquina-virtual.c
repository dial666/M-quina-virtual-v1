#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_MEMORIA 16384
#define TAM_REGISTROS 32 
#define TAM_TABLA_SEGMENTOS 2
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

#define EAX_INDEX 10
#define EBX_INDEX 11
#define ECX_INDEX 12
#define EDX_INDEX 13
#define EEX_INDEX 14
#define EFX_INDEX 15

#define AC_INDEX 16
#define CC_INDEX 17

typedef void (*ArrayOperaciones[32])(char[], int[], int[]);

void terminarPrograma(char mensaje[]);
int verificarNumOperacion(char primer_byte);
void mostrarArreglo(char arr[], int n);
void verificarIndiceSegmento(int indiceSegmento, int tablaSegmentos[]);
int mascara0primerosBits(int cantBits);
int tipoOperando(int operando);

void leerArchivoEntrada(char nombreArchivo[], char memoria[], int tablaSegmentos[], int registros[]);
void convertirArregloAInt(char arregloBytes[], int n, int *num);
void inicializarTablaSegmentos(int tamanoCodigo, int tablaSegmentos[]);
void inicializarPunterosInicioSegmentos(int tablaSegmentos[], int registros[]);
void fetch(char memoria[], int registros[], int tablaSegmentos[], int dirLogica, int cantBytes);
void ejecutarPrograma(char memoria[], int registros[], int tablaSegmentos[], ArrayOperaciones operaciones);

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

    ArrayOperaciones operaciones;//array de funciones

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

    leerArchivoEntrada(argv[1], memoria, tablasegmentos, registros);
    //ejecutarPrograma(memoria, registros, tablasegmentos);
    ejecutarPrograma(memoria, registros, tablasegmentos, operaciones);

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
    int aux = 0,
        i;

    //para validar los accesos a la tabla de segmentos, es necesario inic. los valores de las 8 entradas
    for (i = 0; i< TAM_TABLA_SEGMENTOS; i++)
        tablaSegmentos[i] = -1;

    aux = aux | tamanoCodigo;
    tablaSegmentos[0] = aux;
    aux = aux << 16;
    aux = aux | (TAM_MEMORIA - tamanoCodigo);
    tablaSegmentos[1] = aux;

}

void inicializarPunterosInicioSegmentos(int tablaSegmentos[], int registros[]) {
    //inicialiar CS
    registros[CS_INDEX] = 0;
    //inicializar DS
    registros[DS_INDEX] = 0;
    registros[DS_INDEX] = registros[DS_INDEX] | 0x00010000;
    //inicializar IP = CS
    registros[IP_INDEX] = registros[CS_INDEX];

    //de prueba:
    //registros[7] = 0x00010000;
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

    int dirBase = tablaSegmentos[segmentIndex] >> 16; //si empieza con bit 1 habria problemas de signo
    int tamanioSegmento = tablaSegmentos[segmentIndex] & 0x0000FFFF;

    int dirFisica = dirBase + offset;

    if( (dirBase <= dirFisica) && ( (dirBase + tamanioSegmento) >= (dirFisica + cantBytes) ) )
        registros[MAR_INDEX] = (cantBytes << 16) | ((dirFisica) & (0x0000FFFF)); //CREO QUE EL ULTIMO & ESTA DE MAS PERO REVISAR
    else
        terminarPrograma("segmentation fault");

}

void leerMemoria(char memoria[], int registros[]){
    
    int cantBytes = registros[MAR_INDEX] >> 16;
    int direccion = registros[MAR_INDEX] & 0x00FF;
    int valor = 0;
    for(int i = 0; i < cantBytes; i++)
        valor = (valor << 8) | (memoria[direccion + i] & 0x000000FF);  // no mantiene signo de valor leido

    valor = valor << (32 - 8*cantBytes);  //restora signo
    valor = valor >> (32 - 8*cantBytes);
    registros[MBR_INDEX] = valor;
    
}


void fetchInstruccion(char memoria[], int registros[], int tablaSegmentos[]){
    fetch(memoria, registros, tablaSegmentos, registros[IP_INDEX], 1);
}

void fetch(char memoria[], int registros[], int tablaSegmentos[], int dirLogica, int cantBytes){
    cargarLAR(dirLogica, registros);
    cargarMAR(cantBytes, registros, tablaSegmentos);
    leerMemoria(memoria, registros);
}

void decodeInstruccion(char memoria[], int registros[], int tablaSegmentos[]){ //IP todavia apunta a inicio de instruccion
    int instruccion = registros[MBR_INDEX];
    int tipo1 = (instruccion >> 6) /*(y como es SAR:)*/ & 0b11;
    int tipo2 = (instruccion >> 4) & 0b11;

    registros[OPC_INDEX] = instruccion & 0b00011111;

    fetch(memoria, registros, tablaSegmentos, registros[IP_INDEX] + 1, tipo1); //fetch op1 (o B)
    registros[OP1_INDEX] = registros[MBR_INDEX]; //depende de que leerMemoria escriba 0 en el MBR si el tipo1 es 0 (instruccion sin operandos)
    if(tipo2 == 0){
        registros[OP2_INDEX] = 0;
    }else{
        fetch(memoria, registros, tablaSegmentos, registros[IP_INDEX] + 1 + tipo1, tipo2);
        registros[OP2_INDEX] = registros[MBR_INDEX];
    }


    registros[OP1_INDEX] &= 0x00FFFFFF;
    registros[OP2_INDEX] &= 0x00FFFFFF;

    registros[OP1_INDEX] |= (tipo1 << 24);
    registros[OP2_INDEX] |= (tipo2 << 24);

    if(tipo2!=0)
        intercambiarVar(&registros[OP1_INDEX], &registros[OP2_INDEX]);

    registros[IP_INDEX] += 1 + tipo1 + tipo2;   

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

int OperandotoInmediato(int operando, char memoria[], int registros[], int tablaSegmentos[]){
    int tipo = tipoOperando(operando);
    int valor = (operando << 8) >> 8;
    if(tipo == 2)
        return valor;
    else if (tipo == 01)
        return registros[valor]; //no contempla registro inexistente
    else if(tipo == 3){
        int registro = (valor >> 16) & 0x1F;
        int offset = (valor << 16) >> 16;
        int dirLogica = registros[registro] + offset;
        fetch(memoria, registros, tablaSegmentos, dirLogica, 4);
        return registros[MBR_INDEX];
    }
    else
        terminarPrograma("Un operando de tipo ninguno no puede convertirse a un inmediato");

}

void cargarMBR(int registros[], int valor){
    registros[MBR_INDEX] = valor;
}

void escribirMemoria(char memoria[], int registros[], int tablaSegmentos[]){
    int cantBytes = registros[MAR_INDEX] >> 16;
    int direccion = registros[MAR_INDEX] & 0x0000FFFF;

    int valor = registros[MBR_INDEX];

    for(int i = 1; i <= cantBytes; i++)
        memoria[direccion + cantBytes - i] = (valor << (32-i*8)) >> 24; //shiftea el byte que quiero escribir hasta el byte mas significativo y luego lo shiftea hasta el byte menos significativo
        //creo que el char trunca y toma el byte menos significativo del int, asi que tambien podria ser:
        //memoria[direccion + cantBytes - i] = valor >> (i*8-8);

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

void actualizarCC(int registros[], int valor){ //primer bit N, segundo Z
    registros[CC_INDEX] &= 0x3FFFFFFF; //setea en 0 primeros dos bits pero deja el resto con el valor que tuvieran
    if(valor == 0)
        registros[CC_INDEX] |= 0x40000000; //01xxx...
    else if (valor < 0)
        registros[CC_INDEX] |= 0x80000000; //10xxx...
    else
        registros[CC_INDEX] |= 0x00000000; //innecesario pero agrega claridad
}

void actualizarAC(int registros[], int valor){
    registros[AC_INDEX] = valor;
}

void mv_mov(char memoria[], int registros[], int tablaSegmentos[]){
    int B = OperandotoInmediato(registros[OP2_INDEX], memoria, registros, tablaSegmentos);
    escribirMemoriaRegistro(memoria, registros, tablaSegmentos, registros[OP1_INDEX], B);
}
void mv_add(char memoria[], int registros[], int tablaSegmentos[]){
    int A = OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos);
    int B = OperandotoInmediato(registros[OP2_INDEX], memoria, registros, tablaSegmentos);
    //printf("A:%d, B:%d, A+B:%d\n", A, B, A+B);
    escribirMemoriaRegistro(memoria, registros, tablaSegmentos, registros[OP1_INDEX], A+B);
    actualizarCC(registros, A+B);

    //pruebas 
    /* printf("A:%d, B:%d, A+B:%d\n", A, B, A+B);
    printf("Operando: 0x%X, valor:%d\n", registros[OP1_INDEX], OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos)); */
}
void mv_sub(char memoria[], int registros[], int tablaSegmentos[]){
    int A = OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos);
    int B = OperandotoInmediato(registros[OP2_INDEX], memoria, registros, tablaSegmentos);
    escribirMemoriaRegistro(memoria, registros, tablaSegmentos, registros[OP1_INDEX], A-B);
    actualizarCC(registros, A-B);

    /* //pruebas:
    printf("A:%d, B:%d, A-B:%d\n", A, B, A-B);
    printf("Operando: 0x%X, valor:%d\n", registros[OP1_INDEX], OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos)); */    
}
void mv_mul(char memoria[], int registros[], int tablaSegmentos[]){
    int A = OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos);
    int B = OperandotoInmediato(registros[OP2_INDEX], memoria, registros, tablaSegmentos);
    escribirMemoriaRegistro(memoria, registros, tablaSegmentos, registros[OP1_INDEX], A*B);
    actualizarCC(registros, A*B);

    /* //pruebas:
    printf("A:%d, B:%d, A*B:%d\n", A, B, A*B);
    printf("Operando: 0x%X, valor:%d\n", registros[OP1_INDEX], OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos));
    
    printf("CC: 0x%08X, AC:0x%08X\n", registros[CC_INDEX], registros[AC_INDEX]); */
}
void mv_div(char memoria[], int registros[], int tablaSegmentos[]){
    int A = OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos);
    int B = OperandotoInmediato(registros[OP2_INDEX], memoria, registros, tablaSegmentos);

    if(B == 0)
        terminarPrograma("error: division por cero");

    escribirMemoriaRegistro(memoria, registros, tablaSegmentos, registros[OP1_INDEX], A/B);
    actualizarCC(registros, A/B);
    actualizarAC(registros, A%B);

    /* //pruebas:
    printf("A:%d, B:%d, A/B:%d\n", A, B, A/B);
    printf("Operando: 0x%X, valor:%d\n", registros[OP1_INDEX], OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos));

    printf("CC: 0x%08X, AC:%d\n", registros[CC_INDEX], registros[AC_INDEX]); */
}
void mv_cmp(char memoria[], int registros[], int tablaSegmentos[]){
    int A = OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos);
    int B = OperandotoInmediato(registros[OP2_INDEX], memoria, registros, tablaSegmentos);
    actualizarCC(registros, A-B);

  /*   printf("A:%d, B:%d, A-B:%d\n", A, B, A-B);
    printf("Operando: 0x%X, valor:%d\n", registros[OP1_INDEX], OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos));

    printf("CC: 0x%08X, AC:%d\n", registros[CC_INDEX], registros[AC_INDEX]);  */
}
void mv_shl(char memoria[], int registros[], int tablaSegmentos[]){
    int A = OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos);
    int B = OperandotoInmediato(registros[OP2_INDEX], memoria, registros, tablaSegmentos);
    
    escribirMemoriaRegistro(memoria, registros, tablaSegmentos, registros[OP1_INDEX], A<<B);
    actualizarCC(registros, A<<B);

    /* printf("A:0x%08X, B:%d, A<<B:0x%08X\n", A, B, A<<B);
    printf("Operando: 0x%X, valor:0x%08X\n", registros[OP1_INDEX], OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos));

    printf("CC: 0x%08X, AC:%d\n", registros[CC_INDEX], registros[AC_INDEX]); */

}

void mv_shr(char memoria[], int registros[], int tablaSegmentos[]){
    int A = OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos);
    int B = OperandotoInmediato(registros[OP2_INDEX], memoria, registros, tablaSegmentos);

    int resultado = (A>>B) & mascara0primerosBits(B);

    
    escribirMemoriaRegistro(memoria, registros, tablaSegmentos, registros[OP1_INDEX], resultado);
    actualizarCC(registros, resultado);

    /*printf("A:0x%08X, B:%d, A>>B:0x%08X\n", A, B, resultado);
    printf("Operando: 0x%X, valor:0x%08X\n", registros[OP1_INDEX], OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos));

    printf("CC: 0x%08X, AC:%d\n", registros[CC_INDEX], registros[AC_INDEX]);*/
    
}
void mv_sar(char memoria[], int registros[], int tablaSegmentos[]){
    int A = OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos);
    int B = OperandotoInmediato(registros[OP2_INDEX], memoria, registros, tablaSegmentos);
    
    escribirMemoriaRegistro(memoria, registros, tablaSegmentos, registros[OP1_INDEX], A>>B);
    actualizarCC(registros, A>>B);

    /* printf("A:0x%08X, B:%d, A>>B:0x%08X\n", A, B, A>>B);
    printf("Operando: 0x%X, valor:0x%08X\n", registros[OP1_INDEX], OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos));

    printf("CC: 0x%08X, AC:%d\n", registros[CC_INDEX], registros[AC_INDEX]); */ 
    
}
void mv_and(char memoria[], int registros[], int tablaSegmentos[]){
    int A = OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos);
    int B = OperandotoInmediato(registros[OP2_INDEX], memoria, registros, tablaSegmentos);
    
    escribirMemoriaRegistro(memoria, registros, tablaSegmentos, registros[OP1_INDEX], A&B);
    actualizarCC(registros, A&B);
}
void mv_or(char memoria[], int registros[], int tablaSegmentos[]){
    int A = OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos);
    int B = OperandotoInmediato(registros[OP2_INDEX], memoria, registros, tablaSegmentos);
    
    escribirMemoriaRegistro(memoria, registros, tablaSegmentos, registros[OP1_INDEX], A|B);
    actualizarCC(registros, A|B);
}
void mv_xor(char memoria[], int registros[], int tablaSegmentos[]){
    int A = OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos);
    int B = OperandotoInmediato(registros[OP2_INDEX], memoria, registros, tablaSegmentos);
    
    escribirMemoriaRegistro(memoria, registros, tablaSegmentos, registros[OP1_INDEX], A^B);
    actualizarCC(registros, A^B);
}

void mv_swap(char memoria[], int registros[], int tablaSegmentos[]){

    int operando1 = registros[OP1_INDEX]; //los guardo primero por si las variables se apuntan entre si
    int operando2 = registros[OP2_INDEX];

    int tipo1 = tipoOperando(operando1);
    int tipo2 = tipoOperando(operando2);

    if((tipo1 == 2) || (tipo2 == 2))
        terminarPrograma("error: inmediato como operando de operacion swap");
    else{

        int A = OperandotoInmediato(operando1, memoria, registros, tablaSegmentos);
        int B = OperandotoInmediato(operando2, memoria, registros, tablaSegmentos);
        
        escribirMemoriaRegistro(memoria, registros, tablaSegmentos, operando1, B);
        escribirMemoriaRegistro(memoria, registros, tablaSegmentos, operando2, A);
    }
}
void mv_ldh(char memoria[], int registros[], int tablaSegmentos[]){//precondicion: A tiene un tamaño de 32 bits
    int A = OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos);
    int B = OperandotoInmediato(registros[OP2_INDEX], memoria, registros, tablaSegmentos);

    B &= 0xFFFF; //me quedo solo con los 2 bytes menos significativos
    B = B<<16;
    A &= 0xFFFF; //seteo primeros 2 bytes en 0 y me quedo con los 2 bytes menos significativos
    A = A|B;
    
    escribirMemoriaRegistro(memoria, registros, tablaSegmentos, registros[OP1_INDEX], A);
}
void mv_ldl(char memoria[], int registros[], int tablaSegmentos[]){
    int A = OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos);
    int B = OperandotoInmediato(registros[OP2_INDEX], memoria, registros, tablaSegmentos);

    B &= 0xFFFF; //me quedo solo con los 2 bytes menos significativos
    A &= 0xFFFF0000; //seteo ultimos 2 bytes en 0 y me quedo con los 2 bytes mas significativos
    A = A|B;
    
    escribirMemoriaRegistro(memoria, registros, tablaSegmentos, registros[OP1_INDEX], A);
}
void mv_rnd(char memoria[], int registros[], int tablaSegmentos[]){//genera solo enteros
    srand(time(NULL)); //setea la seed de random con el tiempo para emular aleatoriedad
    int B = OperandotoInmediato(registros[OP2_INDEX], memoria, registros, tablaSegmentos);

    int aleatorio = (rand() % (B - 0 + 1)) + 0; //el formato es rd_num= (rd_num % (max - min + 1)) + min
    
    escribirMemoriaRegistro(memoria, registros, tablaSegmentos, registros[OP1_INDEX], aleatorio);

    /* printf("B:%d, A RAND B:0x%08X\n", B, aleatorio);
    printf("Operando: 0x%X, valor:%d\n", registros[OP1_INDEX], OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos));

    printf("CC: 0x%08X, AC:%d\n", registros[CC_INDEX], registros[AC_INDEX]);  */
}

void jump(char memoria[], int registros[], int tablaSegmentos[], int operando){
    int nuevoIP = OperandotoInmediato(operando, memoria, registros, tablaSegmentos);

    if(nuevoIP > 0xFFFF) // offset de la instruccion desde el CS es demasiado grande e invadira el indice de la tabla de segmentos
        terminarPrograma("offset de instruccion demasiado grande");
    if(tipoOperando(operando) == 2)
        nuevoIP += registros[CS_INDEX]; //esto suma el indice del CS en la tabla de segmentos resultando en (para CS indice 0 en tabla):
                                        // 00 00 nuevoIP, e.g., para ir a instruccion 9: 00 00 00 09
    registros[IP_INDEX] = nuevoIP;

    /* printf("nuevoIP: 0x%08X\n", registros[IP_INDEX]);
    printf("Operando: 0x%X, valor:0x%08X\n", operando, OperandotoInmediato(operando, memoria, registros, tablaSegmentos));

    printf("CC: 0x%08X, AC:%d\n", registros[CC_INDEX], registros[AC_INDEX]); */
}

int jumpif(char memoria[], int registros[], int tablaSegmentos[], int operando, int n, int z){
    int cc = registros[CC_INDEX];
    int cc_n = (cc >> 31) & 0b01;
    int cc_z = (cc >> 30) & 0b01;

    /* printf("cc_n: %d cc_z: %d\n", cc_n, cc_z);
    printf("Operando: 0x%X, valor:0x%08X\n", operando, OperandotoInmediato(operando, memoria, registros, tablaSegmentos));

    printf("CC: 0x%08X, AC:%d\n", registros[CC_INDEX], registros[AC_INDEX]); */

    if((cc_n == n) && (cc_z == z))
        jump(memoria, registros, tablaSegmentos, operando);
    else
        return 0;

    
}

int minimo(int a, int b){
    if (a>b)
        return b;
    else 
        return a;
}


int cadenaToInmediato(char* cadena, int formato){ //lo convierte a valor de 32 bits 
    //PRECONDICION: el string debe significar un inmediato de igual o menos que 4 bytes
    int inmediato=0;
    int largo = minimo(strlen(cadena), 4);
    switch(formato){
        case 0x1: //decimal
            return (int) strtol(cadena, NULL, 10);
            break;
        case 0x2: //caracteres
            for (int i=0; i<largo; i++)
                inmediato = (inmediato << 8) | cadena[i];
            return inmediato;
            break;
        case 0x4: //octal
            return (int) strtol(cadena, NULL, 8);
            break;
        case 0x8: //hexadecimal
            return (int) strtol(cadena, NULL, 16);
            break;
        case 0x10: //binario
            return (int) strtol(cadena, NULL, 2);
            break;
        default:
            terminarPrograma("formato de escritura a memoria erroneo");
    }
}

char* inmediatoToString(int inmediato, int formato){//
    static char cadena[192];
    char temp[48];
    cadena[0] = '\0';

    int primero = 1;

    if (formato & 0x01) { // decimal
        snprintf(temp, sizeof(temp), "%d", inmediato);
        strcat(cadena, temp);
        primero = 0;
    }
    if (formato & 0x02) { // caracter
        snprintf(temp, sizeof(temp), "%c", (inmediato >= 32 && inmediato <= 126) ? (char)inmediato : '.');
        if (!primero) strcat(cadena, " ");
        strcat(cadena, temp);
        primero = 0;
    }
    if (formato & 0x04) { // octal
        snprintf(temp, sizeof(temp), "0o%o", inmediato);
        if (!primero) strcat(cadena, " ");
        strcat(cadena, temp);
        primero = 0;
    }
    if (formato & 0x08) { // hexadecimal
        snprintf(temp, sizeof(temp), "0x%X", inmediato);
        if (!primero) strcat(cadena, " ");
        strcat(cadena, temp);
        primero = 0;
    }
    if (formato & 0x10) { // binario
        char binario[33] = {0};
        for (int i = 31; i >= 0; i--) {
            binario[31 - i] = (inmediato & (1 << i)) ? '1' : '0';
        }
        binario[32] = '\0';
        snprintf(temp, sizeof(temp), "0b%s", binario);
        if (!primero) strcat(cadena, " ");
        strcat(cadena, temp);
    }

    return cadena;
}

void mv_sys(char memoria[], int registros[], int tablaSegmentos[]){
    int formato = registros[EAX_INDEX];
    int cantCeldas = registros[ECX_INDEX] & 0xFFFF;
    int tamanioCelda = (registros[ECX_INDEX]>>16) & 0xFFFF;
    int dirLogica = registros[EDX_INDEX];                     
    
    int modo = OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos);
    
    if(tamanioCelda < 1 || tamanioCelda > 4)  //solo puede escribir celdas de 1 a 4 bytes (MBR es de 32 bits)
        terminarPrograma("tamanio de celda invalido");
        
    char cadenaConsola[200];    //SI NO LE PONGO TAMAÑO, INVADE LA MEMORIA Y ME CAMBIA OTRAS COSAS LPMMMM
    for(int i = 0; i < cantCeldas; i++){
        if((dirLogica >> 16)!=(registros[DS_INDEX]>>16))  //controlamos que este en el DS
            terminarPrograma("segmentatio fault, no puede escribir o leer datos fuera del DS");
        cargarLAR(dirLogica, registros);
        cargarMAR(tamanioCelda, registros, tablaSegmentos);
        printf("[%X]: ", registros[MAR_INDEX]&0xFFFF);
        if(modo == 1){ //READ (escribe en memoria lo leido en consola)
            scanf("%s", cadenaConsola);
            registros[MBR_INDEX] = cadenaToInmediato(cadenaConsola, formato);
            escribirMemoria(memoria, registros, tablaSegmentos);

        }else if(modo == 2){// WRITE (escribe en consola)
            leerMemoria(memoria, registros);
            
            printf("%s\n", inmediatoToString(registros[MBR_INDEX], formato));
        }else
            terminarPrograma("operando invalido para instruccion sys");
            
        dirLogica+=tamanioCelda;
    }        
    
}
void mv_jmp(char memoria[], int registros[], int tablaSegmentos[]){
    jump(memoria, registros, tablaSegmentos, registros[OP1_INDEX]);
}
void mv_jz(char memoria[], int registros[], int tablaSegmentos[]){
    jumpif(memoria, registros, tablaSegmentos, registros[OP1_INDEX], 0, 1);
}
void mv_jp(char memoria[], int registros[], int tablaSegmentos[]){
    jumpif(memoria, registros, tablaSegmentos, registros[OP1_INDEX], 0, 0);
}
void mv_jn(char memoria[], int registros[], int tablaSegmentos[]){
    jumpif(memoria, registros, tablaSegmentos, registros[OP1_INDEX], 1, 0);
}
void mv_jnz(char memoria[], int registros[], int tablaSegmentos[]){
    jumpif(memoria, registros, tablaSegmentos, registros[OP1_INDEX], 1, 0)
    || jumpif(memoria, registros, tablaSegmentos, registros[OP1_INDEX], 0, 0);
}
void mv_jnp(char memoria[], int registros[], int tablaSegmentos[]){
    jumpif(memoria, registros, tablaSegmentos, registros[OP1_INDEX], 1, 0)
    || jumpif(memoria, registros, tablaSegmentos, registros[OP1_INDEX], 0, 1);
}
void mv_jnn(char memoria[], int registros[], int tablaSegmentos[]){
    jumpif(memoria, registros, tablaSegmentos, registros[OP1_INDEX], 0, 1)
    || jumpif(memoria, registros, tablaSegmentos, registros[OP1_INDEX], 0, 0);
}
void mv_not(char memoria[], int registros[], int tablaSegmentos[]){
    int A = OperandotoInmediato(registros[OP1_INDEX], memoria, registros, tablaSegmentos);
    
    escribirMemoriaRegistro(memoria, registros, tablaSegmentos, registros[OP1_INDEX], ~A);
    actualizarCC(registros, ~A);
}
void mv_stop(char memoria[], int registros[], int tablaSegmentos[]){
    printf("fin\n");
    registros[IP_INDEX] = -1;

}
void mv_vacio(char memoria[], int registros[], int tablaSegmentos[]){
    terminarPrograma("codigo de operacion invalido");
};

int mascara0primerosBits(int cantBits){
    return cantBits < 32 ? (1U << (32 - cantBits)) - 1 : 0;
}

int tipoOperando(int operando){
    return (operando >> 24) & (0x00000003);
}

void ejecutarPrograma(char memoria[], int registros[], int tablaSegmentos[], ArrayOperaciones operaciones) {
    //ciclo real
    while(registros[IP_INDEX] != -1){
        fetchInstruccion(memoria, registros, tablaSegmentos);
        decodeInstruccion(memoria, registros, tablaSegmentos);
        operaciones[registros[OPC_INDEX]](memoria, registros, tablaSegmentos);
    }
}