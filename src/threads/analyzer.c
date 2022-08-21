//
// Created by Alan Ćwiek on 8/19/22.
//

#include <unistd.h>
#include <malloc.h>
#include "reader.h"
#include "analyzer.h"
#include "printer.h"
#include "../queue.h"
#include "thread.h"

static struct CpuStats *prevStat = NULL;
static struct Queue *queue = NULL;
static struct Thread *thread = NULL;

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

static void destroy() {
    queue_destroy(queue);
    queue = NULL;
}

static void *analyzer_thread_routine(void *arg) {
    queue = queue_create(255, sizeof(struct CpuStats) * core_count);
    while (thread_is_running(thread)) {
        if (prevStat != NULL) {
            if (queue_is_empty(queue)) continue;
            struct CpuStats *current = queue_dequeue(queue);
            f32 *usage = malloc(sizeof (f32) * core_count);
            for (int i = 0; i < core_count; ++i) {
                usage[i] = get_cpu_usage(&prevStat[i], &current[i]);
            }
            printer_add_data(usage);
            free(prevStat);
            prevStat = current;
        } else {
            prevStat = queue_dequeue(queue);
        }
        sleep(1);
    }
    destroy();
}

void analyzer_add_data(struct CpuStats *stat) {
    queue_enqueue(queue, stat);
}

struct Thread *analyzer_get_thread() {
    return thread;
}

void analyzer_init(u16 cores) {
    core_count = cores;
    thread = thread_create(analyzer_thread_routine);
    thread_run(thread, NULL);
}
