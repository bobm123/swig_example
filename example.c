/* File : example.c */
 
#include <time.h>
double My_variable = 3.0;

int fact(int n)
{
    if (n <= 1)
        return 1;
    else 
        return n*fact(n-1);
}
 
int my_mod(int x, int y)
{
    return (x%y);
}

#ifdef AVOID_CTIME
char time_str[27];

char *get_time()
{
    time_t ltime;
    time(&ltime);
    ctime_s(time_str, sizeof(time_str), &ltime);
    return time_str;
 }
#else
char *get_time()
{
    time_t ltime;
    time(&ltime);
    return ctime(&ltime);
}
#endif
