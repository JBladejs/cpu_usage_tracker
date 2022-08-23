//
// Created by Alan Ćwiek on 8/19/22.
//

#include <unistd.h>
#include <malloc.h>
#include "reader.h"
#include "analyzer.h"
#include "thread.h"
#include "../helper/usage_calculator.h"
#include "buffer.h"

static struct CpuStats *prevStat = NULL;
static struct Thread *thread = NULL;

static u16 core_count = 1;

static void *analyzer_thread_routine(struct Thread *used_thread) {
    while (thread_is_running(used_thread)) {
        thread_time(used_thread, TRUE);
        if (prevStat != NULL) {
            struct CpuStats *current = thread_read_from_buffer(thread);
            f32 *usage;
            if (current == NULL) {
                break;
            }
            usage = malloc(sizeof (f32) * core_count);
            for (int i = 0; i < core_count; ++i) {
                usage[i] = usage_calculator_get_usage(&prevStat[i], &current[i]);
            }
            thread_write_to_buffer(used_thread, usage);
            free(prevStat);
            free(usage);
            prevStat = current;
        } else {
            prevStat = thread_read_from_buffer(thread);
        }
        sleep(1);
    }
    free(prevStat);
    return NULL;
}

struct Thread *analyzer_get_thread(void) {
    return thread;
}

void analyzer_init(u16 cores, struct Buffer *read_buffer, struct Buffer *write_buffer) {
    core_count = cores;
    thread = thread_create("analyzer", analyzer_thread_routine, read_buffer, write_buffer);
}
