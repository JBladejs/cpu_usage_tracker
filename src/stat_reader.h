//
// Created by Alan Ćwiek on 8/20/22.
//

#ifndef CPU_USAGE_TRACKER_STAT_READER_H
#define CPU_USAGE_TRACKER_STAT_READER_H

#include "common.h"

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

struct StatReader;
struct StatReader *stat_reader_create(char *file_name);
u16 stat_reader_get_core_count(struct StatReader *reader);
void stat_reader_read(struct StatReader *reader, struct CpuStats *stat);
void stat_reader_destroy(struct StatReader *reader);

#endif //CPU_USAGE_TRACKER_STAT_READER_H
