//
// Created by Alan Ćwiek on 8/18/22.
//

#include "reader.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "common.h"

static u8 running = FALSE;
static FILE *fp;

//TODO: move to a different file
static f64 get_cpu_usage(CpuStats *prev, CpuStats *current) {
    u64 prev_idle = prev->idle + prev->iowait;
    u64 idle = current->idle + current->iowait;

    u64 prev_non_idle = prev->user + prev->nice + prev->system + prev->irq + prev->softirq + prev->steal;
    u64 non_idle = current->user + current->nice + current->system + current->irq + current->softirq + current->steal;

    u64 prev_total = prev_idle + prev_non_idle;
    u64 total = idle + non_idle;

    u64 total_diff = total - prev_total;
    u64 idle_diff = idle - prev_idle;

    if (total_diff == 0) return 0.0f;
    f64 usage = ((f64) (total_diff - idle_diff) / (f64) total_diff) * 100.0f;

    return usage;
}

/* Core count includes one additional core which is the total of all cores */
static u16 read_core_count() {
    s8 cpu_name[255];
    cpu_name[0] = 'c';

    u16 core_count;
    while (cpu_name[0] == 'c') {
        core_count++;
        fscanf(fp, "%s %*ld %*ld %*ld %*ld %*ld %*ld %*ld %*ld %*ld %*ld", cpu_name);
    }

    return --core_count;
}

static void read_stats(CpuStats *stat, u16 core_count) {
    s64 user, nice, system, idle;
    for (int i = 0; i < core_count; ++i) {
        CpuStats *current = &stat[i];
        fscanf(fp, "%*s %ld %ld %ld %ld %ld %ld %ld %ld %*ld %*ld",
               &current->user, &current->nice, &current->system, &current->idle,
               &current->iowait, &current->irq, &current->softirq, &current->steal);
    }
}

void *reader_init(void *arg) {
    running = TRUE;
    fp = fopen("/proc/stat", "r");

    if (fp == NULL) {
        //TODO: alert watchdog
        reader_destroy();
    } else {
        u16 core_count = read_core_count();

        CpuStats *prev_stats = malloc(sizeof(CpuStats) * core_count);
        CpuStats *current_stats = malloc(sizeof(CpuStats) * core_count);

        while (running) {
            rewind(fp);
            read_stats(prev_stats, core_count);
            sleep(1);
            rewind(fp);
            fflush(fp);
            read_stats(current_stats, core_count);

            system("clear");
            for (int i = 0; i < core_count; ++i) {
                printf("CPU %d usage: %f\n", i, get_cpu_usage(&prev_stats[i], &current_stats[i]));
            }
        }
    }
    reader_destroy();
}

void reader_destroy() {
    running = FALSE;
    if (fp != NULL) fclose(fp);
}
