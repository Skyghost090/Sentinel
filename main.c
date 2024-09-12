#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "main.h"

void gpuLog_(){
    sprintf(gpuFileOutput, "%s/gpu-manager.log", _date);
    input = open("/var/log/gpu-manager.log", O_RDONLY);
    inputSize = lseek(input,0,SEEK_END);
    lseek(input,0,SEEK_SET);
    char buffer[inputSize];
    mkdir(_date, 777);
    output = open(gpuFileOutput, O_CREAT, 0777);
    close(output);
    output = open(gpuFileOutput, O_RDWR);
    lseek(output,0,SEEK_SET);
    gpuLog = read(input, buffer, inputSize);
    write(output, buffer, strlen(buffer));
}

void dmesg_(){
    sprintf(dmesgOutput, "%s/dmesg", _date);
    input = open("/var/log/dmesg", O_RDONLY);
    inputSize = lseek(input,0,SEEK_END);
    lseek(input,0,SEEK_SET);
    char buffer[inputSize];
    mkdir(_date, 777);
    output = open(dmesgOutput, O_CREAT, 0777);
    close(output);
    output = open(dmesgOutput, O_RDWR);
    while(1000){
        lseek(output,0,SEEK_SET);
        dmesg = read(input, buffer, inputSize);
        write(output, buffer, strlen(buffer));
    }
}

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
            gpuLog_();
            dmesg_();
        }
    } else {
        printf("Invalid command type --help for more information\n");
    }
}
