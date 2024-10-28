int     ft_str_is_lowercase(char *str)
{
    int     x;

    x = 0;
    while(str[x] != '\0')
    {
        if(!(str[x] >= 'a' && str[x] <= 'z'))
        {
            return (0);
        }
        x++;
    }

    return (1);
}