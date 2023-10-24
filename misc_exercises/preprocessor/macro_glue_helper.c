#include <stdio.h>

#define TIME time 
#define min_time 0.01
#define max_time 6.1
#define time_count 11

// tokenization to use macro defined values in macros
#define GLUE_HELPER(x,y) x##_##y
#define GLUE(x,y) GLUE_HELPER(x,y)

#define AVERAGE(x) (((GLUE(max, x)) - (GLUE(min, x))) / (GLUE(x, count)))

int main()
{
    printf("(%0.3f - %0.3f) / %i = %0.3f\n", max_time, min_time, time_count, AVERAGE(TIME));
    return 0;
}
