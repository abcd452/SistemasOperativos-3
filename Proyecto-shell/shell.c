#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include "shell_utils.h"

char PWD[PATH_MAX]; // Variable que guarda el directorio desde donde se ejecuto el SHELL
char SHELL_PATH[PATH_MAX]; // Variable que guarda el directorio donde esta el SHELL 
char *p;

int main(int argc, char* argv[])
{
    char stream_command[512];
    getcwd(PWD, sizeof(PWD)); // Función de la libreria unistd que permite obtener el directorio de trabajo actual.
    if(!(p = strrchr(argv[0],'/'))) // Función que se uso para saber desde donde se ejecutaba
    {
        strcpy(SHELL_PATH,p);
    }else
    {
        // La estrategia usada aqui es: Como el programa se llamo desde un directorio que no era la raiz del programa, entonces
        // se hace un cambio hacia ese directorio, se guarda y luego se vuelve al directorio desde donde se llamo el programa. 
        char AUX_PATH[PATH_MAX];
        char * AUX_NAME = strchr(p,'/'); 
        char PROGRAM_NAME[PATH_MAX];
        strcpy(PROGRAM_NAME,AUX_NAME);
        * p = '\0'; 
        getcwd(AUX_PATH, sizeof(AUX_PATH));
        chdir(argv[0]); // Función de unistd que permite cambiar entre directorios.
        getcwd(SHELL_PATH,sizeof(SHELL_PATH));
        strcat(SHELL_PATH,PROGRAM_NAME);
        chdir(AUX_PATH);
    }
   

    printf(" _______                      \n");
    printf("< SHELL >                     \n");
    printf(" -------                      \n");
    printf("       \\  ^__^               \n");
    printf("        \\ (oo)\\_______      \n");
    printf("          (__)\\       )\\/\\ \n");
    printf("              ||----w||       \n");
    printf("              ||     ||     \n\n");

    char stream_token[512];
    char *token;
    char delimitador[3] = " "; 
    do
    {
        printf("$_ ");
        scanf("%[^\n]s",stream_command);
        fgetc(stdin);
        fflush(stdin);
        /////
        strcpy(stream_token,stream_command);
        token = strtok(stream_token,delimitador); 
        ///// 
        if(!strcmp("quit",stream_command))
        {
            printf("\n");
            break;
        }
        else if(!strcmp("environ",stream_command))
        {
            printf("$PWD=%s:$shell=%s\n",PWD,SHELL_PATH);  
        }
        else if(!strcmp("clr",stream_command))
        {   
            system("clear");
        }
        else if(!strcmp("help",stream_command))
        {
            showHelp();
        }
        else if(!strcmp("pause",stream_command))
        {
            pauseOperation();
        }    
        else if(token != NULL && !strcmp("cd",token))
        {
            token = strtok(NULL," ");
            if(token == NULL)
            {
                __uid_t uid = getuid();
                struct passwd * pw = getpwuid(uid);
                if(pw == NULL)
                {
                    fprintf(stderr,"Fail to get user $HOME\n");
                    exit(EXIT_FAILURE);
                }
                chdir(pw->pw_dir);
                getcwd(PWD, sizeof(PWD));
            }else
            {   
                if(chdir(token) != 0)
                {
                    fprintf(stderr,"Invalid destination path\n");
                }
                getcwd(PWD, sizeof(PWD));
            }
   
        }
        else if(token != NULL && !strcmp("echo",token))
        {
            echo(stream_command,sizeof(stream_command));
        }
        else if(token != NULL && !strcmp("dir",token))
        {
            token = strtok(NULL," ");
            if(token == NULL)
            {
                dir(NULL,PWD);
            }else
            {
                dir(token,PWD);
            }
        }
        //
        else{
            
        }
        memset(stream_command,'\0',512);


    } while (1);
    

    return 0;
}