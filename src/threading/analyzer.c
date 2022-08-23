//
// Created by Alan Ćwiek on 8/19/22.
//

#include "main_threads.h"
#include <unistd.h>
#include <malloc.h>
#include <stdbool.h>
#include "thread.h"
#include "../helper/usage_calculator.h"
#include "buffer.h"

static u16 core_count = 1;

static void *analyzer_thread_routine(struct Thread *thread) {
    struct CpuStats *prev_stat = NULL;
    while (thread_is_running(thread)) {
        thread_time(thread, TRUE);
        if (prev_stat != NULL) {
            struct CpuStats *current = thread_read_from_buffer(thread);
            f32 *usage;
            if (current == NULL) {
                break;
            }
            usage = malloc(sizeof(f32) * core_count);
            for (int i = 0; i < core_count; ++i) {
                usage[i] = usage_calculator_get_usage(&prev_stat[i], &current[i]);
            }
            thread_write_to_buffer(thread, usage);
            free(prev_stat);
            free(usage);
            prev_stat = current;
        } else {
            prev_stat = thread_read_from_buffer(thread);
        }
        sleep(1);
    }
    free(prev_stat);
    return NULL;
}

void analyzer_init(u16 cores, struct Buffer *read_buffer, struct Buffer *write_buffer) {
    core_count = cores;
    thread_create("analyzer", analyzer_thread_routine, read_buffer, write_buffer, true, NULL);
}
