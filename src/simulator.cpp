#include "simulator.h"
#include "term_utils.h"

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
                std::cout << "Bloco não encontrado ou corrompido" << std::endl;
                break;
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
    unsigned int miss = 0;
    unsigned int hit = 0;
    std::vector<unsigned int> block_cached;
    cache.clear();
    std::cout << "Simulação com cache" << std::endl;
    std::cout << std::endl;
    ticks = 0;

    for(auto &it : joblist){
        for(auto& it2 : it.get_arcs()){
            std::cout << "P" << it.get_id() << " precisa blocos de A" << it2 << std::endl;
            long first = filesystem.get_first_block(it2);
            if(first < 0){
                std::cout << "Bloco não encontrado ou corrompido" << std::endl;
                break;
            }

            do {
                std::cout << "Gerenciador entrega B" << first;
                if(cache.get(first)){
                    ticks++;
                    std::cout << " da cache";
                    hit++;
                    if(std::find(block_cached.begin(), block_cached.end(), first) == block_cached.end())
                        block_cached.push_back(first);
                } else {
                    ticks += 100000;
                    std::cout << " do disco";
                    miss++;
                }
                std::cout << std::endl;
                first = filesystem.get_next(first);
            } while(first != -1);

            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "Tempo total: " << ticks << std::endl;
    std::cout << "Quantidade de hit: " << hit << std::endl;
    std::cout << "Quantidade de miss: " << miss << std::endl;

    std::cout << std::endl << "Blocos que foram para a cache:" << std::endl;
    for(auto &it : block_cached)
        std::cout << "B" << it << " ";
    std::cout << std::endl;
    std::cout << std::endl << "Blocos que terminaram na cache:" << std::endl;
    for(unsigned int i = 0; i < cache.get_size(); i++)
        std::cout << "B" << cache.get_block(i) << " ";
    
    std::cout << std::endl;
}

void FSSimulator::run_defrag()
{
    std::cout << "Defrag" << std::endl << std::endl;

    filesystem.defrag();
}

void FSSimulator::show_list()
{
    std::cout << "File list" << std::endl << std::endl;
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