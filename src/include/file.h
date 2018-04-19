#ifndef MMALGO_FILE_H
#define MMALGO_FILE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class fat {
public:
    fat(unsigned int id, std::string next);
    unsigned int id;
    std::string next;
};

class job {
public:
    job(unsigned int id, std::string arcs);
    unsigned int id;
    std::string arcs;
};

class FSParser {
public:
    FSParser();
    void load_fat(std::string file_name);
    void load_job(std::string file_name);

    unsigned int get_list_number();
    unsigned int get_task_number();
    const std::vector<std::string> explode(const std::string& s, const char& c);

    std::vector<fat> disk;
    std::vector<job> jobs;

private:
    
    bool isInteger(const std::string &s);
};



#endif