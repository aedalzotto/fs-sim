#ifndef FSSIM_PHYS_H_
#define FSSIM_PHYS_H_

#include <vector>
#include <map>

class Fat {
public:
    Fat();
    void clear();
    void map(unsigned int id, long next);
    long get_first_block(unsigned int block);
    long get_next(unsigned int block);

private:
    std::map<unsigned int, long> fstable;
    long find_previous(long actual);
};

class Job {
public:
    Job(unsigned int id, std::vector<unsigned int> arcs);
    unsigned int get_id();
    std::vector<unsigned int> get_arcs();

private:
    unsigned int id;
    std::vector<unsigned int> arcs;
};

class Cache{
public:
    Cache(unsigned int maxSize);
    bool get(unsigned int id);
    void clear();
    
private:
    std::vector<std::pair<unsigned int, unsigned int> > cache;
    unsigned int maxSize;

    void add(unsigned int block);
};

#endif