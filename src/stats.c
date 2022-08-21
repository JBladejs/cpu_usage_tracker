//
// Created by Alan Ćwiek on 8/20/22.
//

#include <bits/types/FILE.h>
#include <malloc.h>
#include "stats.h"

struct Stats {
    FILE *file;
    u16 core_count;
};

static u16 read_core_count(struct Stats *reader) {
    rewind(reader->file);
    s8 cpu_name[255];
    cpu_name[0] = 'c';

    u16 core_count;
    while (cpu_name[0] == 'c') {
        core_count++;
        fscanf(reader->file, "%s %*ld %*ld %*ld %*ld %*ld %*ld %*ld %*ld %*ld %*ld", cpu_name);
    }

    return --core_count;
}

struct Stats *stats_initialize(char *file_name) {
    struct Stats *reader = malloc(sizeof(struct Stats));
    reader->file = fopen(file_name, "r");
    if (reader->file == NULL) return NULL;

    reader->core_count = read_core_count(reader);
    return reader;
}

u16 stats_get_core_count(struct Stats *reader) {
    return reader->core_count;
}

void stats_read(struct Stats *reader, struct CpuStats *stat) {
    fflush(reader->file);
    rewind(reader->file);
    s64 user, nice, system, idle;
    for (int i = 0; i < reader->core_count; ++i) {
        struct CpuStats *current = &stat[i];
        fscanf(reader->file, "%*s %ld %ld %ld %ld %ld %ld %ld %ld %*ld %*ld",
               &current->user, &current->nice, &current->system, &current->idle,
               &current->iowait, &current->irq, &current->softirq, &current->steal);
    }
}

void stat_destroy(struct Stats *reader) {
    if (reader->file != NULL) fclose(reader->file);
    free(reader);
}