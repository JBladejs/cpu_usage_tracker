//
// Created by Alan Ćwiek on 8/21/22.
//

#include <unistd.h>
#include "threads/logger.h"
#include "threads/thread.h"
#include "threads/watchdog.h"
#include "threads/reader.h"
#include "threads/analyzer.h"
#include "threads/printer.h"

void program_terminate(int signum) {
    logger_log("Signal received, terminating program...");
    thread_stop(watchdog_get_thread());
    thread_stop(reader_get_thread());
    thread_stop(analyzer_get_thread());
    thread_stop(printer_get_thread());
    sleep(1);
    thread_stop(logger_get_thread());
}