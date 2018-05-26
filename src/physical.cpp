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

    if(eof_count != arc)
        return -1;

    return it->first;
}

long Fat::get_first_from_eof(long arc)
{
    long first = -1;
    while(arc != -1){
        first = arc;
        arc = find_previous(first);
    }

    return first;
}

void Fat::swap_blocks(unsigned int block, unsigned int place)
{
    long aux = fstable[place];
    fstable[place] = block;
    fstable[block] = aux;
}

long Fat::get_free()
{
    for(auto it = fstable.begin(); it != fstable.end(); ++it){
        if(it->second == -2){
            return it->first;
        }
    }
    return -1;
}

void Fat::defrag()
{
    std::vector<unsigned int> last_block;
    unsigned int file = 0;

    //Bloco que contem o EOF do A0
    auto last = get_last(file);

    //Cria vector com posição dos EOF para manter a ordem dos arquivos!
    while(last != -1){
        last_block.push_back(last);
        file++;
        last = get_last(file);
    }

    unsigned int count = 2; //Primeiro bloco vai pra posição 2 (0 e 1 reservados)
    for(int i = 0; i < last_block.size(); i++){
        long current = get_first_from_eof(last_block[i]); //Pega primeiro bloco do arquivo 
        while(current != -1){   //Se o arquivo está corrompido, será ignorado
            while(fstable[count] == -3) //Pula os blocos ruins!
                count++;

            if(count == current){ //Se já está no lugar certo, ignora
                count++;
                current = get_next(current);
                continue;
            }

            long free_id = get_free();
            if(free_id < 0) //Se não há blocos livres, não há como desfragmentar
                return;

            long prev_cnt = find_previous(count);
            long prev_mvd = find_previous(current);
            if(get_next(count) == -1){
                auto it = std::find(last_block.begin(), last_block.end(), count);
                *it = free_id;
            }
            fstable[free_id] = fstable[count];
            fstable[count] = -2;
            if(prev_cnt != -1)
                fstable[prev_cnt] = free_id;
            if(get_next(current) == -1){
                auto it = std::find(last_block.begin(), last_block.end(), current);
                *it = count;
            }
            fstable[count] = fstable[current];
            fstable[current] = -2;
            if(prev_mvd != -1)
                fstable[prev_mvd] = count;
            current = get_next(count);
            count++;
        }
    }
}