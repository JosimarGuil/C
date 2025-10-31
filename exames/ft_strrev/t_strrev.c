char    *ft_strrev(char *str)
{
    char *tmp;
    int len = 0;

    while (*str)
        len++;
    int i =0;
    while(i < (len -1))
    {
        tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
        i++;
    }
    return ();
}