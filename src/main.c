//
// Created by Alan Ćwiek on 8/19/22.
//

#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "program.h"
#include "file_io/statfile.h"
#include "threads/logger.h"
#include "threads/reader.h"
#include "threads/analyzer.h"
#include "threads/printer.h"
#include "threads/watchdog.h"

int main(void) {
    u16 core_count;
    struct Statfile *statfile;
    struct sigaction action;
    struct Buffer *read_data, *analyzed_data;
    struct Thread **threads;
    memset (&action, 0, sizeof (struct sigaction));

    /* This flag generates a warning on a valid code */
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"
#endif

    action.sa_handler = (__sighandler_t) &program_handle_signal;

#ifdef __clang__
#pragma clang diagnostic pop
#endif

    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);

    statfile = statfile_initialize("/proc/stat");
    if (statfile == NULL) {
        logger_log("Error: Could not open /proc/stat. Terminating program...");
        exit(1);
    }
    core_count = statfile_get_core_count(statfile);

    read_data = BUFFER_ARRAY_NEW(struct CpuStats, core_count, 5);
    analyzed_data = BUFFER_ARRAY_NEW(f32, core_count, 10);

    logger_init();
    reader_init(statfile, read_data);
    analyzer_init(core_count, read_data, analyzed_data);
    printer_init(core_count, analyzed_data);

    threads = malloc(sizeof (struct Thread) * 3);
    threads[0] = reader_get_thread();
    threads[1] = analyzer_get_thread();
    threads[2] = printer_get_thread();

    watchdog_init(threads, 3);
    sleep(20);
//    program_terminate();

    buffer_destroy(read_data);
    buffer_destroy(analyzed_data);

    return 0;
}
