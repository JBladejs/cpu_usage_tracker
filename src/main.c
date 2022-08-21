//
// Created by Alan Ćwiek on 8/19/22.
//

#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "analyzer.h"
#include "printer.h"
#include "statfile.h"
#include "thread.h"

void terminate(int signum) {
    reader_stop();
    analyzer_stop();
    printer_stop();
}

int main() {
    struct sigaction action;
    memset (&action, 0, sizeof (struct sigaction));
    action.sa_handler = &terminate;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);

    struct Statfile *reader = statfile_initialize("/proc/stat");
    if (reader == NULL) {
        //TODO: alert watchdog
        return 1;
    }
    u16 core_count = statfile_get_core_count(reader);

    pthread_t reader_thread;
    pthread_t analyzer_thread;

    printer_init();
    printer_set_core_count(core_count);
    thread_run(printer_get_thread(), NULL);

    analyzer_set_core_count(core_count);
    u8 result = pthread_create(&analyzer_thread, NULL, analyzer_init, NULL);
    if (result != 0) {
        perror("Could not create a thread!");
        return 1;
    }

    reader_set_stat_reader(reader);
    result = pthread_create(&reader_thread, NULL, reader_init, NULL);
    if (result != 0) {
        perror("Could not create a thread!");
        return 1;
    }

    pthread_join(reader_thread, NULL);
    pthread_join(analyzer_thread, NULL);
    thread_join(printer_get_thread());

    system("clear");
    printf("Program finished!\n");
    return 0;
}
