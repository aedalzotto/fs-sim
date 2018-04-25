#include "cli.h"

FSCli::FSCli()
{
    last_opt = FS_OPT_EXIT;
    last_prog_opt = FS_PROG_BACK;
    fat_loaded = false;
    job_loaded = false;
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
            if(fat_loaded && job_loaded)
                run_program();
            else {
                std::cout << "Files not loaded!" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
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
    std::cout << "FAT file selected: ";
    if(fat_loaded) std::cout << fat_filename;
    else std::cout << "None";
    std::cout << std::endl;
    std::cout << "Process file selected: ";
    if(job_loaded) std::cout << job_filename;
    else std::cout << "None";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Option: ";
    std::cin >> last_opt;
    return last_opt;    
}

void FSCli::run_program()
{
    simulator.load_physical(parser.get_disk(), parser.get_jobs());
    while(program_menu()){
        switch(last_prog_opt){
        case FS_PROG_CACHED:
            //simulator.run(true);
            break;
        case FS_PROG_UNCACHED:
            simulate(false);
            break;
        case FS_PROG_DEFRAG:
            //defrag_memory();
            break;
        case FS_PROG_RELOAD:
            simulator.load_physical(parser.get_disk(), parser.get_jobs());
            break;
        default:
            std::cout << "Invalid option!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        }
    }
}

int FSCli::program_menu()
{
    Terminal::clear();
    std::cout << "FS Simulator Program" << std::endl;
    std::cout << "FAT file selected: " << fat_filename << std::endl;
    std::cout << "Process file selected: " << job_filename << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "0 - Main menu" << std::endl;
    std::cout << "1 - Run cached simulation" << std::endl;
    std::cout << "2 - Run uncached simulation" << std::endl;
    std::cout << "3 - Run defragmentation" << std::endl;
    std::cout << "4 - Reload files to remove modifications" << std::endl;
    std::cout << std::endl;
    std::cout << "Option: ";
    std::cin >> last_prog_opt;
    return last_prog_opt;
}

void FSCli::select_fat()
{
    Terminal::clear();
    std::cout << "FS Simulator FAT File Selection" << std::endl;
    std::cout << "Type full or relative path to \"FAT\":" << std::endl;
    std::cout << "Path: ";
    std::cin >> fat_filename;
    try {
        parser.load_fat(fat_filename);
        fat_loaded = true;
    } catch(const std::runtime_error& ex){
        std::cerr << "Error: " << ex.what();
        fat_loaded = false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));    
}

void FSCli::select_job()
{
    Terminal::clear();
    std::cout << "FS Simulator Process File Selection" << std::endl;
    std::cout << "Type full or relative path to \"processos\":" << std::endl;
    std::cout << "Path: ";
    std::cin >> job_filename;
    try {
        parser.load_job(job_filename);
        job_loaded = true;
    } catch(const std::runtime_error& ex){
        std::cerr << "Error: " << ex.what();
        job_loaded = false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void FSCli::simulate(bool cached)
{
    Terminal::clear();
    //printar lista dos arquivos
    if(cached)
        return;
    else
        simulator.run_uncached();
    //show_files();

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}