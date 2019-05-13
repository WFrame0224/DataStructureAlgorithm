#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack_L.c"

int flboncaai(int n)
{
    if (n < 2)
    {
        return n == 0 ? 0 : 1;
    }
    return flboncaai(n - 1) + flboncaai(n - 2);
}

int main(void)
{
    for(int i = 0; i < 12; i++)
    {
        printf("%d ",flboncaai(i));
    }
    
    return 0;
}