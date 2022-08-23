//
// Created by Alan Ćwiek on 8/20/22.
//

#include <bits/types/FILE.h>
#include <malloc.h>
#include "statfile.h"

struct Statfile {
    FILE *file;
    char *file_name;
    u16 core_count;

    //padding
    u64 : 48;
};

static u16 read_core_count(Statfile *reader) {
    s8 cpu_name[255];
    u16 core_count;
    rewind(reader->file);
    cpu_name[0] = 'c';

    core_count = 0;
    while (cpu_name[0] == 'c') {
        core_count++;
        fscanf(reader->file, "%s %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", cpu_name);
    }

    return --core_count;
}

Statfile *statfile_initialize(char *file_name) {
    Statfile *reader = malloc(sizeof(Statfile));
    reader->file_name = file_name;
    reader->file = fopen(file_name, "r");
    if (reader->file == NULL) return NULL;

    reader->core_count = read_core_count(reader);
    return reader;
}

u16 statfile_get_core_count(Statfile *reader) {
    return reader->core_count;
}

void statfile_read(Statfile *reader, CpuStats *stat) {
    fflush(reader->file);
    rewind(reader->file);
    for (int i = 0; i < reader->core_count; ++i) {
        CpuStats *current = &stat[i];
        fscanf(reader->file, "%*s %ld %ld %ld %ld %ld %ld %ld %ld %*d %*d",
               &current->user, &current->nice, &current->system, &current->idle,
               &current->iowait, &current->irq, &current->softirq, &current->steal);
    }
}

void statfile_destroy(Statfile *reader) {
    if (reader->file != NULL) fclose(reader->file);
    free(reader);
}
