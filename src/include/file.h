#ifndef MMALGO_FILE_H
#define MMALGO_FILE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class mem_list {
public:
    mem_list(unsigned int id, unsigned int size);
    unsigned int id;
};


class FSParser {
public:
    FSParser();
    void load_fat(std::string file_name);
    void load_job(std::string file_name);

    unsigned int get_list_number();
    unsigned int get_task_number();
    const std::vector<std::string> explode(const std::string& s, const char& c);

    std::vector<mem_list> fat;
    std::vector<jobs> job;

private:
    
    bool isInteger(const std::string &s);
};



#endif