//
// Created by Alan Ćwiek on 8/18/22.
//

#include "reader.h"
#include <stdio.h>
#include <unistd.h>
#include <bits/types/sig_atomic_t.h>
#include <malloc.h>
#include "common.h"
#include "analyzer.h"

volatile static sig_atomic_t running = FALSE;
static FILE *fp;

/* Core count includes one additional core which is the total of all cores */
static u16 read_core_count() {
    rewind(fp);
    s8 cpu_name[255];
    cpu_name[0] = 'c';

    u16 core_count;
    while (cpu_name[0] == 'c') {
        core_count++;
        fscanf(fp, "%s %*ld %*ld %*ld %*ld %*ld %*ld %*ld %*ld %*ld %*ld", cpu_name);
    }

    return --core_count;
}

static void read_stats(struct CpuStats *stat, u16 core_count) {
    fflush(fp);
    rewind(fp);
    s64 user, nice, system, idle;
    for (int i = 0; i < core_count; ++i) {
        struct CpuStats *current = &stat[i];
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
//        analyzer_set_core_count(core_count);

        struct CpuStats *stats = malloc(sizeof(struct CpuStats) * core_count);

        while (running) {
            read_stats(stats, core_count);
            //passing only total usage for now
            analyzer_add_data(stats);

            sleep(1);
        }
        free(stats);
    }
    reader_destroy();
}

void reader_destroy() {
    running = FALSE;
    if (fp != NULL) fclose(fp);
}
