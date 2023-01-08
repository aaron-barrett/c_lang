#include <stdio.h>
#include <ctype.h>

#define MAXLEN 1000

/* The below functions where reworked with pointers */
int getlines(char* s, int lim);
int atoi(char* s);
void itoa(int n, char* s);
void reverse(char *s);
int strindex(char *s, char* t);
int getop(char* s);

int main()
{
    char s[MAXLEN];
    printf("Enter some string:\n");
    if (getlines(s, MAXLEN) > 0)
        printf("%s\n",s);

    char number[MAXLEN] = "1234";
    printf("%s to int %d\n", number, atoi(number));

    char reverse_this[MAXLEN] = "This!";
    reverse(reverse_this);
    printf("Reversed: %s\n", reverse_this);
    char number_n[MAXLEN];

    int n = -4567;
    itoa(n,number_n);
    printf("%d to string %s.\n", n, number_n);

    char first[MAXLEN] = "First Word";
    char second[MAXLEN] = "Word";
    printf("\"%s\" occurs in \"%s\" at index %d.\n", second, first, strindex(first,second));

    char main_buf[MAXLEN];
    printf("Enter some number:\n");
    char* getop_msg;
    if (getop(main_buf) == 1)
        getop_msg = "(Number)";
    else 
        getop_msg = "(Not Number)";
    printf("%s %s\n",main_buf, getop_msg);
    return 0;
}

int getlines(char* s, int lim)
{
    int c, i;
    i = 0;
    while(i < lim-1 && (c=getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n'){
        *s++ = c;
        ++i;
    }
    *s = '\0';
    return i;
}

int atoi(char* s)
{
    int i, n;
    n = 0;
    while ( *s >= '0' && *s <= '9')
        n = 10 * n + (*s++ - '0');
    return n;
}

void itoa(int n, char* s)
{
    int sign;
    int len = 0;
    if ((sign = n) < 0)
        len++;
        n = -n;
    do {
        *s++ = n % 10 + '0';
        len++;
    } while( (n/= 10) > 0);
    if (sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse(s-len);
}

void reverse(char* s)
{
    char* temp = s;
    char hold = ' ';
    int count = 0;
    int i;
    while (*++temp != '\0')
        count++;
    for(i = 0 ; i < count/2; i++){
        hold = *(s+i);
        *(s+i) = *(s + count - i);
        *(s + count - i) = hold;
    }
    *(s+count+1) = '\0';
}

int strindex(char* s, char* t)
{
    int i, j, k;
    for(i = 0; *(s + i) != '\0'; i++){
        for(j=i, k=0; *(t+k) != '\0' && *(s+j) == *(t+k); j++, k++)
            ;
        if (k > 0 && *(t+k) == '\0')
            return i;
    }
    return -1;

}

int getch(void);
void ungetch(int c);

int getop(char* s)
{
    int i, c;
    i = 0;
    while ((*(s+i) = c = getch()) == ' ' || c == '\t')
        i++;
    *(s+1) = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
        return c;       /* not a number */
    i++;
    if (isdigit(c) || c == '-')     /* collect integer part */
        while (isdigit(*(s+i) = c = getch()))
            i++;
    if (c == '.'){     /* collect fraction part */
        *(s+i) = c;
        i++;
        while (isdigit(*(s+i) = c = getch()))
            i++;
    }
    *(s+i) = '\0';
    if (c != EOF)
        ungetch(c);
    return 1;
}

#define BUFSIZE 100
char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */
int getch(void)     /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back to input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else 
        buf[bufp++] = c;
}