#include <stdio.h>

#define MAXLENGTH 1000

char* strncpy(char* s, char* t, size_t n)
{
    size_t size_sstr = 0;
    char* x = s;
    while(*++x != '\0')
        size_sstr++;
    for(size_t i = 0 ; i < n && i != size_sstr ; i++)
        *(s+i) = *(t+i);
    return s;
}

char* strncat(char* s, char* t, size_t n)
{
    size_t size_sstr = 0;
    char* x = s;
    while(*++s != '\0')
        size_sstr++;
    size_t i = 0;
    for(; i < n ; i++)
        *(s+i) = *(t+i);
    *(s+i) = '\0';
    return x;
}

int strncmp(char* s, char *t, size_t n)
{
    for(int i = 0 ; i < n; i++)
        if (*(s+i) == *(t+i))
            continue;
        else
            return *(s+i) - *(t+i);
    return 0;
}

int main()
{
    char s[MAXLENGTH] = "First String";
    char u[MAXLENGTH] = "First String";
    char t[MAXLENGTH] = "Second String";
    int n = 5;
    printf("Before copying %d elements of t = \"%s\" to s = \"%s\".\n", n, t,s);
    printf("s = %s\n",s);
    printf("t = %s\n",t);
    char* l = strncpy(s,t,n);
    printf("After copying %d elements of t = \"%s\" to s = \"%s\".\n", n, t, u);
    printf("s = %s\n",s);
    printf("t = %s\n",t);
    printf("Return pointer is:\n", l);
    printf("l = %s\n",l);
    printf("\n");

    char ss[MAXLENGTH] = "First String";
    char uu[MAXLENGTH] = "First String";
    char tt[MAXLENGTH] = "Second String";
    printf("Before concat %d elements of t = \"%s\" to s = \"%s\".\n", n, tt,ss);
    printf("s = %s\n",ss);
    printf("t = %s\n",tt);
    l = strncat(ss,tt,n);
    printf("After concat %d elements of t = \"%s\" to s = \"%s\".\n", n, tt, uu);
    printf("s = %s\n",ss);
    printf("t = %s\n",tt);
    printf("Return pointer is:\n", l);
    printf("l = %s\n",l);

    char sss[MAXLENGTH] = "1534";
    char ttt[MAXLENGTH] = "3834";
    n = 2;
    printf("Before cmp %d elements of t = \"%s\" to s = \"%s\".\n", n, ttt,sss);
    printf("s = %s\n",sss);
    printf("t = %s\n",ttt);
    int c = strncmp(sss,ttt,n);
    printf("After cmp %d elements of t = \"%s\" to s = \"%s\".\n", n, ttt, sss);
    printf("s = %s\n",sss);
    printf("t = %s\n",ttt);
    printf("Return int is %d.\n", c);

    return 0;
}