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
#include "../usage_calculator.h"

static struct CpuStats *prevStat = NULL;
static struct Queue *queue = NULL;
static struct Thread *thread = NULL;

static u16 core_count = 1;

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
                usage[i] = usage_calculator_get_usage(&prevStat[i], &current[i]);
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
