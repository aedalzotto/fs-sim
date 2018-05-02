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
    return get_first_from_eof(get_last(arc));
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

unsigned int Cache::get_block(unsigned int position)
{
    return cache[position].first;
}

unsigned int Cache::get_size()
{
    return cache.size();
}

long Fat::get_last(unsigned int arc)
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

    return it->first;
}

long get_first_from_eof(unsigned int block)
{
    unsigned int first = -1;
    while(block != -1){
        first = block;
        block = find_previous(first);
    }

    return first;
}