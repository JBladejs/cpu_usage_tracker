//
// Created by Alan Ćwiek on 8/21/22.
//

#ifndef CPU_USAGE_TRACKER_USAGE_MONITOR_H
#define CPU_USAGE_TRACKER_USAGE_MONITOR_H

#include "common.h"
#include "statfile.h"

f32 usage_calculator_get_usage(struct CpuStats *prev, struct CpuStats *current);

#endif //CPU_USAGE_TRACKER_USAGE_MONITOR_H
