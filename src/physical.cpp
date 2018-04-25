#include "physical.h"

Fat::Fat()
{

}

void Fat::clear()
{
    fstable.clear();
}

void Fat::map(unsigned int id, long next)
{
    fstable[id] = next;
}

long Fat::get_first_block(unsigned int arc)
{
    long eof_count = -1;
    //Problema no iterator de map
    for(auto &it : fstable){
        if(it.second == -1){
            eof_count++;
            if(eof_count == arc)
                return it.first;
        }
    }
    return eof_count;
}

long Fat::get_next(unsigned int block)
{
    return fstable[block];
}

Job::Job(unsigned int id, std::vector<unsigned int> arcs)
{
    this->id = id;
    this->arcs = arcs;
}

unsigned int Job::get_id()
{
    return id;   
}

std::vector<unsigned int> Job::get_arcs()
{
    return arcs;
}