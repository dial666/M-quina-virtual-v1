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

/**
 * @brief Verifica el índice usado para acceder a la tabla de segmentos.
 * 
 * Verifica que el índice sea menor a 8 y que la tabla tenga un valor válido en esa posición.
 * Es decir, que tenga un valor distinto a -1.
 * Si el índice no es válido, termina el programa.
 * 
 * @param indiceSegmento Los 2 bytes más significativos de una dirección lógica.
 * @param tablaSegmentos 
 * 
 * @pre La tabla de segmentos debe estar inicializada con -1 o un valor válido.
 */
void verificarIndiceSegmento(int indiceSegmento, int tablaSegmentos[]) {
    if (!(indiceSegmento >= 0 && indiceSegmento < TAM_TABLA_SEGMENTOS && tablaSegmentos[indiceSegmento] > -1))
        terminarPrograma("se intentó acceder a un bloque de memoria inexistente");
}

/**
 * @brief Pone en el MAR los datos necesarios o termina el porgrama si son incorrectos.
 * 
 * Crea la dirección física a partir de la dirección lógica en LAR.
 * Si la dirección base del segmento apuntado por los primeros 2 bytes de la
 * dirección lógica es menor o igual a la dirección física y el límite de acceso
 * es menor al límite del segmento, en los 2 bytes más significativos de MAR irá 
 * la cantidad de bytes a leer/escribir y en los otros 2 irá la dirección física.
 * De no cumplirse, termina el programa.
 * 
 * @param cantBytes Cantidad de bytes a leer/escribir en memoria.
 * @param registros 
 * @param tablaSegmentos
 * 
 * @pre LAR debe tener algún valor.
 * @pre cantBytes debe ser menor o igual a 4.
 */
void cargarMAR(int cantBytes, int registros[], int tablaSegmentos[]){
    int dirLogica = registros[LAR_INDEX];
    int offset = dirLogica & 0x0000FFFF;
    int segmentIndex = dirLogica >> 16;

    verificarIndiceSegmento(segmentIndex, tablaSegmentos);

    int dirBase = tablaSegmentos[segmentIndex] >> 16; //si empieza con bit 1 habria problemas de signo
    int tamanioSegmento = tablaSegmentos[segmentIndex] & 0x0000FFFF;

    int dirFisica = dirBase + offset;
    if( (dirBase <= dirFisica) && ( (dirBase + tamanioSegmento) >= (dirFisica + cantBytes) ) ){
        registros[MAR_INDEX] = (cantBytes << 16) | ((dirFisica) & (0x0000FFFF)); //CREO QUE EL ULTIMO & ESTA DE MAS PERO REVISAR
        //printf("cantBytes: %X MAR2: %X\n",cantBytes, registros[MAR_INDEX]);
    }
    else
        terminarPrograma("segmentation fault");

}

/**
 * @brief Pone en MBR un valor leído de memoria.
 * 
 * Extrae la cantidad de bytes a leer y la dirección física de MAR.
 * Utiliza una variable auxiliar inicializada en 0 con la cual, mediante
 * corrimientos y la operación OR con cada celda de memoria, convierte lo guardado
 * en varias celdas de memoria a un valor int. 
 * Se asegura de restaurar el signo del número leído.
 * Al final, lo guarda en MBR.
 * 
 * @param memoria 
 * @param registros 
 * 
 * @pre En MAR debe haber en los 2 bytes más significativos la cantidad de bytes
 * a leer y en los otros 2 una dirección física válida.
 */
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

/**
 * @brief Pone en MBR un valor.
 * 
 * @param registros 
 * @param valor
 * 
 * @see store() 
 */
void cargarMBR(int registros[], int valor){
    registros[MBR_INDEX] = valor;
}

/**
 * @brief Pone en las celdas de memoria un valor guardado en MBR.
 * 
 * Extrae la cantidad de bytes a leer y la dirección física de MAR.
 * Guarda byte por byte en las celdas de memoria con la representación big-endian.
 * El proceso de guardado es el siguiente:
 * -Mueve hacia la izquierda el valor en MBR, dejando el byte a guardar en el 
 * más significativo.
 * -Lo baja a los 8 bits más bajos.
 * -Lo asigna a la celda de memoria correspondiente y como esta es char, solamente
 * se queda con los 8 bits menos significativos del resultado de los desplazamientos.
 * Es decir, no importa si se propagaron 1s en el proceso.
 * 
 * @param memoria 
 * @param registros 
 * @param tablaSegmentos 
 * 
 * @pre En MAR debe haber en los 2 bytes más significativos la cantidad de bytes
 * a leer y en los otros 2 una dirección física válida.
 * @pre En MBR debe haber un valor.
 */
void escribirMemoria(char memoria[], int registros[], int tablaSegmentos[]){
    int cantBytes = registros[MAR_INDEX] >> 16;
    int direccion = registros[MAR_INDEX] & 0x0000FFFF;

    int valor = registros[MBR_INDEX];

    //printf("cantBytes: %X direccion:%X valor:%X\n", cantBytes, direccion, valor);
    for(int i = 1; i <= cantBytes; i++)
        memoria[direccion + cantBytes - i] = (valor << (32-i*8)) >> 24; //shiftea el byte que quiero escribir hasta el byte mas significativo y luego lo shiftea hasta el byte menos significativo
        //creo que el char trunca y toma el byte menos significativo del int, asi que tambien podria ser:
        //memoria[direccion + cantBytes - i] = valor >> (i*8-8);
}

/**
 * @brief Invoca las funciones necesarias para escribir en memoria en el orden correcto.
 * 
 * @param memoria 
 * @param registros 
 * @param tablaSegmentos 
 * @param dirLogica Dirección lógica derivada de un operando de memoria.
 * @param cantBytes Cantidad de bytes/celdas a escribir en memoria.
 * @param valor Valor a escribir en memoria.
 * 
 * @pre cantBytes debe ser menor o igual a 4.
 */
void store(char memoria[], int registros[], int tablaSegmentos[], int dirLogica, int cantBytes, int valor){
    cargarLAR(dirLogica, registros);
    cargarMAR(cantBytes, registros, tablaSegmentos);
    cargarMBR(registros, valor);
    escribirMemoria(memoria, registros, tablaSegmentos);
}

/**
 * @brief Valida que un registro exista.
 * 
 * @param indexReg Índice de un registro.
 */
void verificarIndiceRegistro(int indexReg) {
    if (!(indexReg>=0 && indexReg<=6 || indexReg>=10 && indexReg<=17 || indexReg==26 || indexReg==27))
        terminarPrograma("intento de acceso a un registro inexistente");
}

/**
 * @brief Escribe en un registro o en memoria un valor.
 * 
 * Extrae el tipo de operando y el resto de los datos (registro, offset) del
 * operando.
 * Realiza distintas instrucciones de escritura de acuerdo al tipo de operando.
 * Si es de memoria, controla que la suma del offset de la dirección lógica en el 
 * registro indicado por el operando y el offset del operando no superen los 2
 * bytes.
 * Esto es para que no ocurra un overflow y se "contamine" el puntero a la
 * dirección del segmento en la dirección lógica.
 * De no cumplirse esta condición, se termina el programa.
 * Si se cumple, se arma la nueva dirección lógica y se invoca a store(). 
 * 
 * @warning Quizás sea mejor hacer dicha validación en su propia función.
 * 
 * @param memoria 
 * @param registros 
 * @param tablaSegmentos 
 * @param operando Valor del registro OP1 u OP2.
 * @param valor Valor a escribir en registro o en memoria.
 * 
 * @pre El operando no es de tipo inmediato.
 */
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
        int base = registros[reg];
        int seg = (base >> 16) & 0xFFFF;
        int baseOff = base & 0xFFFF;
        int nuevoOff = baseOff + offset;
        if (nuevoOff < 0 || nuevoOff > 0xFFFF)
            terminarPrograma("segmentation fault: offset fuera de rango");
        int dirLog = (seg << 16) | (nuevoOff & 0xFFFF);
        store(memoria, registros, tablaSegmentos, dirLog, 4, valor);
    }
    else
        terminarPrograma("Solo es posible escribir en un registro o direccion de memoria");
}

/**
 * @brief Obtiene el valor de un operando.
 * 
 * @warning Cuando el operando es de memoria, no verifica que no haya overflow con
 * el offset, algo que sí se hace en escribirMemoriaRegistro().
 * @see escribirMemoriaRegistro().
 * 
 * @param operando Valor en OP1 u OP2.
 * @param memoria 
 * @param registros 
 * @param tablaSegmentos 
 * @return int Valor del operando.
 */
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
        ////printf("registro: %X offset:%X\n", registro, offset);
        int dirLogica = registros[registro] + offset;
        fetch(memoria, registros, tablaSegmentos, dirLogica, 4);
        return registros[MBR_INDEX];
    }
    else
        terminarPrograma("Un operando de tipo ninguno no puede convertirse a un inmediato");

}

/**
 * @brief Invoca las funciones necesarias para leer de memoria en el orden correcto.
 * 
 * @param memoria 
 * @param registros 
 * @param tablaSegmentos 
 * @param dirLogica Dirección lógica derivada de un operando de memoria.
 * @param cantBytes Cantidad de bytes/celdas a leer de memoria.
 */
void fetch(char memoria[], int registros[], int tablaSegmentos[], int dirLogica, int cantBytes){
    cargarLAR(dirLogica, registros);
    cargarMAR(cantBytes, registros, tablaSegmentos);
    leerMemoria(memoria, registros);
}