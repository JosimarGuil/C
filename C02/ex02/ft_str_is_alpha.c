 int    ft_str_is_alpha(char *str)
 {
    int x;

    x = 0;
    while(str[x] != '\0')
    {   
        if(!((str[x] >= 'a' && str[x] <= 'z') || (str[x] >= 'A' && str[x] <= 'Z')))
            return (0);
        x++;
    }

    return (1);
 }