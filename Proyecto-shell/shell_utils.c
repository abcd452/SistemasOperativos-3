#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/types.h>

int showHelp()
{
    __pid_t rc = fork();
    if(rc < 0 )
    {
        fprintf(stderr,"Failed to create process child\n");
        return -1;
    }else if (rc == 0)
    {
        char *myargs[4];
        myargs[0] = strdup("more");
        myargs[1] = strdup("-6");
        myargs[2] = strdup("man.help");
        myargs[3] = NULL;
        execvp(myargs[0],myargs);
    }else
    {   
        int status_code;
        __pid_t rc_wait = wait(&status_code);
        if(status_code != 0)
        {
            fprintf(stderr,"An Errror ocurred until read manual page");
            return -1;
        } 
    }
    
    return 0;

}

int pauseOperation()
{
    int back  = 1;
    printf("Press Enter to continue ... \n");
    int firstChar = 10;
    int newChar;
    while (back)
    {
        newChar = getchar();
        if(firstChar == 10 && newChar == 10)
        {
            back = 0;
        }
        else
        {
            firstChar = newChar;
        }
    }

    return 0;
}

void echo(char stream_command[],int size)
{
    int enter = 1;
            for(int i = 4; i < size; i++)
            {   
                if('\t' == stream_command[i] || ' ' == stream_command[i])
                {   
                    if(enter)
                    {
                        printf(" ");
                        enter = 0;
                    }
                    
                }
                else if('\0' == stream_command[i])
                {
                    break;
                }
                else
                {
                    printf("%c",stream_command[i]);
                    enter = 1;
                }
                
            }
            printf("\n");
}

void dir(char* directory,char defaultDir[])
{
    DIR *dp;
            struct dirent *ep;

            if(directory == NULL)
            {
                dp = opendir(defaultDir);
            }else{
                opendir(directory);
            }
            if(dp != NULL)
            {
                ep = readdir(dp);
                while (ep = readdir(dp))
                {
                    printf("%s\t",ep->d_name);
                }
                printf("\n");
                (void) closedir(dp);                
            }else
            {
                fprintf(stderr,"Can't open directory");
            }
}
