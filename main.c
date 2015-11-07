#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main()
{
    uint32_t mensajeCodificado;

    uint8_t d=59,inicio=1<<7,f;

    uint32_t contador, inicio1 = 1<<31;

    mensajeCodificado=codificar(d);

    printf("\nMensaje:\n");
    for(contador = inicio; contador > 0; contador >>= 1)
        if(contador & d)
            printf("1");
        else
            printf("0");


    printf("\n\nMensaje codificado:\n");
    for(contador = inicio1; contador > 0; contador >>= 1)
        if(contador & mensajeCodificado)
            printf("1");
        else
            printf("0");

        printf("\n\n\n");




        f=decodificar(mensajeCodificado);

         printf("\n\nMensaje decodificado:\n");
    for(contador = inicio; contador > 0; contador >>= 1)
        if(contador & f)
            printf("1");
        else
            printf("0");

        printf("\n\n\n");







    return 0;
}
