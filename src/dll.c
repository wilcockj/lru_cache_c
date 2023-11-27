#include "dll.h"

dll create_dll(){
    dll new_dll;
    new_dll.head = NULL;
    new_dll.tail = NULL;
    new_dll.length = 0;
    return new_dll;
}
