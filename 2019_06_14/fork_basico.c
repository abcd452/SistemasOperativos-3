#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

/** 
 
Soy el hijo y mi identificador es 34567
Soy el padre, mi identificador es 34566 y el de mi hijo es 34567

*/

int main(int argc, char** argv)
{
    pid_t pid;

    pid = fork();
    if(pid == 0)
    {
        printf("Soy el hijo y mi identificador es: %d\n",getpid());
    }else
    {
        int status;
        int rc_wait = wait(&status);
        printf("Soy el padre, mi identificador es: %d y el de mi hijo es: %d \n",getpid(),rc_wait);    
    }
    
    return 0;
}