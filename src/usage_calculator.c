//
// Created by Alan Ćwiek on 8/21/22.
//

#include "usage_calculator.h"

f32 usage_calculator_get_usage(struct CpuStats *prev, struct CpuStats *current) {
    u64 prev_idle = prev->idle + prev->iowait;
    u64 idle = current->idle + current->iowait;

    u64 prev_non_idle = prev->user + prev->nice + prev->system + prev->irq + prev->softirq + prev->steal;
    u64 non_idle = current->user + current->nice + current->system + current->irq + current->softirq + current->steal;

    u64 prev_total = prev_idle + prev_non_idle;
    u64 total = idle + non_idle;

    u64 total_diff = total - prev_total;
    u64 idle_diff = idle - prev_idle;

    if (total_diff == 0) return 0.0f;
    f32 usage = ((f32) (total_diff - idle_diff) / (f32) total_diff) * 100.0f;

    return usage;
}