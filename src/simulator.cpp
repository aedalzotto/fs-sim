#include "simulator.h"

FSSimulator::FSSimulator() : 
cache(32)
{

}

void FSSimulator::load_physical(Fat filesystem, std::vector<Job> joblist)
{
    this->filesystem = filesystem;
    this->joblist = joblist;
}

void FSSimulator::run_uncached()
{
    std::cout << "Simulação sem cache" << std::endl;
    std::cout << std::endl;
    ticks = 0;
    for(auto &it : joblist){
        for(auto& it2 : it.get_arcs()){
            std::cout << "P" << it.get_id() << " precisa blocos de A" << it2 << std::endl;
            long first = filesystem.get_first_block(it2);
            if(first < 0){
                std::cout << "Bloco não encontrado" << std::endl;
                return;
            }

            do {
                std::cout << "Gerenciador entrega B" << first << std::endl;
                ticks += 100000;
                first = filesystem.get_next(first);
            } while(first != -1);

            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "Tempo total: " << ticks << std::endl;
}

void FSSimulator::run_cached()
{
    cache.clear();
    std::cout << "Simulação com cache" << std::endl;
    std::cout << std::endl;
    ticks = 0;
    for(auto &it : joblist){
        for(auto& it2 : it.get_arcs()){
            std::cout << "P" << it.get_id() << " precisa blocos de A" << it2 << std::endl;
            long first = filesystem.get_first_block(it2);
            if(first < 0){
                std::cout << "Bloco não encontrado" << std::endl;
                return;
            }

            do {
                std::cout << "Gerenciador entrega B" << first;
                if(cache.get(first)){
                    ticks++;
                    std::cout << " da cache";
                } else {
                    ticks += 100000;
                    std::cout << " do disco";
                }
                std::cout << std::endl;
                first = filesystem.get_next(first);
            } while(first != -1);

            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "Tempo total: " << ticks << std::endl;
}


void FSSimulator::show_list()
{
    unsigned int file = 0;
    long first = filesystem.get_first_block(file);
    while(first >= 0){
        std::cout << "A" << file << ": ";
        std::cout << "B" << first;
        first = filesystem.get_next(first);
        while(first != -1) {            
            std::cout << " -> B" << first;
            first = filesystem.get_next(first);
        }
        std::cout << std::endl;
        file++;
        first = filesystem.get_first_block(file);
    }
}