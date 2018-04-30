#include "physical.h"
#include <iostream>

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

long Fat::find_previous(long actual)
{
    for(auto it = fstable.begin(); it != fstable.end(); ++it){
        if(it->second == actual){
            return it->first;
        }
    }
    return -1;
}

long Fat::get_first_block(unsigned int arc)
{
    long eof_count = -1;

    auto it = fstable.begin();
    for(; it != fstable.end(); ++it){
        if(it->second == -1){
            eof_count++;
            if(eof_count == arc){
                break;
            }
        }
    }

    if(it == fstable.end())
        return -1;

    unsigned int first;
    long found = it->first;
    do {
        first = found;
        found = find_previous(first);
    } while(found != -1);

    return first;

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