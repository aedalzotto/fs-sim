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