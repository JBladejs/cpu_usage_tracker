//
// Created by Alan Ćwiek on 8/20/22.
//

#ifndef CPU_USAGE_TRACKER_STATFILE_H
#define CPU_USAGE_TRACKER_STATFILE_H

#include "../common.h"

struct CpuStats {
    u64 user;
    u64 nice;
    u64 system;
    u64 idle;
    u64 iowait;
    u64 irq;
    u64 softirq;
    u64 steal;
};

struct Statfile;
struct Statfile *statfile_initialize(char *file_name);
u16 statfile_get_core_count(struct Statfile *stats);
void statfile_read(struct Statfile *stats, struct CpuStats *stat);
void statfile_destroy(struct Statfile *stats);

#endif //CPU_USAGE_TRACKER_STATFILE_H
