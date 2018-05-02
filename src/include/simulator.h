#ifndef FSSIM_SIM_H_
#define FSSIM_SIM_H_

#include <iostream>
#include <algorithm>

#include "physical.h"

class FSSimulator {
public:
    FSSimulator();
    void load_physical(Fat filesystem, std::vector<Job> joblist);
    void run_uncached();
    void run_cached();
    void show_list();
    void defrag();

private:
    Fat filesystem;
    Cache cache;
    std::vector<Job> joblist;
    long long ticks;
};

#endif