#include "file.h"
#include <sstream>

FSParser::FSParser()
{

}

void FSParser::load_fat(std::string file_name)
{
    fat.clear();
    std::fstream file;

    file.open(file_name, std::fstream::in);
    if(!file.is_open())
        throw std::runtime_error("Unable to open list.");
    
    //Evita ler header
    file.ignore ( 102, '2' );

    std::string buffer;
    std::vector<std::string> buffer_split;

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

        
        disk.push_back(fat(buffer_split[0], buffer_split[1]));

    }
    buffer_split.clear();
    buffer.clear();
    file.close();
}

void FSParser::load_job(std::string file_name)
{
    job.clear();
    std::fstream file;

    file.open(file_name, std::fstream::in);
    if(!file.is_open())
        throw std::runtime_error("Unable to open list.");
    
    //Evita ler header
    file.ignore ( 125, '0' );

    std::string buffer;
    std::vector<std::string> buffer_split;

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

        
        jobs.push_back(job(buffer_split[0], buffer_split[1]));

    }
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

fat::fat(unsigned int id, std::string next)
{
    this->id = id;
    this->next = next;
}

job::job(unsigned int id, std::string arcs)
{
    this->id = id;
    this->arcs = arcs;
}

unsigned int FSParser::get_jobs_number()
{
    return jobs.size();
}
unsigned int FSParser::get_disk_size()
{
    return disk.size();
}