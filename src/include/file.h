#ifndef FSSIM_FILE_H_
#define FFSIM_FILE_H_

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstring>

#include "physical.h"

class FSParser {
public:
    FSParser();
    void load_fat(std::string file_name);
    void load_job(std::string file_name);

    Fat get_disk();
    std::vector<Job> get_jobs();

private:
    const std::vector<std::string> explode(const std::string& s, const char& c);
    void remove_chars(std::string &from, char *to_remove);

    Fat disk;
    std::vector<Job> jobs;
};

#endif