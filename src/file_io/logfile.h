//
// Created by Alan Ćwiek on 8/21/22.
//

#ifndef CPU_USAGE_TRACKER_LOGFILE_H
#define CPU_USAGE_TRACKER_LOGFILE_H

#include <bits/types/FILE.h>
#include <bits/types/time_t.h>
#include "../common.h"

typedef struct Logfile {
    char *file_name;
    FILE *file;
    time_t time;
} Logfile;

Logfile *logfile_init(char *file_name);

void logfile_write(Logfile *logfile, char *message);

void logfile_destroy(Logfile *logfile);


#endif //CPU_USAGE_TRACKER_LOGFILE_H
