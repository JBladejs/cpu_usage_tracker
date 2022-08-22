//
// Created by Alan Ćwiek on 8/21/22.
//

#include "program.h"
#include "threads/logger.h"
#include "threads/thread.h"

void program_handle_signal(void) {
    logger_log("Signal received. Terminating program...");
    program_terminate();
}

void program_terminate(void) {
    thread_destroy_all();
}
