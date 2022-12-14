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

static void *analyzer_thread_routine(Thread *thread) {
    CpuStats *prev_stat = NULL;
    u32 core_count = thread_get_arg(thread).core_count;
    while (thread_is_running(thread)) {
        thread_time(thread, TRUE);
        if (prev_stat != NULL) {
            CpuStats *current = thread_read_from_buffer(thread);
            f32 *usage;
            if (current == NULL) {
                break;
            }
            usage = malloc(sizeof(f32) * core_count);
            for (u32 i = 0; i < core_count; ++i) {
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

void analyzer_init(u16 cores, Buffer *read_buffer, Buffer *write_buffer) {
    ThreadArg arg;
    arg.core_count = cores;
    thread_init("analyzer", analyzer_thread_routine, read_buffer, write_buffer, true, arg);
}
