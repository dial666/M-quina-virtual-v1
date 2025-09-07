#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define TAM_MEMORIA 16384
#define TAM_REGISTROS 32 
#define TAM_TABLA_SEGMENTOS 8
#define CANT_BYTES_TAM_CODIGO 2
#define MAX_CANT_BYTES_LEC_ESC 4
#define CANT_BYTES_LEC_ESC 4

typedef struct {
    char nombre[3];
    int valor;
} registro;

void terminarPrograma(char mensaje[]);
int verificarNumOperacion(char primer_byte);
void mostrarArreglo(char arr[], int n);
void inicializarRegistros(registro registros[]);

void leerArchivoEntrada(char nombreArchivo[], char memoria[], int tablaSegmentos[], registro registros[]);
int convertirArregloAInt(char arregloBytes[], int n);
void convertirIntAArreglo(char arregloBytes[], int n, int valor);
void inicializarTablaSegmentos(int tamanoCodigo, int tablaSegmentos[]);
void inicializarPunterosInicioSegmentos(int tablaSegmentos[], registro registros[]);


void ejecutarPrograma(char memoria[], registro registros[], int tablaSegmentos[]);
int conseguirIndiceReg(char nombReg[], registro registros[]);
void conseguirIntervaloSegmento(int punteroASegmento, int tablaSegmentos[], int *direccionBase, int *limSegmento);
int IPEstaEnSegmentoCodigo(int IP, int direccionBase, int limSegmento);
void decodificarInstruccion(int instruccion, registro registros[]);
void leerOperandosIncrementarIP(char memoria[], registro registros[], int direccionBase, int limiteSegmento);

int registroEsValido(int nroRegistro);
void prepararLAR(int operandoMemoria, registro registros[]);
int cantBytesEsValida(int cantBytes);
void prepararMAR(registro registros[], int tablaSegmentos[], int cantBytes);
int indiceSegmentoEsValido(int indiceSegmento, int tablaSegmentos[]);
int conseguirValidarDirFisica(int dirLogica, int tablaSegmentos[], int cantBytes);
void leerMemoria(registro registros[], char memoria[]);
int conseguirValorEnMemoria(int operandoMemoria, char memoria[], int tablaSegmentos[], registro registros[]) ;
void escribirMemoria(registro registros[], char memoria[]);
void ponerValorEnMemoria(int operandoMemoria, char memoria[], int tablaSegmentos[], registro registros[], int valor);

int main(int argc, char *argv[]) {

    registro registros[TAM_REGISTROS]; //32 registros de 32 bits
    char memoria[TAM_MEMORIA];  //16 KiB
    int tablasegmentos[TAM_TABLA_SEGMENTOS]; //8 entradas de 32 bits

    inicializarRegistros(registros);
    leerArchivoEntrada("C:/Users/valen/OneDrive/Documentos/Facultad/Arquitectura/M-quina-virtual-v1/sample.vmx", memoria, tablasegmentos, registros);
    ejecutarPrograma(memoria, registros, tablasegmentos);

    return 0;
}

//FUNCIONES QUE COMPARTEN EL BLOQUE DE INICIALIZACIÓN Y EL DE EJECUCIÓN DE INSTRUCCIONES--------------------------

void terminarPrograma(char mensaje[]) {
    printf("%s\n", mensaje);
    exit(EXIT_FAILURE);
}

//consigue el índice de un registro dado su nombre
int conseguirIndiceReg(char nombReg[], registro registros[]) {
    int i = 0;
    while (strcmp(nombReg, registros[i].nombre) != 0)
        i++;
    return i;
}

int convertirArregloAInt(char arregloBytes[], int n) {
    int i, 
        num, aux,
        cantBytesDesplazar = n - 1;

    num = 0;
    for(i = 0; i < n; i++) {
        aux = (unsigned char) arregloBytes[i];
        aux = aux << (cantBytesDesplazar * 8);
        num = num | aux;
        cantBytesDesplazar--;
    }
    return num;
}

//esta función no la utiliza el bloque de inicialización pero tiene que ver con la de arriba
void convertirIntAArreglo(char arregloBytes[], int n, int valor) {
    int i = n - 1;
    unsigned int aux = valor;

    for (; i >= 0; i--) {
        arregloBytes[i] = aux & 0x000000FF;
        aux = aux >> 8;
    }
}

//FUNCIONES PARA DEBUGGEAR------------------------------------------------------------------

void mostrarArreglo(char arr[], int n) {
    int i = 0;
    for (; i < n; i++)
        printf("%x\n", arr[i]);
}

//FUNCIONES QUE INCIALIZAN ESTRUCTURAS PROPIAS DE ESTE PROGRAMA Y NO DEL CPU----------------

//horripilante pero me daba paja hacer una función que lea de archivo
void inicializarRegistros(registro registros[]) {
    strcpy(registros[0].nombre, "LAR");
    strcpy(registros[1].nombre, "MAR");
    strcpy(registros[2].nombre, "MBR");
    strcpy(registros[3].nombre, "IP");
    strcpy(registros[4].nombre, "OPC");
    strcpy(registros[5].nombre, "OP1");
    strcpy(registros[6].nombre, "OP2");
    strcpy(registros[10].nombre, "EAX");
    strcpy(registros[11].nombre, "EBX");
    strcpy(registros[12].nombre, "ECX");
    strcpy(registros[13].nombre, "EDX");
    strcpy(registros[14].nombre, "EEX");
    strcpy(registros[15].nombre, "EFX");
    strcpy(registros[16].nombre, "AC");
    strcpy(registros[17].nombre, "CC");
    strcpy(registros[26].nombre, "CS");
    strcpy(registros[27].nombre, "DS");
}

//FUNCIONES USADAS EN LA INICIALIZACIÓN DE LAS ESTRUCTURAS----------------------------------

void leerArchivoEntrada(char nombreArchivo[], char memoria[], int tablaSegmentos[], registro registros[]) {
    FILE *archBin;
    int tamCodigo; //variable auxiliar para leer cada dos bytes
    char lineaCodigo, 
        tamCodigoAux[CANT_BYTES_TAM_CODIGO], 
        aux;
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
            
        tamCodigo = convertirArregloAInt(tamCodigoAux, CANT_BYTES_TAM_CODIGO);

        if (tamCodigo > TAM_MEMORIA)
            terminarPrograma("el tamamo del codigo supera al de la memoria");

        i = 0;
        while (i <= tamCodigo && fread(&lineaCodigo, sizeof(lineaCodigo), 1, archBin) == 1) {
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

void inicializarPunterosInicioSegmentos(int tablaSegmentos[], registro registros[]) {
    int indiceCS = conseguirIndiceReg("CS", registros), 
        indiceDS = conseguirIndiceReg("DS", registros),
        indiceIP = conseguirIndiceReg("IP", registros);
    //inicialiar CS
    registros[indiceCS].valor = 0;
    //inicializar DS
    registros[indiceDS].valor = 0;
    registros[indiceDS].valor = registros[indiceDS].valor | 0x00010000;
    //inicializar IP = CS
    registros[indiceIP].valor = registros[indiceCS].valor;
}

//FUNCIONES EXCLUSIVAS DE LA EJECUCIÓN DE LAS INSTRUCCIONES-----------------------------------

void ejecutarPrograma(char memoria[], registro registros[], int tablaSegmentos[]) {
    int direccionBase, 
        limiteSegmento, 
        i = 0,
        indiceCS = conseguirIndiceReg("CS", registros),
        indiceIP = conseguirIndiceReg("IP", registros);

    conseguirIntervaloSegmento(registros[indiceCS].valor, tablaSegmentos, &direccionBase, &limiteSegmento);
    while (IPEstaEnSegmentoCodigo(registros[indiceIP].valor, direccionBase, limiteSegmento)) {
        // decodificarInstruccion(memoria[registros[indiceIP].valor], registros);
        // leerOperandosIncrementarIP(memoria, registros, direccionBase, limiteSegmento);
        ponerValorEnMemoria(0x031B000A, memoria, tablaSegmentos, registros, 90876);
        //printf("memoria: %d\n", memoria[45]);
        printf("memoria: %d\n", conseguirValorEnMemoria(0x031B000A, memoria, tablaSegmentos, registros));
        registros[indiceIP].valor = -1;
    }
}

//consigue la dirección base y el límite superior de un dado segmento
void conseguirIntervaloSegmento(int punteroASegmento, int tablaSegmentos[], int *direccionBase, int *limSegmento) {
    //consigo el indice del segmento
    punteroASegmento = punteroASegmento >> 16;
    //verifico que ese indice esté dentro de los limites de la tabla y que tenga un valor valido
    if (indiceSegmentoEsValido(punteroASegmento, tablaSegmentos)) {
        *direccionBase = tablaSegmentos[punteroASegmento];
        *direccionBase = *direccionBase >> 16;
        *limSegmento = (tablaSegmentos[punteroASegmento] & 0x0000FFFF) + *direccionBase;
    }
}

//verifica que el IP esté dentro de los límites del segmento de código
int IPEstaEnSegmentoCodigo(int IP, int direccionBase, int limSegmento) {
    if (IP >= direccionBase && IP <= limSegmento)
        return 1;
    else
        if (IP == -1)
            return 0;
        else
            terminarPrograma("IP apunta a una direccion de memoria no permitida");
}

//pone en OPC el número de operación, y en OP1 y OP2 el tipo de operando en el byte más significativo
void decodificarInstruccion(int instruccion, registro registros[]) {
    int indiceOP1 = conseguirIndiceReg("OP1", registros), 
        indiceOP2 = conseguirIndiceReg("OP2", registros), 
        indiceOPC = conseguirIndiceReg("OPC", registros);

    registros[indiceOPC].valor = registros[indiceOP1].valor = registros[indiceOP2].valor = 0;

    //setea OPC
    registros[indiceOPC].valor = registros[indiceOPC].valor | (instruccion & 0x1F);

    //setea OP1
    registros[indiceOP1].valor = registros[indiceOP1].valor | (instruccion & 0x30);
    registros[indiceOP1].valor = registros[indiceOP1].valor << 20;

    //setea OP2
    registros[indiceOP2].valor = registros[indiceOP2].valor | (instruccion & 0xC0);
    registros[indiceOP2].valor = registros[indiceOP2].valor << 18;
}

//obtiene la cantidad de bytes que tiene el operando, lee dichos bytes de la memoria y los guarda en un arreglo para luego pasarlo a un int
void leerOperandosIncrementarIP(char memoria[], registro registros[], int direccionBase, int limiteSegmento) {
    int indiceOP1 = conseguirIndiceReg("OP1", registros),
        indiceOP2 = conseguirIndiceReg("OP2", registros),
        indiceIP = conseguirIndiceReg("IP", registros),
        i, n;
    char operandoBytes[MAX_CANT_BYTES_LEC_ESC];
    
    //incremento IP para pararme en el byte que tengo que leer
    registros[indiceIP].valor++;

    //leo el operando B
    n = registros[indiceOP2].valor >> 24;
    i = 0;
    while (IPEstaEnSegmentoCodigo(registros[indiceIP].valor, direccionBase, limiteSegmento) && i < n) {
        operandoBytes[i] = memoria[registros[indiceIP].valor];
        i++;
        registros[indiceIP].valor++;
    }
    registros[indiceOP2].valor = registros[indiceOP2].valor | convertirArregloAInt(operandoBytes, n);
    
    //leo operando A
    n = registros[indiceOP1].valor >> 24;
    i = 0;
    while (IPEstaEnSegmentoCodigo(registros[indiceIP].valor, direccionBase, limiteSegmento) && i < n) {
        operandoBytes[i] = memoria[registros[indiceIP].valor];
        i++;
        registros[indiceIP].valor++;
    }
    registros[indiceOP1].valor = registros[indiceOP1].valor | convertirArregloAInt(operandoBytes, n);
}

//verifica que el registro sea de los 16 que son válidos
int registroEsValido(int nroRegistro) {
    if (nroRegistro >= 0 && nroRegistro <= 6 || nroRegistro >= 10 && nroRegistro <= 17 || nroRegistro == 26 || nroRegistro == 27)
        return 1;
    else
        terminarPrograma("intento de acceso a un registro invalido");
}

//retorna el contenido de un registro
int conseguirValorRegistro(int operando, registro registros[]) {
    int nroRegistro = operando & 0x0000001F;
    return registros[nroRegistro].valor;
}

//pone la dirección lógica en el LAR
void prepararLAR(int operandoMemoria, registro registros[]) {
    int indiceLAR = conseguirIndiceReg("LAR", registros),
        nroRegistro;

    //quito el tipo de operando en el primer byte
    operandoMemoria = operandoMemoria & 0x00FFFFFF;
    //me quedo con el número de registro
    nroRegistro = operandoMemoria >> 16;
    if (registroEsValido(nroRegistro))
        //pongo en el LAR la dirección lógica que aparece en el registro y a eso le sumo el offset que está en el operando
        registros[indiceLAR].valor = registros[nroRegistro].valor + (operandoMemoria & 0x0000FFFF);
}

//valida la cantidad de bytes que se quieren leer/escribir de memoria. en la primera parte siempre son 4 bytes
int cantBytesEsValida(int cantBytes) {
    if (cantBytes <= TAM_MEMORIA && cantBytes >= 0)
        return 1;
    else
        terminarPrograma("se intentó leer/escribir una cantidad de bytes invalida de memoria");
}

void prepararMAR(registro registros[], int tablaSegmentos[], int cantBytes) {
    int indiceMAR, 
        indiceLAR;

    if (cantBytesEsValida(cantBytes)) {
        indiceMAR = conseguirIndiceReg("MAR", registros),
        indiceLAR = conseguirIndiceReg("LAR", registros);
        
        //pongo en los primeros 2 bytes del MAR la cantidad de bytes a leer/escribir
        registros[indiceMAR].valor = cantBytes << 16;
        //pongo en el resto la dirección física si es válida
        registros[indiceMAR].valor = registros[indiceMAR].valor | conseguirValidarDirFisica(registros[indiceLAR].valor, tablaSegmentos, cantBytes);
    }
}

//valida que el indice de la tabla en la dirección lógica sea menor a 8 y que la tabla tenga un valor válido en esa posición
int indiceSegmentoEsValido(int indiceSegmento, int tablaSegmentos[]) {
    if (indiceSegmento >= 0 && indiceSegmento < TAM_TABLA_SEGMENTOS && tablaSegmentos[indiceSegmento] > -1)
        return 1;
    else
        terminarPrograma("se intentó acceder a un bloque de memoria inexistente");
}

//el nombre es bastante descripitivo
int conseguirValidarDirFisica(int dirLogica, int tablaSegmentos[], int cantBytes) {
    int offset = dirLogica & 0x0000FFFF,
        dirBase,
        limSegmento,
        dirFisica,
        limAcceso;
    
        //consigue la direccioó base y el límite del segmento
        conseguirIntervaloSegmento(dirLogica, tablaSegmentos, &dirBase, &limSegmento);
        //la dirección física es la dirección base más el offset indicado en la dirección lógica
        dirFisica = dirBase + offset;
        limAcceso = dirFisica + cantBytes;
        if (dirBase <= dirFisica && limSegmento >= limAcceso)
            return dirFisica;
        else
            terminarPrograma("fallo de segmento");
}

//crea un arreglo que es una copia de la memoria pero de la porción indicada por MAR, luego ese arreglo lo convierte a int
void leerMemoria(registro registros[], char memoria[]) {
    int indiceMAR = conseguirIndiceReg("MAR", registros),
        indiceMBR = conseguirIndiceReg("MBR", registros),
        cantBytes = registros[indiceMAR].valor >> 16,
        dirFisica = registros[indiceMAR].valor & 0x0000FFFF,
        i, n, j;
    char aux[MAX_CANT_BYTES_LEC_ESC];
        
    //variables para recorrer la memoria
    i = dirFisica;
    n = dirFisica + cantBytes;
    //variable para copiar en el arreglo auxiliar
    j = 0;
    //copia de esa porción de memoria
    for (; i < n; i++) {
        aux[j] = memoria[i];
        j++;
    }
    //pongo el valor en el MBR
    registros[indiceMBR].valor = convertirArregloAInt(aux, cantBytes);
}

//setea los registros necesarios (LAR, MAR) y devuelve el valor del MBR
int conseguirValorEnMemoria(int operandoMemoria, char memoria[], int tablaSegmentos[], registro registros[]) {
    prepararLAR(operandoMemoria, registros);
    prepararMAR(registros, tablaSegmentos, CANT_BYTES_LEC_ESC);
    leerMemoria(registros, memoria);
    return registros[conseguirIndiceReg("MBR", registros)].valor;
}

//pasa a un arreglo char el valor en MBR y lo copia a la memoria en el lugar indicado por MAR
void escribirMemoria(registro registros[], char memoria[]) {
    int indiceMAR = conseguirIndiceReg("MAR", registros),
        indiceMBR = conseguirIndiceReg("MBR", registros),
        cantBytes = (registros[indiceMAR].valor >> 16) & 0x0000FFFF,
        dirFisica = registros[indiceMAR].valor & 0x0000FFFF,
        i, n, j;
    char aux[MAX_CANT_BYTES_LEC_ESC];

    //variables para recorrer la memoria
    i = dirFisica;
    n = dirFisica + cantBytes;
    //variable para copiar en el arreglo auxiliar
    j = 0;
    //convierte el valor en el MBR en un arreglo char
    convertirIntAArreglo(aux, cantBytes, registros[indiceMBR].valor);
    //copiar arreglo a la memoria
    for (; i < n; i++) {
        memoria[i] = aux[j];
        j++;
    }
}

//setea los registros necesarios (LAR, MAR) y pone en memoria el valor en MBR
void ponerValorEnMemoria(int operandoMemoria, char memoria[], int tablaSegmentos[], registro registros[], int valor) {
    prepararLAR(operandoMemoria, registros);
    prepararMAR(registros, tablaSegmentos, CANT_BYTES_LEC_ESC);
    registros[conseguirIndiceReg("MBR", registros)].valor = valor;
    escribirMemoria(registros, memoria);
}