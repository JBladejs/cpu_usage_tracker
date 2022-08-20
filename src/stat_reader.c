//
// Created by Alan Ćwiek on 8/20/22.
//

#include <bits/types/FILE.h>
#include <malloc.h>
#include "stat_reader.h"

struct StatReader {
    FILE *file;
    u16 core_count;
};

static u16 read_core_count(struct StatReader *reader) {
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

struct StatReader *stat_reader_create(char *file_name) {
    struct StatReader *reader = malloc(sizeof(struct StatReader));
    reader->file = fopen(file_name, "r");
    if (reader->file == NULL) return NULL;

    reader->core_count = read_core_count(reader);
    return reader;
}

u16 stat_reader_get_core_count(struct StatReader *reader) {
    return reader->core_count;
}

void stat_reader_read(struct StatReader *reader, struct CpuStats *stat) {
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

void stat_reader_destroy(struct StatReader *reader) {
    if (reader->file != NULL) fclose(reader->file);
    free(reader);
}
