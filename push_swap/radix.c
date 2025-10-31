#include "push_swap.h"
#include <stdlib.h>

/* Comparador para qsort utilizado em normalize */
static int cmp_int(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

/* normalize: mapeia valores para ranks 0..n-1 */
static int *normalize_stack(t_stack *a)
{
    int n = a->size;
    if (n <= 1) return NULL;

    int *arr = malloc(sizeof(int) * n);
    int *copy = malloc(sizeof(int) * n);
    if (!arr || !copy)
    {
        free(arr);
        free(copy);
        write(2, "Error\n", 6);
        exit(1);
    }

    /* Preenche arr com os valores da pilha */
    t_node *cur = a->top;
    for (int i = 0; cur; cur = cur->next, i++)
        arr[i] = cur->value;

    /* Cria uma cópia e ordena */
    for (int i = 0; i < n; i++)
        copy[i] = arr[i];
    qsort(copy, n, sizeof(int), cmp_int);

    /* Mapeia cada valor para seu índice ordenado */
    for (int i = 0; i < n; i++)
    {
        int lo = 0, hi = n - 1;
        while (lo <= hi)
        {
            int mid = (lo + hi) / 2;
            if (copy[mid] == arr[i])
            {
                arr[i] = mid;
                break;
            }
            if (copy[mid] < arr[i])
                lo = mid + 1;
            else
                hi = mid - 1;
        }
    }

    /* Atualiza os valores da pilha com os ranks */
    cur = a->top;
    for (int i = 0; cur; cur = cur->next, i++)
        cur->value = arr[i];

    free(arr);
    return copy; /* Retorna a cópia ordenada */
}


/* number of bits */
static int num_bits(int n)
{
    int bits = 0;
    while ((n >> bits) != 0) bits++;
    if (bits == 0) bits = 1;
    return bits;
}

void sort_large(t_stack *a, t_stack *b)
{
    if (!a || a->size <= 1) return;

    int n = a->size;
    int *rank_to_value = normalize_stack(a); // ranks 0..n-1

    int bits = 0;
    while ((n - 1) >> bits)
        bits++;

    for (int j = 0; j < bits; j++)
    {
        int count = n;
        while (count--)
        {
            int top = peek(a);
            if (((top >> j) & 1) == 0)
                pb(a, b);
            else
                ra(a);
        }
        while (!is_empty(b))
            pa(a, b);
    }

    // Ajuste final para colocar rank 0 no topo
    int min_idx = get_index(a, 0);
    if (min_idx <= a->size / 2)
    {
        while (min_idx--)
            ra(a);
    }
    else
    {
        int r = a->size - min_idx;
        while (r--)
            rra(a);
    }

    free(rank_to_value); // liberamos o array de valores originais
}

