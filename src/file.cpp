#include "file.h"

FSParser::FSParser()
{

}

void FSParser::load_fat(std::string file_name)
{
    disk.clear();
    std::fstream file;

    file.open(file_name, std::fstream::in);
    if(!file.is_open())
        throw std::runtime_error("Unable to open list.");
    
    //Evita ler header
    file.ignore(105);

    std::string buffer;
    std::vector<std::string> buffer_split;
    long int buf_next;

    while(!file.eof()){
        std::getline(file, buffer);
        if(!buffer.size())
            break;

        buffer_split.clear();
        buffer_split = explode(buffer, 0x09);

        if(buffer_split.size() != 2){
            file.close();
            throw std::runtime_error("Número de colunas inválido.");
        }
        
        if(!buffer_split[1].compare("EOF")){
            buf_next = -1;
        } else if(!buffer_split[1].compare("FREE")){
            buf_next = -2;
        } else if(!buffer_split[1].compare("BAD")){
            buf_next = -3;
        } else {
            buf_next = std::stoi(buffer_split[1]);
        }

        disk.map(std::stoi(buffer_split[0]), buf_next);
    }
    
    buffer_split.clear();
    buffer.clear();
    file.close();
}

void FSParser::load_job(std::string file_name)
{
    jobs.clear();
    std::fstream file;

    file.open(file_name, std::fstream::in);
    if(!file.is_open())
        throw std::runtime_error("Unable to open list.");
    
    //Evita ler header
    file.ignore(128);

    std::string buffer;
    std::vector<std::string> buffer_split;

    std::vector<std::string> buffer_arcs;
    std::vector<unsigned int> arc_ids;

    while(!file.eof()){
        std::getline(file, buffer);

        if(!buffer.size())
            break;

        buffer_split.clear();
        buffer_arcs.clear();
        arc_ids.clear();

        buffer_split = explode(buffer, 0x09);

        if(buffer_split.size() != 2){
            file.close();
            throw std::runtime_error("Número de colunas inválido.");
        }

        remove_chars(buffer_split[1], "[],A");
        buffer_arcs = explode(buffer_split[1], ' ');

        for(auto& it : buffer_arcs){
            arc_ids.push_back(std::stoi(it));
        }

        jobs.push_back(Job(std::stoi(buffer_split[0]), arc_ids));

    }

    buffer_split.clear();
    buffer.clear();
    buffer_arcs.clear();
    arc_ids.clear();
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

/**
 * 
 */
void FSParser::remove_chars(std::string &from, char *to_remove)
{
    for(unsigned int i = 0; i < strlen(to_remove); i++){
        from.erase(std::remove(from.begin(), from.end(), to_remove[i]), from.end());
    }
}

std::vector<Job> FSParser::get_jobs()
{
    return jobs;
}

Fat FSParser::get_disk()
{
    return disk;
}