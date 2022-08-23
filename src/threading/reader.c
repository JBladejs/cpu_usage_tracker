//
// Created by Alan Ćwiek on 8/18/22.
//

#include "reader.h"
#include <unistd.h>
#include <malloc.h>
#include <stdbool.h>
#include "thread.h"
#include "buffer.h"

static struct Statfile *stat_reader = NULL;

static void reader_destroy(void) {
    statfile_destroy(stat_reader);
    stat_reader = NULL;
}

static void *reader_thread_routine(struct Thread *thread) {
    u16 core_count = statfile_get_core_count(stat_reader);

    struct CpuStats *stats = malloc(sizeof(struct CpuStats) * core_count);

    while (thread_is_running(thread)) {
        thread_time(thread, TRUE);
        statfile_read(stat_reader, stats);

        thread_write_to_buffer(thread, stats);
        sleep(1);
    }

    free(stats);
    reader_destroy();
    return NULL;
}

void reader_init(struct Statfile *statfile, struct Buffer *buffer) {
    stat_reader = statfile;
    thread_create("reader", reader_thread_routine, NULL, buffer, true);
}
