//
// Created by Alan Ćwiek on 8/20/22.
//

#ifndef CPU_USAGE_TRACKER_STATFILE_H
#define CPU_USAGE_TRACKER_STATFILE_H

#include <bits/types/FILE.h>
#include "../common.h"

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

typedef struct Statfile {
    FILE *file;
    char *file_name;
    u16 core_count;

    //padding
    u64 : 48;
} Statfile;

Statfile *statfile_init(char *file_name);

u16 statfile_get_core_count(Statfile *stats);

void statfile_read(Statfile *stats, CpuStats *stat);

void statfile_destroy(Statfile *stats);

#endif //CPU_USAGE_TRACKER_STATFILE_H
