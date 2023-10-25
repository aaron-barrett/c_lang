// See https://gcc.gnu.org/onlinedocs/cpp/Swallowing-the-Semicolon.html for more details
// swallow the semicolon for expression in if-else statement using a macro that defines a warning if an expression returns true

#include <stdio.h>
#include  <stdlib.h>

#define WARN_IF(EXP) \
do { if (EXP) { \
        fprintf(stderr, "Warning: " #EXP "\n"); } } \
while(0)

#define WARN_IF_NO_DO_WHILE(EXP) \
if (EXP) { \
        fprintf(stderr, "Warning: " #EXP "\n"); }

int main()
{
    int x = 0 ; 
    if (x == 0)
        WARN_IF(x == 0);
        // WARN_IF(x == 0) // won't work
    else 
        printf("no\n");

    if (x == 0)
        WARN_IF_NO_DO_WHILE(x == 0)
        // WARN_IF_NO_DO_WHILE(x == 0); // also won't work
    else 
        printf("no\n");

    printf("Regular print\n");
    return 0;
}