#include "push_swap.h"
#include <string.h>


static int is_sorted(t_stack *list);
void sort_three(t_stack *stack_a);
void sort_five(t_stack *a, t_stack *b);
int get_index(t_stack *stack, int value);
int get_min(t_stack *stack);

void sort_stack(t_stack *a, t_stack *b)
{
    if (a->size == 2)
        sa(a);
    else if (a->size == 3)
        sort_three(a);
    else if (a->size == 5)
        sort_five(a, b);
    else
        sort_large(a, b);
}

static int is_sorted(t_stack *list)
{
    t_node *cur;

    if (!list || list->size <= 1)
        return 1;

    cur = list->top;
    while (cur && cur->next)
    {
        if (cur->value > cur->next->value)
            return -1;
        cur = cur->next;
    }
    return 1;
}

void sort_three(t_stack *a)
{
    int top;
    int mid;
    int bot;
    t_node *n;

    if (!a || a->size != 3)
        return;

    /* obter valores top, mid, bot */
    n = a->top;
    top = n->value;
    mid = n->next->value;
    bot = n->next->next->value;

    /* Caso 1: top > mid && mid < bot && top < bot => sa */
    if (top > mid && mid < bot && top < bot)
        sa(a);

    /* Caso 2: top > mid && mid > bot => sa + rra */
    else if (top > mid && mid > bot)
    {
        sa(a);
        rra(a);
    }

    /* Caso 3: top > mid && mid < bot && top > bot => ra */
    else if (top > mid && mid < bot && top > bot)
        ra(a);

    /* Caso 4: top < mid && mid > bot && top < bot => sa + ra */
    else if (top < mid && mid > bot && top < bot)
    {
        sa(a);
        ra(a);
    }

    /* Caso 5: top < mid && mid > bot && top > bot => rra */
    else if (top < mid && mid > bot && top > bot)
        rra(a);
}

void sort_five(t_stack *a, t_stack *b)
{
    int k;
    int min;

    k = 0;
    while (k < 2)
    {
        min = get_min(a);
        if (get_index(a, min) <= a->size / 2)
        {
            while (peek(a) != min)
                ra(a);
        }
        else
        {
            while (peek(a) != min)
                rra(a);
        }
        pb(a, b);
        k++;
    }
    sort_three(a);

    /* Ajuste para pilha ligada — precisamos ver os dois primeiros valores */
    if (b->size == 2 && b->top->value < b->top->next->value)
        sb(b);

    pa(a, b);
    pa(a, b);

    min = get_min(a);
    while (peek(a) != min)
        ra(a);
}

int get_index(t_stack *stack, int value)
{
    t_node *cur;
    int idx;

    if (!stack)
        return -1;
    cur = stack->top;
    idx = 0;
    while (cur)
    {
        if (cur->value == value)
            return idx;
        cur = cur->next;
        idx++;
    }
    return -1;
}

int get_min(t_stack *stack)
{
    t_node *cur;
    int min;

    if (!stack || stack->size == 0)
        return INT_MIN; /* ou outro sentinel se preferires */

    cur = stack->top;
    min = cur->value;
    while (cur)
    {
        if (cur->value < min)
            min = cur->value;
        cur = cur->next;
    }
    return min;
}
