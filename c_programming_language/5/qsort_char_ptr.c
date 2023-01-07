#include <stdio.h>
#include <string.h>

void print(char* s[], size_t n)
{
    for(int i = 0;  i != n; i++)
        printf("%s\n", s[i]);
    printf("\n");
}

/* quick sort code */
void swap(char* v[], int i, int j)
{
    char* temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort(char* v[], int left, int right)
{
    int i, last;
    void swap(char* v[], int left, int right);

    if(left >= right)
        return ;
    swap(v, left, (left+right)/2);
    last = left;
    for(i = left + 1; i <= right; i++)
        if (strcmp(v[i] , v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last+1, right);
}

int main()
{
    char* s[2] = {"This should be 2", "This should be 1."};
    int n = sizeof(s) / sizeof(s[0]);
    print(s,n);
    qsort(s,0,n-1);
    print(s,n);
    return 0;
}