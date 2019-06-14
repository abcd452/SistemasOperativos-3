#include "solucion.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
  int x = 20;
  __pid_t pid;


  pid = fork();
  if(pid==0)
  {
    printf("fibonacci(%d) = ",x);
    x = fibonacci(x);
    printf("%d\n",x);
    guardarEntero("archivo",x);
  }else
  {
    int status;
    int rc = wait(&status);
    if(status != 0)
    {
        return -1;    
    }
    int fibo = leerEntero("archivo");
    printf("El valor de fibonacci multiplicado por 100 es %d\n", fibo*1000);
  }
  
  return 0;
}