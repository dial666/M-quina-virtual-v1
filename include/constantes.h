#ifndef CONSTANTES_H
#define CONSTANTES_H

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

#define CANT_OP 32
#define MAX_STR_LEN 4

static const char* const NOMBRE_REG[TAM_REGISTROS] = {
    [0x00] = "LAR",
    [0x01] = "MAR",
    [0x02] = "MBR",
    [0x03] = "IP",
    [0x04] = "OPC",
    [0x05] = "OP1",
    [0x06] = "OP2",
    [0x07] = "",
    [0x08] = "",
    [0x09] = "",
    [0x0A] = "EAX",
    [0x0B] = "EBX",
    [0x0C] = "ECX",
    [0x0D] = "EDX",
    [0x0E] = "EEX",
    [0x0F] = "EFX",
    [0x10] = "AC",
    [0x11] = "CC",
    [0x12] = "",
    [0x13] = "",
    [0x14] = "",
    [0x15] = "",
    [0x16] = "",
    [0x17] = "",
    [0x18] = "",
    [0x19] = "",
    [0x1A] = "CS",
    [0x1B] = "DS",
    [0x1C] = "",
    [0x1D] = "",
    [0x1E] = "",
    [0x1F] = ""
};

static const char* const MNEMONICOS[CANT_OP] = {
    [0x00] = "SYS",
    [0x01] = "JMP",
    [0x02] = "JZ",
    [0x03] = "JP",
    [0x04] = "JN",
    [0x05] = "JNZ",
    [0x06] = "JNP",
    [0x07] = "JNN",
    [0x08] = "NOT",
    [0x09] = "",     
    [0x0A] = "",     
    [0x0B] = "",     
    [0x0C] = "",     
    [0x0D] = "",     
    [0x0E] = "",     
    [0x0F] = "STOP",
    [0x10] = "MOV",
    [0x11] = "ADD",
    [0x12] = "SUB",
    [0x13] = "MUL",
    [0x14] = "DIV",
    [0x15] = "CMP",
    [0x16] = "SHL",
    [0x17] = "SHR",
    [0x18] = "SAR",
    [0x19] = "AND",
    [0x1A] = "OR",
    [0x1B] = "XOR",
    [0x1C] = "SWAP",
    [0x1D] = "LDL",
    [0x1E] = "LDH",
    [0x1F] = "RND"
};


#endif