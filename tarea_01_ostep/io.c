#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    FILE *fp1;

    int lastPos;
    int posicionActual = 1;

    if( argc < 2 )
    {
        printf("La cantidad de argumentos no es la indicada\n");
        printf("Usar la siguiente sintaxis: \" program-name file-name \" format.\n");
        return -1;
    }

    if((access(argv[1],F_OK) == -1) || (access(argv[1], R_OK) == -1))
    {
        printf("El archivo no puede ser abierto: %s\n ",argv[1]);
        return -1;
    }

    fp1 = fopen(argv[1],"r");

    fseek(fp1,0,SEEK_END);

    lastPos = ftell(fp1);

    while( posicionActual < lastPos )
    {
        posicionActual++;
        fseek(fp1,-posicionActual,SEEK_END);
        printf("%c",fgetc(fp1));
    }
    printf("\n");
    fclose(fp1);

    return 0;
}