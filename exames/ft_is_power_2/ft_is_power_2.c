int	    is_power_of_2(unsigned int n)
{
    if (n == 1)
        return (1);
    int  i = 1;

    while (i < n)
    {
        if (i == n)
            return (1);
        i *= 2;
    }
    return (0);
}