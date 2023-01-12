#include <stdio.h>
#include <stdlib.h>

/* numcmp: compars s1 and s2 numerically */
int numcmp(char* s1, char* s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    printf("atof(%s) = %f\n", s1, v1);
    printf("atof(%s) = %f\n", s2, v2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else 
        return 0;
}

int main()
{
    char s1[] = "String One";
    char s2[] = "String Two";
    printf("numcmp(%s, %s) = %d\n",s1, s2, numcmp(s1,s2));

    char s3[] = "396";
    char s4[] = "269";
    printf("numcmp(%s, %s) = %d\n", s3, s4,numcmp(s3,s4));

    char s5[] = "AZ396String";
    char s6[] = "AZ269String";
    printf("numcmp(%s, %s) = %d\n", s5, s6,numcmp(s5,s6));

    return 0;
}