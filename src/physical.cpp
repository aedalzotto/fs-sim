#include "physical.h"
#include <iostream>
#include <algorithm>

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

Cache::Cache(unsigned int maxSize){
    this->maxSize = maxSize;
}

void Cache::add(unsigned int id)
{
    if(cache.size() == maxSize){
        auto max = cache.begin();
        for(auto it = max; it != cache.end(); ++it){
            if(it->second > max->second){
                max = it;
            }
        }
        cache.erase(max);
    }
 
    cache.emplace_back(id, 0);
}

void Cache::clear()
{
    cache.clear();
}

bool Cache::get(unsigned int id)
{   
    bool found = false;
    for(auto &it : cache){
        it.second++;
        if(it.first == id){
            found = true;
            it.second = 0;
        }
    }
    if(!found) add(id);
    return found;
}


