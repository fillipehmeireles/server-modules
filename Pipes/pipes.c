/***
    Pipes

        - pipes.c


    Author: Fillipe Meireles
    Organization: Luspew

    https://github.com/fillipehmeireles/server-modules

***/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

    if(argc < 2){
        printf("[!]Please, provide the command.");
        return -1;
    }

    FILE *fp = popen(argv[1],"r");
    char *buffer = (char *)malloc(sizeof(fp));

    while(fgets(buffer,sizeof(fp),fp) != NULL){
        printf("%s", buffer);
    }

    return 0;
}