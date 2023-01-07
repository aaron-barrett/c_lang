#include <stdio.h>
#include <string.h>

int main()
{
    char s[] = "First String";
    char u[] = "First String";
    char t[] = "Second String";
    int n = 5;
    printf("Before copying %d elements of t = \"%s\" to s = \"%s\".\n", n, t,s);
    printf("s = %s\n",s);
    printf("t = %s\n",t);
    char* l = strncpy(s,t,n);
    printf("After copying %d elements of t = \"%s\" to s = \"%s\".\n", n, t, u);
    printf("s = %s\n",s);
    printf("t = %s\n",t);
    printf("Return pointer is:\n");
    printf("l = %s\n",l);
    printf("\n");

    char ss[] = "First String";
    char uu[] = "First String";
    char tt[] = "Second String";
    printf("Before concat %d elements of t = \"%s\" to s = \"%s\".\n", n, tt,ss);
    printf("s = %s\n",ss);
    printf("t = %s\n",tt);
    l = strncat(ss,tt,n);
    printf("After concat %d elements of t = \"%s\" to s = \"%s\".\n", n, tt, uu);
    printf("s = %s\n",ss);
    printf("t = %s\n",tt);
    printf("Return pointer is:\n");
    printf("l = %s\n",l);
    printf("\n");


    char sss[] = "1534";
    char ttt[] = "3834";
    n = 2;
    printf("cmp %d elements of t = \"%s\" to s = \"%s\".\n", n, ttt,sss);
    printf("s = %s\n",sss);
    printf("t = %s\n",ttt);
    int c = strncmp(sss,ttt,n);
    printf("Return int is %d.\n", c);

    return 0;
}