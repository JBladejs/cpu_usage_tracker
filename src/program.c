//
// Created by Alan Ćwiek on 8/21/22.
//

#include <string.h>
#include "program.h"
#include "threading/logger.h"
#include "threading/thread.h"
#include "threading/thread_manager.h"

/* This flag generates a warning on a valid code */
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"
#endif

void program_setup_signal_handling(void) {
    struct sigaction action;

    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = (__sighandler_t) &program_handle_signal;

    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

void program_handle_signal(void) {
    logger_log("Signal received. Terminating program...");
    program_terminate();
}

void program_terminate(void) {
    thread_manager_destroy_all();
}
