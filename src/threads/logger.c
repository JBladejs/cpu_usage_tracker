//
// Created by Alan Ćwiek on 8/21/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "logger.h"
#include "../file_io/logfile.h"
#include "thread.h"
#include "../program.h"

static struct Logfile *logfile;
static struct Thread *thread;
static struct Buffer *log_buffer = NULL;

static void *logger_thread_routine(struct Thread *used_thread) {
    logger_log("Program started.");
    while (thread_is_running(used_thread)) {
        char* message = thread_read_from_buffer(used_thread);
        if (message == NULL) break;
        logfile_write(logfile, message);
        free(message);
    }
    logfile_destroy(logfile);
    buffer_destroy(log_buffer);
    return NULL;
}

void logger_init(void) {
    logfile = logfile_init("cpu_usage_tracker.log");
    if (logfile == NULL) {
        perror("Error: could not initialize logfile\n");
        program_terminate();
    }
    log_buffer = BUFFER_NEW(char[255], 20);
    thread = thread_create("logger", logger_thread_routine, log_buffer, NULL);
    thread_run(thread);
}

void logger_log(char *message) {
    buffer_push(log_buffer, message);
}
