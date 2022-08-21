//
// Created by Alan Ćwiek on 8/19/22.
//

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include "threads/analyzer.h"
#include "threads/printer.h"
#include "statfile.h"
#include "threads/thread.h"

void terminate(int signum) {
    thread_stop(reader_get_thread());
    thread_stop(analyzer_get_thread());
    thread_stop(printer_get_thread());
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

    printer_init(core_count);
    analyzer_init(core_count);
    reader_init(statfile);

    thread_join(reader_get_thread());
    thread_join(analyzer_get_thread());
    thread_join(printer_get_thread());

    system("clear");
    printf("Program finished!\n");
    return 0;
}
