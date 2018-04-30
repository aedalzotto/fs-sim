#ifndef FS_CLI_H
#define FS_CLI_H

#include <iostream>
#include <chrono>
#include <thread>
#include "term_utils.h"
#include "file.h"
#include "simulator.h"

class FSCli {
public:
    FSCli();
    ~FSCli() {}
    int run();

private:
    enum options {
        FS_OPT_EXIT,
        FS_OPT_SEL_FAT,
        FS_OPT_SEL_JOB,
        FS_OPT_RUN_OPT
    };
    enum prog_opts {
        FS_PROG_BACK,
        FS_PROG_CACHED,
        FS_PROG_UNCACHED,
        FS_PROG_DEFRAG,
        FS_PROG_RELOAD,
        FS_PROG_LIST
    };

    FSParser parser;
    FSSimulator simulator;

    std::string fat_filename;
    std::string job_filename;

    int last_opt;
    int last_prog_opt;

    bool fat_loaded;
    bool job_loaded;

    int main_menu();
    void select_fat();
    void select_job();
    void run_program();
    int program_menu();
    void simulate(bool cached);
};

#endif