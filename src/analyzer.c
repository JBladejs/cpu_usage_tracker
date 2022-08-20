//
// Created by Alan Ćwiek on 8/19/22.
//

#include <unistd.h>
#include <bits/types/sig_atomic_t.h>
#include <malloc.h>
#include "reader.h"
#include "analyzer.h"
#include "printer.h"
#include "queue.h"

static struct CpuStats *prevStat = NULL;
static struct Queue *queue = NULL;

volatile static sig_atomic_t running = FALSE;
static u16 core_count = 1;

static f32 get_cpu_usage(struct CpuStats *prev, struct CpuStats *current) {
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

void *analyzer_init(void *arg) {
    running = TRUE;
    queue = QUEUE_NEW(struct CpuStats, 255);
    while (running) {
        if (prevStat != NULL) {
            struct CpuStats *current = queue_dequeue(queue);
            f32 usage = get_cpu_usage(prevStat, current);
            printer_add_data(usage);
            free(prevStat);
            prevStat = current;
        } else {
            prevStat = queue_dequeue(queue);
        }
        sleep(1);
    }
    analyzer_destroy();
}

void analyzer_destroy() {
    running = FALSE;
    queue_destroy(queue);
    queue = NULL;
}

void analyzer_add_data(struct CpuStats stat) {
    queue_enqueue(queue, &stat);
}

void analyzer_set_core_count(u16 value) {
    core_count = value;
}
