#include <unistd.h>

int main(int argc,char **argv) 
{
    if (argc < 2)
    {
        write(1, "\n", 1);
        return (0);
    }
    int i = 0;
    char ch;
    while (argv[1][i] != '\0') 
    {
        
        if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
        {
            ch = 'a';
            while (ch <= argv[1][i])
            {
                write(1,&argv[1][i], 1);
                ch++;
            }
        }
        else if ((argv[1][i] >= 'A' && argv[1][i] <= 'Z'))
        {
            ch = 'A';
            while (ch <= argv[1][i])
            {
                write(1,&argv[1][i], 1);
                ch++;
            }
        }
        else
            write(1,&argv[1][i], 1);
        i++;
    }
    return (0);
}