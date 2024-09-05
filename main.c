#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char *argv[]){
    uid_t uid = getuid();
    if (uid != 0) {
        printf("Sentinel only run a root\n");
        exit(6);
    }

    if(argv[1]){
        if(strcmp("--help", argv[1]) == 0){
            printf("%s\n", helpMessage);
        }

        if(strcmp("-s", argv[1]) == 0){
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            sprintf(_date, "./%d%02d%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
            sprintf(commandDmesg, "cp -f /var/log/dmesg %s", _date);
            sprintf(commandGpu, "cp -f /var/log/gpu-manager.log %s", _date);
            sprintf(commandBoot, "cp -f /var/log/boot.log.7 %s", _date);
            mkdir(_date, 777);
            while(1000){
                system(commandDmesg);
                system(commandGpu);
                system(commandBoot);
            }
        }
    } else {
        printf("Invalid command type --help for more information\n");
    }
}
