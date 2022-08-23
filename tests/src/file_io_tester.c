//
// Created by Alan Ćwiek on 8/22/22.
//

#include <assert.h>
#include <stddef.h>
#include <malloc.h>
#include <string.h>
#include "../../src/file_io/statfile.h"
#include "../../src/file_io/logfile.h"

static void proc_stat_open_test(void) {
    Statfile *stats = statfile_initialize("/proc/stat");
    assert(stats != NULL);
    statfile_destroy(stats);
}

static void dummy_proc_stat_test(void) {
    CpuStats *cpu_stats;
    Statfile *dummy = statfile_initialize("test_proc_stat");
    assert(statfile_get_core_count(dummy) == 4);
    cpu_stats = malloc(sizeof(CpuStats) * 4);
    statfile_read(dummy, cpu_stats);
    assert(cpu_stats[0].user == 762786);
    assert(cpu_stats[1].nice == 407);
    assert(cpu_stats[2].system == 9850);
    statfile_destroy(dummy);
}

static void logfile_test(void) {
    Logfile *log;
    FILE *file;
    char buffer[255];

    remove("test.log");

    log = logfile_init("test.log");
    logfile_write(log, "test");
    logfile_destroy(log);

    file = fopen("test.log", "r");
    assert(file != NULL);

    fscanf(file, "%*s %*s %s", buffer);
    assert(strcmp(buffer, "test") == 0);

    fclose(file);

    log = logfile_init("test.log");
    logfile_write(log, "test2");
    logfile_destroy(log);

    file = fopen("test.log", "r");
    assert(file != NULL);

    fscanf(file, "%*s %*s %s", buffer);
    assert(strcmp(buffer, "test") == 0);
    fscanf(file, "%*s %*s %s", buffer);
    assert(strcmp(buffer, "test2") == 0);

    fclose(file);

    remove("test.log");
}

int main(void) {
    proc_stat_open_test();
    dummy_proc_stat_test();
    logfile_test();
    return 0;
}
