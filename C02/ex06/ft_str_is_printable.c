int     ft_str_is_printable(char *str)
{
    int     x;

    x = 0;
    while(str[x] != '\0')
    {
        if(!(str[x] > 31 && str[x] <= 127))
        {
            return (0);
        }
        x++;
    }

    return (1);
}