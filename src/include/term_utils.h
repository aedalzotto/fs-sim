#ifndef TERM_UTILS_H
#define TERM_UTILS_H

#include <unistd.h>
#include <term.h>
#include <cstdio>
#include <sys/ioctl.h>


class Terminal {
public:
    static void clear();
    static int kbhit();
};

#endif