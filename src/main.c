#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
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

f64 get_cpu_usage(CpuStats *stat) {
    CpuStats *prev = &stat[0];
    CpuStats *current = &stat[1];
    u64 total_prev = prev->user + prev->nice + prev->system + prev->idle + prev->iowait + prev->irq + prev->softirq + prev->steal;
    u64 total_current = current->user + current->nice + current->system + current->idle + current->iowait + current->irq + current->softirq + current->steal;
    u64 total_diff = total_current - total_prev;
    u64 idle_diff = current->idle - prev->idle;
    f64 usage = (f64) (total_diff - idle_diff) / (f64) total_diff;
    return usage;
}

int main() {
    u16 core_count = get_core_count();
    CpuStats *prev_stats = malloc(sizeof(CpuStats) * core_count);
    CpuStats *current_stats = malloc(sizeof(CpuStats) * core_count);
    get_stats(prev_stats, core_count);
    sleep(1);
    get_stats(current_stats, core_count);
    prev_stats[1] = current_stats[0];

    f64 usage = get_cpu_usage(prev_stats);
    printf("%f\n", usage);
    return 0;
}
