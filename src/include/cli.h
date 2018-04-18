#ifndef FS_CLI_H
#define FS_CLI_H

#include <iostream>
#include <chrono>
#include <thread>
#include "term_utils.h"

class FSCli {
public:
    FSCli();
    int run();

private:
    enum options {
        FS_OPT_EXIT,
        FS_OPT_SEL_FAT,
        FS_OPT_SEL_JOB,
        FS_OPT_RUN_OPT
    };

    int last_opt;

    int main_menu();
    void select_fat();
    void select_job();
};

#endif