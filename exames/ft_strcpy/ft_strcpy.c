#include <stdio.h>

char    *ft_strcpy(char *s1, char *s2)
{
    char *dest = s1;
    while (*s2)
        *s1++ = *s2++;
    *s1 = '\0';
    return (dest);
}


int main ()
{
    char *teste1;
    char *teste2="josimar";
    printf("%s", ft_strcpy(teste1, teste2));
}