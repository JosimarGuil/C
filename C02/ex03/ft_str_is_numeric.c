#include <stdio.h>

int     ft_str_is_numeric(char *src)
{
    int x;

    x = 0;
   
    while (src[x] != '\0')
    {
        if(!(src[x] >= '0' && src[x] <= '9'))
        {
            return (0);
        }
        x++;
    }

    return (1);
}