//
// Created by Alan Ćwiek on 8/21/22.
//

#include <malloc.h>
#include <time.h>
#include "logfile.h"

struct Logfile *logfile_init(char *file_name) {
    struct Logfile *logfile = malloc(sizeof(struct Logfile));
    logfile->file_name = file_name;
    logfile->file = fopen(file_name, "a+");
    if (logfile->file == NULL) return NULL;
    logfile->time = time(NULL);
    return logfile;
}

void logfile_write(struct Logfile *logfile, char *message) {
    struct tm *time_info = localtime(&logfile->time);
    char time_string[255];
    strftime(time_string, 255, "%T %D", time_info);
    fprintf(logfile->file, "[%s] %s\n",
            time_string, message);
}

void logfile_destroy(struct Logfile *logfile) {
    if (logfile->file != NULL) fclose(logfile->file);
    free(logfile);
}
