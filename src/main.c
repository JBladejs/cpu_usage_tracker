#include <stdio.h>
#include "common.h"

int main() {

    FILE *fp;
    s8 cpu_name[255];
    fp = fopen("/proc/stat", "r");

    if (fp == NULL) {
        //TODO: handle file read error
    } else {
        s64 user, nice, system, idle;
        fscanf(fp, "%s %ld %ld %ld %ld %*ld %*ld %*ld %*ld %*ld %*ld",
               cpu_name, &user, &nice, &system, &idle);
        printf("cpu: %s, user mode: %ld, nice mode: %ld, system mode: %ld, idle: %ld\n",
               cpu_name, user, nice, system, idle);
        fscanf(fp, "%s %ld %ld %ld %ld %*ld %*ld %*ld %*ld %*ld %*ld",
               cpu_name, &user, &nice, &system, &idle);
        printf("cpu: %s, user mode: %ld, nice mode: %ld, system mode: %ld, idle: %ld\n",
               cpu_name, user, nice, system, idle);
    }
    return 0;
}
