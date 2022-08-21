//
// Created by Alan Ćwiek on 8/21/22.
//

#include "program.h"
#include "threads/logger.h"
#include "threads/thread.h"
#include "threads/watchdog.h"
#include "threads/reader.h"
#include "threads/analyzer.h"
#include "threads/printer.h"

void program_handle_signal(int signum) {
    logger_log("Signal received. Terminating program...");
    program_terminate();
}

void program_terminate() {
    thread_stop(watchdog_get_thread());
    thread_stop(reader_get_thread());
    thread_stop(analyzer_get_thread());
    thread_stop(printer_get_thread());
    thread_stop(logger_get_thread());
}