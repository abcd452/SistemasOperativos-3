#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    FILE *fp1; // Se utiliza un apuntador a una estructura FILE de stdio.

    int lastPos; // Posición que va a indicar el final del archivo. 
    int posicionActual = 1; //contador que indica la posición actual dentro del archivo.

    if( argc < 2 ) // Se verifica que se haya ingresado a la shell por lo menos un argumento. 
    {
        printf("La cantidad de argumentos no es la indicada\n");
        printf("Usar la siguiente sintaxis: \" program-name file-name \" format.\n");
        return -1;
    }

    if((access(argv[1],F_OK) == -1) || (access(argv[1], R_OK) == -1)) // Cuando fopen retorna null, significa que hubo un error al abrir el archivo (por permisos o fallos)
    {
        printf("El archivo no puede ser abierto: %s\n ",argv[1]);
        return -1;
    }

    fp1 = fopen(argv[1],"r"); // Función de la libreria STDIO que permite abrir un archivo a traves de su File descriptor
    // La función fseek toma como argumentos el apuntador al "file descriptor", recibe un entero que apunta a la posición especificada
    // teniendo en cuenta que en este caso se esta iniciando al final del archivo dado que al tercer argumento se le esta pasando SEEK_END.
    fseek(fp1,0,SEEK_END);
    // Se guarda el valor (posicional) del final del archivo. 
    lastPos = ftell(fp1);

    while( posicionActual < lastPos ) // El ciclo se hace mientras no se haya llegado a la ultima posición.
    {
        posicionActual++; // Dado que la posición del puntero del File descriptor se encuentra al final, se debe de mover una posición hacia atras la posición actual (que se encuentr aapuntando al final).
        fseek(fp1,-posicionActual,SEEK_END); // Se cambia la posición del puntero avanzando desde el final hacia una posición a la izquierda (por eso se pone -posicionActual).
        printf("%c",fgetc(fp1)); // fgetc lee el caracter del apuntador del archivo y con printf se le especifica el flag %c . 
    }
    printf("\n"); // Salto de línea que permite que no se amontone el texto del archivo con el texto que corresponde al prompt de la shell.
    fclose(fp1); // Se cierra el apuntador al archivo.

    return 0;
}