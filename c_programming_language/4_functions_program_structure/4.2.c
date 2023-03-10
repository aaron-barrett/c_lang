/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   4.2: Extend atof to handle scientific notation of the form 
*
*   123.456e-6
*   
*   where a floating-point number may be followed by e or E and an optionally signed exponent.   
*   
*   Notes:
*********************************************************************************************************************************************/
#include <ctype.h>
#include <stdio.h>

double atof_(char s[])
{
    double val, power;
    int i, sign;
    for(i = 0; isspace(s[i]); i)
    ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for(power = 1.0; isdigit(s[i]); i++){
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    if (s[i] == 'e' || s[i] == 'E'){
        int exponent, exponent_sign;
        exponent_sign = (s[++i] == '-') ? -1 : 1;
        if (exponent_sign == -1 )
            i++;
        if (isdigit(s[i]))
            exponent = (s[i] - '0');
        while (exponent){
            if (exponent_sign < 0)
                power *= 10.0;
            else 
                power /= 10.0;
            exponent--;
        }
    }
    return sign * val / power;
}

int main()
{
    char number[] = "199.90";
    // char number[] = "123.45e-6";
    // char number[] = "11.23e2";
    double  atof_(char []);
    printf("%s to double is %1.8f.\n", number, atof_(number));
    return 0;
}
