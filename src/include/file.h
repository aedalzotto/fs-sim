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
    unsigned int available;
};

class jobs {
public:
    jobs(unsigned int id, unsigned int size);
    unsigned int id;
    unsigned int size;
};

class mmalgo_parser {
public:
    mmalgo_parser();
    void open_list(std::string file_name);
    void open_task(std::string file_name);

    unsigned int get_list_number();
    unsigned int get_task_number();
    const std::vector<std::string> explode(const std::string& s, const char& c);

    std::vector<mem_list> memory;
    std::vector<jobs> task;

private:
    
    bool isInteger(const std::string &s);
};



#endif