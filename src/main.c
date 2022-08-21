//
// Created by Alan Ćwiek on 8/19/22.
//

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <caca_conio.h>
#include "threads/analyzer.h"
#include "threads/printer.h"
#include "file_io/statfile.h"
#include "threads/watchdog.h"
#include "threads/thread.h"
#include "threads/logger.h"

void terminate(int signum) {
    logger_log("Signal received, terminating program...");
    thread_stop(watchdog_get_thread());
    thread_stop(reader_get_thread());
    thread_stop(analyzer_get_thread());
    thread_stop(printer_get_thread());
    sleep(1);
    thread_stop(logger_get_thread());
}

int main() {
    struct sigaction action;
    memset (&action, 0, sizeof (struct sigaction));
    action.sa_handler = &terminate;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);

    struct Statfile *statfile = statfile_initialize("/proc/stat");
    if (statfile == NULL) {
        //TODO: alert watchdog
        return 1;
    }
    u16 core_count = statfile_get_core_count(statfile);

    logger_init();
    printer_init(core_count);
    analyzer_init(core_count);
    reader_init(statfile);

    struct Thread **threads = malloc(sizeof (struct Thread) * 4);
    threads[0] = reader_get_thread();
    threads[1] = analyzer_get_thread();
    threads[2] = printer_get_thread();
    threads[3] = logger_get_thread();

    watchdog_init(threads, 4);

    thread_join(watchdog_get_thread());
    thread_join(reader_get_thread());
    thread_join(analyzer_get_thread());
    thread_join(printer_get_thread());
    thread_join(logger_get_thread());

    system("clear");
    printf("Program finished!\n");
    return 0;
}
