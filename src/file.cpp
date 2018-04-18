#include "file.h"
#include <sstream>

FSParser::FSParser()
{

}

void FSParser::load_fat(std::string file_name)
{
    memory.clear();
    std::fstream file;

    file.open(file_name, std::fstream::in);
    if(!file.is_open())
        throw std::runtime_error("Unable to open list.");

    
    //Evita ler header
    file.ignore ( 102, '2' );

    std::string buffer;
    std::vector<std::string> buffer_split;
    std::vector<unsigned int> inputs;

    while(!file.eof()){
        std::getline(file, buffer);

        if(!buffer.size())
            break;

        buffer_split.clear();
        buffer_split = explode(buffer, '	');

        if(buffer_split.size() != 2){
            file.close();
            throw std::runtime_error("Número de colunas inválido.");
        }

        inputs.clear();
        unsigned int value;
        for(auto& s : buffer_split){
            std::istringstream(s) >> value;
            inputs.push_back(value);    
        }

        if(inputs.size() == 2)
            memory.push_back(mem_list(inputs[0], inputs[1]));

    }
    inputs.clear();
    buffer_split.clear();
    buffer.clear();
    file.close();
}

void FSParser::load_job(std::string file_name)
{
    task.clear();
    std::fstream file;

    file.open(file_name, std::fstream::in);
    if(!file.is_open())
        throw std::runtime_error("Unable to open tasks.");

    std::string buffer;
    std::vector<std::string> buffer_split;
    std::vector<unsigned int> inputs;
    while(!file.eof()){
        std::getline(file, buffer);
        if(!buffer.size())
            break;

        buffer_split.clear();
        buffer_split = explode(buffer, ' ');
        if(buffer_split.size() != 2){
            file.close();
            throw std::runtime_error("Número de colunas inválido.");
        }

        //Evita ler header
        inputs.clear();
        unsigned int value;
        for(auto& s : buffer_split){
            if(isInteger(s)){
                std::istringstream(s) >> value;
                inputs.push_back(value);
            }else{
                inputs.clear();
                break;
            }
        }

        if(inputs.size() == 2)
            task.push_back(jobs(inputs[0], inputs[1]));

    }
    inputs.clear();
    buffer_split.clear();
    buffer.clear();
    file.close();
}

const std::vector<std::string> FSParser::explode(const std::string& s, const char& c)
{
    std::string buff{""};
    std::vector<std::string> v;

    for(auto n:s)
    {
        if(n != c) buff+=n; else
        if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}

mem_list::mem_list(unsigned int id, unsigned int size)
{
    this->id = id;
    
}

jobs::jobs(unsigned int id, unsigned int size)
{
    this->id = id;
    this->size = size;
}

unsigned int mmalgo_parser::get_list_number()
{
    return memory.size();
}
unsigned int mmalgo_parser::get_task_number()
{
    return task.size();
}