//
// Created by Alan Ćwiek on 8/21/22.
//

#ifndef CPU_USAGE_TRACKER_LOGGER_H
#define CPU_USAGE_TRACKER_LOGGER_H

void logger_init();
void logger_log(char* message);
struct Thread *logger_get_thread();

#endif //CPU_USAGE_TRACKER_LOGGER_H
