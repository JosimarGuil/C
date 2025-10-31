#include <unistd.h>


void print_number(int n)
{
    if (n >= 10)
        print_number(n / 10);
    write(1, &"0123456789"[n % 10], 1);
}

int main (void)
{
    int i;

    i = 1;
    while (i <= 100)
    {
        if ((i % 3 == 0) && (i % 5 == 0))
            write(1,"fizzbuzz", 4);
        else if (i % 3 == 0)
            write(1,"fizz", 4);
        else if (i % 5 == 0)
            write(1,"bazz", 4);
        else
            print_number(i);
        write(1, "\n", 1);
        i++;
    }
    return (0);
}