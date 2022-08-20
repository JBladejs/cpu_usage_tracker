//
// Created by Alan Ćwiek on 8/19/22.
//

#ifndef CPU_USAGE_TRACKER_ANALYZER_H
#define CPU_USAGE_TRACKER_ANALYZER_H

#include "reader.h"

void *analyzer_init(void *arg);
struct Queue *analyzer_get_queue();
void analyzer_add_data(struct CpuStats stat);
void analyzer_set_core_count(u16 value);
void analyzer_destroy();

#endif //CPU_USAGE_TRACKER_ANALYZER_H
