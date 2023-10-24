// See https://gcc.gnu.org/onlinedocs/cpp/Swallowing-the-Semicolon.html for more details
// basic example of swallowing the semicolon 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SKIP_SPACES(p, limit)              \
do { char *lim = (limit);                  \
     while (p <= lim) {                    \
       if (*p++ != ' ') {                  \
         p--; printf("%c", *p); break; }}} \
while (0)

int main()
{
    char* a = "one two three";
    printf("%s\n", a);
    while (a <= &a[strlen(a)-1])
    {
      SKIP_SPACES(a, &a[strlen(a)-1]);
      a++;
    }

    return 0;
}