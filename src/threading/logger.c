//
// Created by Alan Ćwiek on 8/21/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "logger.h"
#include "../file_io/logfile.h"
#include "thread.h"
#include "../program.h"

struct Logger {
    struct Logfile *logfile;
    struct Buffer *log_buffer;
    struct Thread* thread;
};

static struct Logger *logger_instance(void) {
    static struct Logger logger = {NULL, NULL, NULL};
    return &logger;
}

static void *logger_thread_routine(struct Thread *used_thread) {
    struct Logger* logger = logger_instance();
    logger_log("Program started.");
    while (thread_is_running(used_thread)) {
        char* message = thread_read_from_buffer(used_thread);
        if (message == NULL) break;
        logfile_write(logger->logfile, message);
        free(message);
    }
    logfile_destroy(logger->logfile);
    buffer_destroy(logger->log_buffer);
    return NULL;
}

void logger_init(void) {
    struct Logger *logger = logger_instance();
    logger->logfile = logfile_init("cpu_usage_tracker.log");
    if (logger->logfile == NULL) {
        perror("Error: could not initialize logfile\n");
        program_terminate();
    }
    logger->log_buffer = BUFFER_NEW(char[255], 20);
    logger->thread = thread_create("logger", logger_thread_routine, logger->log_buffer, NULL, false);
}

void logger_log(char *message) {
    buffer_push(logger_instance()->log_buffer, message);
}

void logger_destroy(void) {
    thread_stop(logger_instance()->thread);
}