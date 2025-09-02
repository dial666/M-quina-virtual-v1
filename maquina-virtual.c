#include <stdio.h>


int main(int argc, char *argv[]) {
    int registros[32]; //32 registros de 32 bits
    char memoria[16384];  //16 KiB
    int tablasegmentos[8]; //8 entradas de 32 bits

    FILE *archbin;
    char aux;

    archbin = fopen(argv[1], "rb");
    if (archbin == NULL) {
        printf("no se pudo abrir el archivo %s\n", argv[1]);
    }
    else {
        fclose(archbin);
    }
    return 0;
}