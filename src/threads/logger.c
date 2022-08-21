//
// Created by Alan Ćwiek on 8/21/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "logger.h"
#include "../file_io/logfile.h"
#include "../collections/queue.h"
#include "thread.h"
#include "../program.h"

static struct Logfile *logfile;
static struct Queue *log_queue;
static struct Thread *thread;

static void *logger_thread_routine(void *arg) {
    logger_log("Program started.");
    while (thread_is_running(thread)) {
        thread_time(thread, TRUE);
        if (!queue_is_empty(log_queue)) {
            char* message = queue_dequeue(log_queue);
            logfile_write(logfile, message);
            free(message);
        }
    }
    logfile_destroy(logfile);
}

void logger_init() {
    logfile = logfile_init("cpu_usage_tracker.log");
    if (logfile == NULL) {
        perror("Error: could not initialize logfile\n");
        program_terminate(0);
    }
    log_queue = QUEUE_NEW(char[255], 255);
    thread = thread_create(logger_thread_routine);
    thread_run(thread, NULL);
}

void logger_log(char *message) {
    if (logfile == NULL) return;
    queue_enqueue(log_queue, message);
}

struct Thread *logger_get_thread() {
    return thread;
}
