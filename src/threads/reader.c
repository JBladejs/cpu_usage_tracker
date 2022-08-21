//
// Created by Alan Ćwiek on 8/18/22.
//

#include "reader.h"
#include <unistd.h>
#include <malloc.h>
#include "analyzer.h"
#include "thread.h"

static struct Statfile *stat_reader = NULL;
static struct Thread *thread = NULL;

void reader_set_stat_reader(struct Statfile *reader) {
    stat_reader = reader;
}

struct Thread *reader_get_thread() {
    return thread;
}

static void reader_destroy() {
    statfile_destroy(stat_reader);
    stat_reader = NULL;
}

static void *reader_thread_routine(void *arg) {
    u16 core_count = statfile_get_core_count(stat_reader);

    struct CpuStats *stats = malloc(sizeof(struct CpuStats) * core_count);

    while (thread_is_running(thread)) {
        statfile_read(stat_reader, stats);
        analyzer_add_data(stats);
        sleep(1);
    }

    reader_destroy();
}

void reader_init(struct Statfile *statfile) {
    stat_reader = statfile;
    thread = thread_create(reader_thread_routine);
    thread_run(thread, NULL);
}
