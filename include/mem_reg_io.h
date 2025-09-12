#ifndef MEM_REG_IO_H
#define MEM_REG_IO_H

/**
 * @file mem_reg_io.h
 * @brief Contiene funciones relacionadas a la escritura y lectura de registros
 * y de memoria.
 */

void cargarLAR(int dirLogica, int registros[]);
void verificarIndiceSegmento(int indiceSegmento, int tablaSegmentos[]);
void cargarMAR(int cantBytes, int registros[], int tablaSegmentos[]);
void leerMemoria(char memoria[], int registros[]);
void cargarMBR(int registros[], int valor);
void escribirMemoria(char memoria[], int registros[], int tablaSegmentos[]);
void store(char memoria[], int registros[], int tablaSegmentos[], int dirLogica, int cantBytes, int valor);
void escribirMemoriaRegistro(char memoria[], int registros[], int tablaSegmentos[], int operando, int valor);
int OperandotoInmediato(int operando, char memoria[], int registros[], int tablaSegmentos[]);
void verificarIndiceRegistro(int indexReg);
void fetch(char memoria[], int registros[], int tablaSegmentos[], int dirLogica, int cantBytes);

#endif