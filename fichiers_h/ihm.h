#include<stdlib.h>

#ifndef _IHM_H_
#define _IHM_H_

#ifdef _WIN64
    void clear_Console();
#elif __linux__
    void clear_Console();
#endif

#endif