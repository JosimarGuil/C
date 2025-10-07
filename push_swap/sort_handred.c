#include <stdlib.h>
#include <unistd.h>
#include "push_swap.h"

/* cria array de ranks (0..n-1) sem alterar a->numbers */
static int *make_ranks(t_stack *a)
{
    int n = a->size;
    int i, j, rank;
    int *ranks = malloc(n * sizeof(int));
    if (!ranks)
        exit(1);

    i = 0;
    while (i < n)
    {
        rank = 0;
        j = 0;
        while (j < n)
        {
            if (a->numbers[j] < a->numbers[i])
                rank++;
            j++;
        }
        ranks[i] = rank;
        i++;
    }
    return ranks;
}

/* rota ranks paralelos (top -> bottom) */
static void rotate_ranks(t_stack *s)
{
    int i, last;
    if (s->size < 2) return;
    last = s->numbers[s->size - 1];
    i = s->size - 1;
    while (i > 0)
    {
        s->numbers[i] = s->numbers[i - 1];
        i--;
    }
    s->numbers[0] = last;
}

/* função principal */
void radix_sort(t_stack *a, t_stack *b)
{
    int *r_arr;
    t_stack *ranks_a;
    t_stack *ranks_b;
    int n, i, max, max_bits, bit;

    if (!a || a->size <= 1)
        return;

    /* construir ranks */
    r_arr = make_ranks(a);
    ranks_a = create_stack(a->capacity);
    ranks_b = create_stack(a->capacity);

    i = 0;
    while (i < a->size)
    {
        push(ranks_a, r_arr[i]);
        i++;
    }
    free(r_arr);

    /* calcular número de bits */
    n = ranks_a->size;
    max = n - 1;
    max_bits = 0;
    while ((max >> max_bits) != 0)
        max_bits++;

    /* radix sort */
    bit = 0;
    while (bit < max_bits)
    {
        int size = a->size;
        int count = 0;
        while (count < size)
        {
            int top_rank = ranks_a->numbers[ranks_a->size - 1];

            if (((top_rank >> bit) & 1) == 0)
            {
                /* move a->b */
                pb(a, b);
                pb(ranks_a, ranks_b); /* sincroniza ranks (sem print extra) */
            }
            else
            {
                ra(a);
                rotate_ranks(ranks_a);
            }
            count++;
        }
        while (!is_empty(ranks_b))
        {
            pa(a, b);
            pa(ranks_a, ranks_b);
        }
        bit++;
    }
    free_stack(ranks_a);
    free_stack(ranks_b);
}
