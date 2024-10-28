char    *ft_strupcase(char *str)
{
    int     x;

    x = 0;
    while(str[x] != '\0')
    {
        if(str[x] >= 'A' && str[x] <= 'Z')
        {
            str[x] = str[x] + 32;
        }
        x++;
    }

    return (str);
}