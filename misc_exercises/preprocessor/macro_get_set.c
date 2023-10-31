// found in https://stackoverflow.com/questions/1358232/why-use-macros-in-c
#include <stdlib.h>

// convenience macros for implementing field setter/getter functions (in c++)
// TODO: think how to use them in c
#ifndef CREATE_GET_SET
#define CREATE_GET_SET(PREFIX, FIELD_NAME,FIELD_DATATYPE) \
    FIELD_DATATYPE PREFIX ## FIELD_NAME;\
    inline FIELD_DATATYPE get ## _ ## FIELD_NAME(void) const\
    { \
        return(PREFIX ## FIELD_NAME); \
    } \
    inline void set ## _ ## FIELD_NAME(FIELD_DATATYPE p) \
    { \
        PREFIX ## FIELD_NAME = p; \
    }
#endif

int main()
{
    return ;
}