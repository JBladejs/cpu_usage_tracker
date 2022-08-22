//
// Created by Alan Ćwiek on 8/19/22.
//

#include <unistd.h>
#include <malloc.h>
#include "reader.h"
#include "analyzer.h"
#include "printer.h"
#include "../collections/queue.h"
#include "thread.h"
#include "../helper/usage_calculator.h"
#include "buffer.h"

static struct CpuStats *prevStat = NULL;
static struct Queue *queue = NULL;
static struct Thread *thread = NULL;

static u16 core_count = 1;

static void destroy() {
    queue_destroy(queue);
    queue = NULL;
}

static void *analyzer_thread_routine(struct Thread *used_thread) {
    queue = queue_create(255, sizeof(struct CpuStats) * core_count);
    while (thread_is_running(used_thread)) {
        thread_time(used_thread, TRUE);
        if (prevStat != NULL) {
            struct CpuStats *current = buffer_pop(used_thread->buffer);
            f32 *usage = malloc(sizeof (f32) * core_count);
            for (int i = 0; i < core_count; ++i) {
                usage[i] = usage_calculator_get_usage(&prevStat[i], &current[i]);
            }
            printer_add_data(usage);
            free(prevStat);
            free(usage);
            prevStat = current;
        } else {
            prevStat = buffer_pop(used_thread->buffer);
            printf("Read data!\n");

        }
        sleep(1);
    }
    destroy();
}

struct Thread *analyzer_get_thread() {
    return thread;
}

void analyzer_init(u16 cores, struct Buffer *buffer) {
    core_count = cores;
    thread = thread_create(analyzer_thread_routine, buffer);
    thread_run(thread, NULL);
}
