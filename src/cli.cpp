#include "cli.h"

FSCli::FSCli()
{
    last_opt = FS_OPT_EXIT;
}

int FSCli::run()
{
    while(main_menu()){
        switch(last_opt){
        case FS_OPT_SEL_FAT:
            select_fat();
            break;
        case FS_OPT_SEL_JOB:
            select_job();
            break;
        case FS_OPT_RUN_OPT:
            break;
        case 42:
            std::cout << "You found the answer!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        default:
            std::cout << "Invalid option!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        }
    }
    return 0;
}

int FSCli::main_menu()
{
    Terminal::clear();
    std::cout << "FS Simulator" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "0 - Exit" << std::endl;
    std::cout << "1 - Select FAT file" << std::endl;
    std::cout << "2 - Select proccess list file" << std::endl;
    std::cout << "3 - Run program for selected files" << std::endl;
    std::cout << std::endl;
    std::cout << "FAT file selected: " << "None" << std::endl; //Alterar com nome do arquivo
    std::cout << "Process file selected: " << "None" << std::endl; //Alterar com nome do arquivo
    std::cout << std::endl;
    std::cout << "Option: ";
    int selection;
    std::cin >> selection;
    last_opt = selection;
    return selection;
}

void FSCli::select_fat()
{

}

void FSCli::select_job()
{

}