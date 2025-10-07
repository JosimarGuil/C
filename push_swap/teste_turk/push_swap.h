#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_stack
{
    int             nbr;
    int             index;
    int             push_const;
    bool            aboove_median;
    bool            cheapest;
    struct  t_stack *target_node;
    struct  t_stack *next;
    struct  t_stack *prev;
}   t_stack;



# endif