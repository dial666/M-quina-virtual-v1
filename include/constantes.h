#ifndef CONSTANTES_H
#define CONSTANTES_H

#define TAM_MEMORIA 65535
#define TAM_MEMORIA_DEFAULT 16384
#define TAM_REGISTROS 32 
#define TAM_TABLA_SEGMENTOS 8
#define CANT_BYTES_TAM_CODIGO 2

#define CS_SEG_INDEX 0
#define DS_SEG_INDEX 1

#define LAR_INDEX 0
#define MAR_INDEX 1
#define MBR_INDEX 2
#define IP_INDEX 3
#define OPC_INDEX 4
#define OP1_INDEX 5
#define OP2_INDEX 6 
#define SP_INDEX 7

#define EAX_INDEX 10
#define EBX_INDEX 11
#define ECX_INDEX 12
#define EDX_INDEX 13
#define EEX_INDEX 14
#define EFX_INDEX 15

#define AC_INDEX 16
#define CC_INDEX 17

#define CS_INDEX 26
#define DS_INDEX 27
#define ES_INDEX 28
#define SS_INDEX 29
#define KS_INDEX 30
#define PS_INDEX 31

#define CANT_OP 32
#define MAX_STR_LEN 4
#define MAX_PARAMS 50

extern const char* const NOMBRE_REG[TAM_REGISTROS];

extern const char* const MNEMONICOS[CANT_OP];


#endif