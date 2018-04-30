#include "term_utils.h"

/**
 * Code from: http://www.cplusplus.com/articles/4z18T05o/
 */
void Terminal::clear()
{
    if(!cur_term){
        int result;
        setupterm(NULL, STDOUT_FILENO, &result);
        if(result <= 0) 
            return;
    }
    putp(tigetstr("clear"));
}

int Terminal::kbhit()
{
    static const int STDIN = 0;
    static bool initialized = false;

    if(!initialized){
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }
    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}