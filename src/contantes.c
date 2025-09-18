#include "constantes.h"
#include <stdio.h>

const char* const NOMBRE_REG[TAM_REGISTROS] = {
    "LAR",  // 0
    "MAR",  // 1
    "MBR",  // 2
    "IP",   // 3
    "OPC",  // 4
    "OP1",  // 5
    "OP2",  // 6
    "null",   // 7
    "null",   // 8
    "null",   // 9
    "EAX",  // 10
    "EBX",  // 11
    "ECX",  // 12
    "EDX",  // 13
    "EEX",  // 14
    "EFX",  // 15
    "AC",   // 16
    "CC",   // 17
    "null",   // 18
    "null",   // 19
    "null",   // 20
    "null",   // 21
    "null",   // 22
    "null",   // 23
    "null",   // 24
    "null",   // 25
    "CS",   // 26
    "DS",   // 27
    "null",   // 28
    "null",   // 29
    "null",   // 30
    "null"    // 31
};

const char* const MNEMONICOS[CANT_OP] = {
    "SYS",   // 0x00
    "JMP",   // 0x01
    "JZ",    // 0x02
    "JP",    // 0x03
    "JN",    // 0x04
    "JNZ",   // 0x05
    "JNP",   // 0x06
    "JNN",   // 0x07
    "NOT",   // 0x08
    "null",    // 0x09
    "null",    // 0x0A
    "null",    // 0x0B
    "null",    // 0x0C
    "null",    // 0x0D
    "null",    // 0x0E
    "STOP",  // 0x0F
    "MOV",   // 0x10
    "ADD",   // 0x11
    "SUB",   // 0x12
    "MUL",   // 0x13
    "DIV",   // 0x14
    "CMP",   // 0x15
    "SHL",   // 0x16
    "SHR",   // 0x17
    "SAR",   // 0x18
    "AND",   // 0x19
    "OR",    // 0x1A
    "XOR",   // 0x1B
    "SWAP",  // 0x1C
    "LDL",   // 0x1D
    "LDH",   // 0x1E
    "RND"    // 0x1F
};
