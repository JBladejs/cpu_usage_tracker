//
// Created by Alan Ćwiek on 8/19/22.
//

#ifndef CPU_USAGE_TRACKER_ANALYZER_H
#define CPU_USAGE_TRACKER_ANALYZER_H

#include "reader.h"

void analyzer_init(u16 cores);
void analyzer_add_data(struct CpuStats *stat);
struct Thread *analyzer_get_thread();

#endif //CPU_USAGE_TRACKER_ANALYZER_H
