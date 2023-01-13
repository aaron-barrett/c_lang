#include <stdio.h>

char ret(){
    return 'a';
}

char retch(char c){
    return c;
}

int main()
{
    /*pfa: array[] of pointer to function returning char */
    char (*pfa[])() = {(*ret), (*ret)};
    printf("(%c, %c)\n", (*pfa[0])(), (*pfa[1])());

    /*pfa2: array[] of pointer to function returning char */
    /* Now with argument char */
    char (*pfa2[])(char) = {(*retch), (*retch)};
    printf("(%c, %c)\n", (*pfa2[0])('s'), (*pfa2[1])('s'));

    return 0;
}