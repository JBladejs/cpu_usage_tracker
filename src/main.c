//
// Created by Alan Ćwiek on 8/19/22.
//

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "program.h"
#include "file_io/statfile.h"
#include "threading/logger.h"
#include "threading/reader.h"
#include "threading/analyzer.h"
#include "threading/printer.h"

int main(void) {
    u16 core_count;
    struct Statfile *statfile;
    struct Buffer *read_data, *analyzed_data;

    program_setup_signal_handling();

    statfile = statfile_initialize("/proc/stat");
    if (statfile == NULL) {
        logger_log("Error: Could not open /proc/stat. Terminating program...");
        exit(1);
    }
    core_count = statfile_get_core_count(statfile);


    read_data = BUFFER_ARRAY_NEW(struct CpuStats, core_count, 5);
    analyzed_data = BUFFER_ARRAY_NEW(f32, core_count, 10);

    logger_init();
    reader_init(statfile, read_data);
    analyzer_init(core_count, read_data, analyzed_data);
    printer_init(core_count, analyzed_data);

    sleep(5);
//    program_handle_signal();

    logger_destroy();
    buffer_destroy(read_data);
    buffer_destroy(analyzed_data);

    return 0;
}
