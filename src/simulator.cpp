#include "simulator.h"

FSSimulator::FSSimulator()
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
    ticks = 0;
    for(auto &it : joblist){
        for(auto& it2 : it.get_arcs()){
            std::cout << "P" << it.get_id() << " precisa blocos de A" << it2;
            long first = filesystem.get_first_block(it2);
            if(first < 0){
                std::cout << "Bloco não encontrado" << std::endl;
                return;
            }
            std::cout << "Gerenciador entrega B" << first << std::endl;
            ticks += 100000;
            while(first != -1){
                first = filesystem.get_next(first);
                std::cout << "Gerenciador entrega B" << first << std::endl;
                ticks += 100000;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Tempo total: " << ticks << std::endl;
}
