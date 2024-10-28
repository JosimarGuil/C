
 char   *ft_strcapitalize(char *str)
 {
        int     x;

        if(str[0] >= 'a' && str[0] <= 'z')
            str[0] -= 32;
        x = 1;
        while(str[x] != '\0')
        {
            if(str[x] >= 'A' && str[x] <= 'Z')
            {
                    if(!(str[x-1] == ' ' || str[x-1] == '+' || str[x-1] == '-'))
                    {
                        str[x] += 32;
                    }
            } 
            else if (str[x] >= 'a' && str[x] <= 'z')
            {       
                    if(str[x-1] == ' ' || str[x-1] == '+' || str[x-1] == '-')
                    {
                        str[x] -= 32;
                    }
            }
            x++;
        }

        return (str);
 }
