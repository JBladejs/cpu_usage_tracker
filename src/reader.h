//
// Created by Alan Ćwiek on 8/18/22.
//

#ifndef CPU_USAGE_TRACKER_READER_H
#define CPU_USAGE_TRACKER_READER_H

#include "common.h"
#include "stats.h"

void reader_set_stat_reader(struct Stats *reader);
void *reader_init(void *arg);
void reader_stop();

#endif //CPU_USAGE_TRACKER_READER_H
