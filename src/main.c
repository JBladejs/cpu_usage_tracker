#include <stdio.h>
#include <malloc.h>
#include "common.h"

typedef struct CpuStats {
    u64 user;
    u64 nice;
    u64 system;
    u64 idle;
    u64 iowait;
    u64 irq;
    u64 softirq;
    u64 steal;
} CpuStats;

//TODO: don't open and close /proc/stat multiple times

/* Core count includes one additional core which is the total of all cores */
u16 get_core_count() {
    FILE *fp;
    fp = fopen("/proc/stat", "r");

    if (fp == NULL) {
        //TODO: handle file read error
    } else {
        s8 cpu_name[255];
        cpu_name[0] = 'c';
        u16 core_count;

        while (cpu_name[0] == 'c') {
            core_count++;
            fscanf(fp, "%s %*ld %*ld %*ld %*ld %*ld %*ld %*ld %*ld %*ld %*ld", cpu_name);
        }

        return --core_count;
    }
}

void get_stats(CpuStats *stat, u16 core_count) {
    FILE *fp;
    fp = fopen("/proc/stat", "r");

    if (fp == NULL) {
        //TODO: handle file read error
    } else {
        s64 user, nice, system, idle;
        for (int i = 0; i < core_count; ++i) {
            CpuStats *current = &stat[i];
            fscanf(fp, "%*s %ld %ld %ld %ld %ld %ld %ld %ld %*ld %*ld",
                   &current->user, &current->nice, &current->system, &current->idle,
                   &current->iowait, &current->irq, &current->softirq, &current->steal);
        }
    }
}

int main() {
    u16 core_count = get_core_count();
    CpuStats *stats = malloc(sizeof(CpuStats) * core_count);
    get_stats(stats, core_count);
    for (int i = 0; i < core_count; ++i) {
        printf("cpu%d user: %ld\n", i, stats[i].user);
    }
}
