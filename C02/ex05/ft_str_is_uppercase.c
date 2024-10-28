int     ft_str_is_uppercase(char *str)
{
    int     x;

    x = 0;
    while(str[x] != '\0')
    {
        if(!(str[x] >= 'A' && str[x] <= 'Z'))
        {
            return (0);
        }
        x++;
    }

    return (1);
}