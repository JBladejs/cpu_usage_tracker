//
// Created by Alan Ćwiek on 8/18/22.
//

#include "reader.h"
#include <unistd.h>
#include <bits/types/sig_atomic_t.h>
#include <malloc.h>
#include "../common.h"
#include "analyzer.h"

volatile static sig_atomic_t running = FALSE;
static struct Statfile *stat_reader = NULL;

void reader_set_stat_reader(struct Statfile *reader) {
    stat_reader = reader;
}

static void reader_destroy() {
    running = FALSE;
    statfile_destroy(stat_reader);
    stat_reader = NULL;
}


void *reader_init(void *arg) {
    running = TRUE;

    u16 core_count = statfile_get_core_count(stat_reader);

    struct CpuStats *stats = malloc(sizeof(struct CpuStats) * core_count);

    while (running) {
        statfile_read(stat_reader, stats);
        analyzer_add_data(stats);
        sleep(1);
    }

    reader_destroy();
}

void reader_stop() {
    running = FALSE;
}