 #include "push_swap.h"

#include <string.h>
int get_max(t_stack *stack);
int get_min(t_stack *stack);
int get_index(t_stack *stack, int value);
static int is_sorted(t_stack *list);
void sort_three(t_stack *stack_a);
void sort_five(t_stack *a, t_stack *b);

void sort_stack(t_stack *a, t_stack *b)
{
    if (a->size == 2)
        sa(a);
    else if (a->size == 3)
        sort_three(a);
    else if (a->size == 5)
        sort_five(a, b);
    else
        radix_sort(a, b);
}

static int is_sorted(t_stack *list)
{
    if (list->size <= 1)
        return (1);
    int i = list->size - 1;
    while (i >= 0)
    {
        if (list->numbers[i] > list->numbers[i - 1]) 
            return (-1);
        i--;
    }
    return (1);
}

void sort_three(t_stack *a)
{
    int top, mid, bot;

    if (!a || a->size != 3)
        return;

    top = a->numbers[a->size - 1];
    mid = a->numbers[a->size - 2];
    bot = a->numbers[a->size - 3];

    /* Caso 1: top > mid && mid < bot && top < bot  => sa */
    if (top > mid && mid < bot && top < bot)
        sa(a);

    /* Caso 2: top > mid && mid > bot  => sa + rra  */
    else if (top > mid && mid > bot)
    {
        sa(a);
        rra(a);
    }

    /* Caso 3: top > mid && mid < bot && top > bot  => ra */
    else if (top > mid && mid < bot && top > bot)
        ra(a);

    /* Caso 4: top < mid && mid > bot && top < bot  => sa + ra */
    else if (top < mid && mid > bot && top < bot)
    {
        sa(a);
        ra(a);
    }

    /* Caso 5: top < mid && mid > bot && top > bot  => rra */
    else if (top < mid && mid > bot && top > bot)
        rra(a);
}

void sort_five(t_stack *a, t_stack *b)
{
    int min;

    // empurrar o menor número para B
    min = get_min(a);
    while (peek(a) != min)
    {
        if (get_index(a, min) <= a->size / 2)
            ra(a);
        else
            rra(a);
    }
    pb(a, b);

    // empurrar o segundo menor para B
    min = get_min(a);
    while (peek(a) != min)
    {
        if (get_index(a, min) <= a->size / 2)
            ra(a);
        else
            rra(a);
    }
    pb(a, b);

    // agora temos 3 em A → ordenar
    sort_three(a);

    // garantir que B está do maior para o menor (para inserir certo)
    if (b->size >= 2 && b->numbers[b->size - 1] < b->numbers[b->size - 2])
        sb(b);

    // trazer de volta
    pa(a, b);
    pa(a, b);
}

#include <stdlib.h>
#include "push_swap.h"

int get_max(t_stack *stack)
{
    int i;

    if (stack->size == 0)
        return (-1);
    int max = stack->numbers[0];
    i =  1;
    while (i < stack->size)
    {
        if (stack->numbers[i] > max)
            max = stack->numbers[i];
        i++;
    }
    return (max);
}

int get_min(t_stack *stack)
{
    int i;
    if (stack->size == 0)
        return (-1);
    int min = stack->numbers[0];
    i = 1;
    while (i < stack->size)
    {
        if (stack->numbers[i] < min)
            min = stack->numbers[i];
        i++;
    }
    return (min);
}

int get_index(t_stack *stack, int value)
{
    int i;

    i = stack->size - 1;
    while (i >= 0) 
    {
        if (stack->numbers[i] == value)
            return (stack->size - 1 - i);
        i--;
    }
    return (-1);
}