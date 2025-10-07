#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "constantes.h"
#include "lectura_arch.h"
#include "utils.h"
#include "mem_reg_io.h"

void interpretarParametros(int argc, 
                           char *argv[], 
                           char** nombArchVmx, 
                           char** nombrArchVmi, 
                           int *tamMemoria, 
                           char* params[], 
                           int *cantParams, 
                           int *disassembler) {
    int i = 1;
    *nombArchVmx =  NULL;
    *nombrArchVmi = NULL;
    *tamMemoria = TAM_MEMORIA_DEFAULT;
    *disassembler = *cantParams = 0;

    while (i < argc) {
        if (terminaCon(argv[i], ".vmx"))
            *nombArchVmx = argv[i];
        else
            if (terminaCon(argv[i], ".vmi"))
                *nombrArchVmi = argv[i];
            else
                if (empiezaCon(argv[i], "-d"))
                    *disassembler = 1;
                else
                    if (empiezaCon(argv[i], "m=")) {
                        int tamanio = (int) strtol(argv[i] + 2, NULL, 10);
                        *tamMemoria = tamanio * pow(2, 10);
                    }
                    else 
                        if (empiezaCon(argv[i], "-p")) {
                            i++;
                            *cantParams = argc - i;
                            int j = 0;
                            for (i; i < argc; i++)
                                params[j++] = argv[i];
                        }
        i++;
    }

    // printf("nombre del archivo vmx: %s\n", *nombArchVmx);
    // printf("nombre del archivo vmi: %s\n", *nombrArchVmi);
    // printf("tamanio de la memoria: %d\n", *tamMemoria);
    // printf("disassembler: %d\n", *disassembler);
    // printf("cantidad de parametros: %d\n", *cantParams);
    // printf("parametros:\n");
    // mostrarArrStr(params, *cantParams);
}

void validarArchivo(char *nombArch) {
    FILE *arch;
    
    arch = fopen(nombArch, "rb");
    if (arch == NULL)
        terminarPrograma(strcat("no se pudo abrir el archivo ", nombArch));
    else
        fclose(arch);
}

int versionVmx(char *nombArch) {
    char aux;
    FILE *arch = fopen(nombArch, "rb");
    fseek(arch, 5, SEEK_SET);
    fread(&aux, sizeof(aux), 1, arch);
    fclose(arch);
    //printf("version: %d\n", aux);
    return aux;
}

void inicializarTablaSegmentos(int tablaSegmentos[]) {
    for (int i = 0; i < TAM_TABLA_SEGMENTOS; i++)
        tablaSegmentos[i] = -1;
}

void agregarEntradaTablaSegmentos(int indexTabla, int tamSegmento, int tablaSegmentos[]) {
    if (indexTabla == 0) {
        tablaSegmentos[indexTabla] = 0;
        tablaSegmentos[indexTabla] |= tamSegmento;
    }
    else {
        int base = ((tablaSegmentos[indexTabla-1] >> 16) & 0xFFFF) + (tablaSegmentos[indexTabla-1 & 0xFFFF]);
        tablaSegmentos[indexTabla] = (base << 16) | tamSegmento;
    }
}

void analizarTamanioSegmento(int tamSegmento, int *registro, int *indexTabla, int tablaSegmentos[]) {
    if (tamSegmento == 0)
        *registro = -1;
    else {
        agregarEntradaTablaSegmentos(*indexTabla, tamSegmento, tablaSegmentos);
        *registro = *indexTabla << 16;
        (*indexTabla)++;
    }
}

int tamanioCadenasPS(int cantParam, char *params[]) {
    int tam = cantParam;
    
    for (int i = 0; i < cantParam; i++)
        tam += strlen(params[i]);
    //printf("tamanio cadenas del PS: %d", tam);
    return tam;
}

void cargarParams(int cantParams, char *params[], int dirFisicaInicio, char memoria[]) {
    int indexParametro = 0;
    int indexCaracter = dirFisicaInicio, n, i;
    int indexPuntero = tamanioCadenasPS(cantParams, params) + dirFisicaInicio;

    for (indexParametro; indexParametro < cantParams; indexParametro++) {
        escribirMemoria(4, indexPuntero, indexCaracter, memoria);
        indexPuntero += 4;
        n = strlen(params[indexParametro]) + 1;
        for (i = 0; i < n; i++) {
            memoria[indexCaracter] = params[indexParametro][i];
            indexCaracter++;
        }
    }
}

void leerArchVmx2(char *nombArch, int tamMemoria, int cantParam, char *params[], char memoria[], int registros[], int tablaSegmentos[]) {
    FILE *arch;
    int indexTabla = 0, i, dirFisica;
    unsigned short tamCS, tamDS, tamES, tamSS, tamKS, tamPS, entryPoint;

    arch = fopen(nombArch, "rb");
    fseek(arch, 6, SEEK_SET);
    fread(&tamCS, sizeof(unsigned short), 1, arch);
    fread(&tamDS, sizeof(unsigned short), 1, arch);
    fread(&tamES, sizeof(unsigned short), 1, arch);
    fread(&tamSS, sizeof(unsigned short), 1, arch);
    fread(&tamKS, sizeof(unsigned short), 1, arch);
    swap2Bytes(&tamCS);
    swap2Bytes(&tamDS);
    swap2Bytes(&tamES);
    swap2Bytes(&tamSS);
    swap2Bytes(&tamKS);
    tamPS = tamanioCadenasPS(cantParam, params) + cantParam * 4;

    // printf("tamanio CS: %04X\n", tamCS);
    // printf("tamanio DS: %04X\n", tamDS);
    // printf("tamanio ES: %04X\n", tamES);
    // printf("tamanio SS: %04X\n", tamSS);
    // printf("tamanio KS: %04X\n", tamKS);
    // printf("tamanio PS: %04X\n", tamPS);

    if (tamPS + tamCS + tamDS + tamES + tamSS + tamKS > tamMemoria)
        terminarPrograma("la sumatoria del tamanio de los segmentos supera el tamanio de la memoria");
    
    fread(&entryPoint, sizeof(unsigned short), 1, arch);
    inicializarTablaSegmentos(tablaSegmentos);
    analizarTamanioSegmento(tamPS, &registros[PS_INDEX], &indexTabla, tablaSegmentos);
    analizarTamanioSegmento(tamKS, &registros[KS_INDEX], &indexTabla, tablaSegmentos);
    analizarTamanioSegmento(tamCS, &registros[CS_INDEX], &indexTabla, tablaSegmentos);
    analizarTamanioSegmento(tamDS, &registros[DS_INDEX], &indexTabla, tablaSegmentos);
    analizarTamanioSegmento(tamES, &registros[ES_INDEX], &indexTabla, tablaSegmentos);
    analizarTamanioSegmento(tamSS, &registros[SS_INDEX], &indexTabla, tablaSegmentos);
    registros[SP_INDEX] = registros[SS_INDEX] + tamSS;
    registros[IP_INDEX] = registros[CS_INDEX] + entryPoint;

    if (cantParam != 0)
        cargarParams(cantParam, params, conseguirDirFisica(registros[PS_INDEX], 0, tablaSegmentos), memoria);
    /*CARGAR EN EL SS EL PUNTERO AL VECTOR, LA CANTIDAD DE PARAMS Y EL RET */
    /*HAY QUE CREAR LA FUNCION PUSH*/
    dirFisica = conseguirDirFisica(registros[CS_INDEX], 0, tablaSegmentos);
    for (i = 0; i < tamCS; i++)
        fread(&memoria[dirFisica+ i], sizeof(char), 1, arch);

    dirFisica = conseguirDirFisica(registros[KS_INDEX], 0, tablaSegmentos);
    for (i = 0; i < tamKS; i++)
        fread(&memoria[dirFisica+ i], sizeof(char), 1, arch);
    
    fclose(arch);
}

void leerArchVmx1(char *nombArch, char memoria[], int registros[], int tablaSegmentos[]) {
    FILE *arch;
    unsigned short tamCodigo;
    int indexTabla = 0, i;

    arch = fopen(nombArch, "rb");
    fseek(arch, 6, SEEK_SET);
    fread(&tamCodigo, sizeof(unsigned short), 1, arch);
    swap2Bytes(&tamCodigo);
    if (tamCodigo > TAM_MEMORIA_DEFAULT)
        terminarPrograma("el tamanio del codigo supera al tamanio de la memoria");

    inicializarTablaSegmentos(tablaSegmentos);
    analizarTamanioSegmento(tamCodigo, &registros[CS_INDEX], &indexTabla, tablaSegmentos);
    analizarTamanioSegmento(TAM_MEMORIA_DEFAULT-tamCodigo, &registros[DS_INDEX], &indexTabla, tablaSegmentos);
    registros[IP_INDEX] = registros[CS_INDEX];
    for (i = 0; i < tamCodigo; i++)
        fread(&memoria[i], sizeof(char), 1, arch);
    fclose(arch);
}

void crearVmi(char *nombArch, int tamMemoria, char memoria[], int registros[], int tablaSagmentos[]) {
    char identificador[] = {'V', 'M', 'I', '2', '5'},
         version = 1,
         auxc;
    int tamId = sizeof(identificador) / sizeof(identificador[0]),
        i,
        j;
    unsigned short tamMemoria2Bytes = (unsigned short) tamMemoria / 1024;
    FILE  *arch;

    arch = fopen(nombArch, "wb");
    fwrite(&identificador, sizeof(identificador[0]), tamId, arch);
    fwrite(&version, sizeof(version), 1, arch);
    swap2Bytes(&tamMemoria2Bytes);
    fwrite(&tamMemoria2Bytes, sizeof(tamMemoria2Bytes), 1, arch);
    
    for (i = 0; i < TAM_REGISTROS; i++) {
        for (j = 0; j < 4; j++) {
            auxc = (char) (registros[i] >> (24-j*8));
            fwrite(&auxc, sizeof(char), 1, arch);
        }
    }
    
    for (i = 0; i < TAM_TABLA_SEGMENTOS; i++) {
        for (j = 0; j < 4; j++) {
            auxc = (char) (tablaSagmentos[i] >> (24-j*8));
            fwrite(&auxc, sizeof(char), 1, arch);
        }
    }
    
    for (i = 0; i < tamMemoria; i++)
        fwrite(&memoria[i], sizeof(char), 1, arch);
}

void cargarVmi(char *nombArch, int *tamMemoria, char memoria[], int registros[], int tablaSegmentos[]) {
    FILE *arch;
    unsigned short auxTamMemoria;
    unsigned char auxByte;
    int i, j;

    arch = fopen(nombArch, "rb");
    fseek(arch, 6, SEEK_SET);
    fread(&auxTamMemoria, sizeof(auxTamMemoria), 1, arch);
    swap2Bytes(&auxTamMemoria);
    *tamMemoria = (int) auxTamMemoria * 1024;

    for (i = 0; i < TAM_REGISTROS; i++) {
        registros[i] = 0;
        for (j = 0; j < 4; j++) {
            fread(&auxByte, sizeof(auxByte), 1, arch);
            registros[i] |= auxByte << (24-(j*8));
        }
    }

    for (i = 0; i < TAM_TABLA_SEGMENTOS; i++) {
        tablaSegmentos[i] = 0;
        for (j = 0; j < 4; j++) {
            fread(&auxByte, sizeof(auxByte), 1, arch);
            tablaSegmentos[i] |= auxByte << (24-(j*8));
        }
    }

    for (i = 0; i < *tamMemoria; i++)
        fread(&memoria[i], sizeof(char), 1, arch);
    
    fclose(arch);
}

void leerArch(char *argv[], int argc, char **nombArchVmi, int *disassembler, int *tamMemoria, char memoria[], int registros[], int tablaSegmentos[]) {
    char *nombArchVmx, *params[MAX_PARAMS];
    int cantParams, version;

    interpretarParametros(argc, argv, &nombArchVmx, nombArchVmi, tamMemoria, params, &cantParams, disassembler);

    if (*tamMemoria > TAM_MEMORIA)
        terminarPrograma("el tamanio de memoria principal excede la maxima posible");

    if (nombArchVmx != NULL) {
        validarArchivo(nombArchVmx);
        version = versionVmx(nombArchVmx);
        if (version == 1)
            leerArchVmx1(nombArchVmx, memoria, registros, tablaSegmentos);
        else
            leerArchVmx2(nombArchVmx, *tamMemoria, cantParams, params, memoria, registros, tablaSegmentos);
    }
    else
        if (*nombArchVmi != NULL) {
            validarArchivo(*nombArchVmi);
            cargarVmi(*nombArchVmi, tamMemoria, memoria, registros, tablaSegmentos);
        }
        else
            terminarPrograma("no se proporciono el nombre de ningun archivo .vmx o .vmi");
}