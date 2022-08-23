//
// Created by Alan Ćwiek on 8/18/22.
//

#include "main_threads.h"
#include <unistd.h>
#include <malloc.h>
#include <stdbool.h>
#include "thread.h"
#include "buffer.h"

static void *reader_thread_routine(Thread *thread) {
    Statfile *statfile = thread_get_arg(thread);
    u16 core_count = statfile_get_core_count(statfile);

    CpuStats *stats = malloc(sizeof(CpuStats) * core_count);

    while (thread_is_running(thread)) {
        thread_time(thread, TRUE);
        statfile_read(statfile, stats);

        thread_write_to_buffer(thread, stats);
        sleep(1);
    }

    free(stats);
    statfile_destroy(statfile);
    return NULL;
}

void reader_init(Statfile *statfile, Buffer *buffer) {
    thread_init("reader", reader_thread_routine, NULL, buffer, true, statfile);
}
