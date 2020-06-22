#include "Challenge11.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

const char * challenge11_GetHint(){
    return "Los Simuladores\n";
}

const char * challenge11_GetAnswer(){
    return "TORTUGA MARITIMA";
}

void challenge11_Run(){
    FILE * pf;
    char * fn = "milazzo.txt";

    printf("...\n");

    if ((pf = fopen(fn, "r")) == NULL) {
        printf("Error, Vanegas no pudo encontrar a: %s ¿Estuviste un año en la selva, solo, hablandole a una camara de television apagada? KJJJJJJ \n", fn);
        return;
    }

    printf("Fase 1 completa, Santos \n");
    printf("...\n");
    printf("https://youtu.be/rHs_DBLJIwk 18:44\n");
    printf("...\n");

    if (!feof(pf)) {
        char buffer [24];
        const char * r = "el pavo esta en el saco";
        fgets(buffer, 24, pf);
        if (strcmp(buffer, r) == 0) {
        printf("La respuesta es TORTUGA MARITIMA\n");
        }
    }
    else {
        printf("Lamponne, tenemos un problema... \n");
    }
    fclose(pf);
}