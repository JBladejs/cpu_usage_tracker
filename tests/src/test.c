//
// Created by Alan Ćwiek on 8/22/22.
//

#include <assert.h>
#include "../../src/file_io/statfile.h"

int main(int argc, char *argv[]) {
    struct Statfile *statfile = statfile_initialize("testfile");
    u8 core_count = statfile_get_core_count(statfile);
    assert(core_count == 4);
    statfile_destroy(statfile);
}