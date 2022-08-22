//
// Created by Alan Ćwiek on 8/18/22.
//

#include "reader.h"
#include <unistd.h>
#include <malloc.h>
#include "thread.h"
#include "buffer.h"

static struct Statfile *stat_reader = NULL;
static struct Thread *thread = NULL;

struct Thread *reader_get_thread() {
    return thread;
}

static void reader_destroy() {
    statfile_destroy(stat_reader);
    stat_reader = NULL;
}

static void *reader_thread_routine(struct Thread *used_thread) {
    u16 core_count = statfile_get_core_count(stat_reader);

    struct CpuStats *stats = malloc(sizeof(struct CpuStats) * core_count);

    while (thread_is_running(used_thread)) {
        thread_time(used_thread, TRUE);
        statfile_read(stat_reader, stats);

        buffer_push(used_thread->buffer, stats);

        sleep(1);
    }

    reader_destroy();
}

void reader_init(struct Statfile *statfile, struct Buffer *buffer) {
    stat_reader = statfile;
    thread = thread_create(reader_thread_routine, buffer);
    thread_run(thread, NULL);
}
