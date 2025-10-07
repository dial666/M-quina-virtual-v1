#ifndef LECTURA_ARCH_H
#define LECTURA_ARCH_H

void interpretarParametros(int argc, 
                           char *argv[], 
                           char** nombArchVmx, 
                           char** nombrArchVmi, 
                           int *tamMemoria, 
                           char* params[], 
                           int *cantParams, 
                           int *disassembler);

void validarArchivo(char *nombArch);
int versionVmx(char *nombArch);
void inicializarTablaSegmentos(int tablaSegmentos[]);
void agregarEntradaTablaSegmentos(int indexTabla, int tamSegmento, int tablaSegmentos[]);
void analizarTamanioSegmento(int tamSegmento, int *registro, int *indexTabla, int tablaSegmentos[]);
int tamanioCadenasPS(int cantParam, char *params[]);
void cargarParams(int cantParams, char *params[], int dirFisicaInicio, char memoria[]);
void leerArchVmx2(char *nombArch, int tamMemoria, int cantParam, char *params[], char memoria[], int registros[], int tablaSegmentos[]);
void leerArchVmx1(char *nombArch, char memoria[], int registros[], int tablaSegmentos[]);
void crearVmi(char *nombArch, int tamMemoria, char memoria[], int registros[], int tablaSagmentos[]);
void cargarVmi(char *nombArch, int *tamMemoria, char memoria[], int registros[], int tablaSegmentos[]);
void leerArch(char *argv[], int argc, char **nombArchVmi, int *disassembler, int *tamMemoria, char memoria[], int registros[], int tablaSegmentos[]);

#endif