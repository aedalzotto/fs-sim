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
    
    std::string buffer;
    std::vector<std::string> buffer_split;
    unsigned int nx_id = 0;

    while(!file.eof()){
        std::getline(file, buffer);

        if(!buffer.size())
            continue;

        buffer_split.clear();
        buffer_split = explode(buffer, 0x09);
        if(buffer_split.size() == 1) buffer_split = explode(buffer, ' ');

        if(buffer_split.size() != 2)
            continue;

        unsigned int id;
        if(isInteger(buffer_split[0]))
            id = std::stoi(buffer_split[0]);
        else
            continue;

        while(id != nx_id){
            if(nx_id >= 2)
                disk.map(nx_id, -3);
            nx_id++;
        }
        nx_id++;
        
        long int buf_next;
        if(!buffer_split[1].compare("EOF")){
            buf_next = -1;
        } else if(!buffer_split[1].compare("FREE")){
            buf_next = -2;
        } else if(!buffer_split[1].compare("BAD")){
            buf_next = -3;
        } else if(isInteger(buffer_split[1])) {
            buf_next = std::stoi(buffer_split[1]);
        } else {
            continue;
        }

        disk.map(id, buf_next);
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

    std::string buffer;
    std::vector<std::string> buffer_split;

    std::vector<std::string> buffer_arcs;
    std::vector<unsigned int> arc_ids;

    while(!file.eof()){
        std::getline(file, buffer);

        if(!buffer.size())
            continue;

        buffer_split.clear();
        remove_chars(buffer, "[],A");
        std::replace(buffer.begin(), buffer.end(), (char)0x09, ' ');

        buffer_split = explode(buffer, ' ');
        if(buffer_split.size() < 2)
            continue;

        unsigned int id;
        if(isInteger(buffer_split[0]))
            id = std::stoi(buffer_split[0]);
        else
            continue;
        
        arc_ids.clear();
        for(int i = 1; i < buffer_split.size(); i++){
            if(isInteger(buffer_split[i]))
                arc_ids.push_back(std::stoi(buffer_split[i]));
            else {
                arc_ids.clear();
                break;
            }
        }

        if(arc_ids.empty())
            continue;

        jobs.push_back(Job(id, arc_ids));

    }

    buffer_split.clear();
    buffer.clear();
    buffer_arcs.clear();
    arc_ids.clear();
    file.close();
}

bool FSParser::isInteger(const std::string &s)
{
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

    char * p ;
    strtol(s.c_str(), &p, 10) ;

    return (*p == 0);
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