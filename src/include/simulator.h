#ifndef FSSIM_SIM_H_
#define FSSIM_SIM_H_

#include <iostream>

#include "physical.h"

class FSSimulator {
public:
    FSSimulator();
    void load_physical(Fat filesystem, std::vector<Job> joblist);
    void run_uncached();

private:
    Fat filesystem;
    std::vector<Job> joblist;
    long long ticks;
};

#endif