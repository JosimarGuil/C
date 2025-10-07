#include "push_swap.h"

// Criar pilha
t_stack *create_stack(int capacity)
{
    t_stack *stack = malloc(sizeof(t_stack));
    if (!stack)
        return NULL;
    stack->numbers = malloc(sizeof(int) * capacity);
    if (!stack->numbers)
    {
        free(stack);
        return NULL;
    }
    stack->size = 0;
    stack->capacity = capacity;
    return stack;
}

// ------------------
// Helpers sem print
// ------------------
static void sa_noprint(t_stack *a)
{
    int tmp;

    if (a->size < 2)
        return;
    tmp = a->numbers[a->size - 1];
    a->numbers[a->size - 1] = a->numbers[a->size - 2];
    a->numbers[a->size - 2] = tmp;
}

static void sb_noprint(t_stack *b)
{
    int tmp;

    if (b->size < 2)
        return;
    tmp = b->numbers[b->size - 1];
    b->numbers[b->size - 1] = b->numbers[b->size - 2];
    b->numbers[b->size - 2] = tmp;
}

/* rotate: primeiro elemento vai para o fim */
static void ra_noprint(t_stack *a)
{
    int tmp;
    int i;

    if (a->size < 2)
        return;
    tmp = a->numbers[a->size - 1]; // guarda topo
    i = a->size - 1;
    while (i > 0)
    {
        a->numbers[i] = a->numbers[i - 1]; // shift para cima
        i--;
    }
    a->numbers[0] = tmp; // antigo topo vai para o fundo
}


static void rb_noprint(t_stack *b)
{
    int tmp;
    int i;

    if (b->size < 2)
        return;
    tmp = b->numbers[0];
    i = 0;
    while (i < b->size - 1)
    {
        b->numbers[i] = b->numbers[i + 1];
        i++;
    }
    b->numbers[b->size - 1] = tmp;
}

/* reverse rotate: último elemento vai para o início */
static void rra_noprint(t_stack *a)
{
    int tmp;
    int i;

    if (a->size < 2)
        return;
    tmp = a->numbers[0]; // guarda fundo
    i = 0;
    while (i < a->size - 1)
    {
        a->numbers[i] = a->numbers[i + 1]; // shift para baixo
        i++;
    }
    a->numbers[a->size - 1] = tmp; // antigo fundo vai para o topo
}

static void rrb_noprint(t_stack *b)
{
    int tmp;
    int i;

    if (b->size < 2)
        return;
    tmp = b->numbers[b->size - 1];
    i = b->size - 1;
    while (i > 0)
    {
        b->numbers[i] = b->numbers[i - 1];
        i--;
    }
    b->numbers[0] = tmp;
}

// ------------------
// Funções públicas (com print)
// ------------------
void sa(t_stack *a) { sa_noprint(a); write(1, "sa\n", 3); }
void sb(t_stack *b) { sb_noprint(b); write(1, "sb\n", 3); }
void ss(t_stack *a, t_stack *b) { sa_noprint(a); sb_noprint(b); write(1, "ss\n", 3); }

void pa(t_stack *a, t_stack *b)
{
    if (!is_empty(b))
    {
        push(a, pop(b));
        write(1, "pa\n", 3);
    }
}

void pb(t_stack *a, t_stack *b)
{
    if (!is_empty(a))
    {
        push(b, pop(a));
        write(1, "pb\n", 3);
    }
}

void ra(t_stack *a) { ra_noprint(a); write(1, "ra\n", 3); }
void rb(t_stack *b) { rb_noprint(b); write(1, "rb\n", 3); }
void rr(t_stack *a, t_stack *b) { ra_noprint(a); rb_noprint(b); write(1, "rr\n", 3); }

void rra(t_stack *a) { rra_noprint(a); write(1, "rra\n", 4); }
void rrb(t_stack *b) { rrb_noprint(b); write(1, "rrb\n", 4); }
void rrr(t_stack *a, t_stack *b) { rra_noprint(a); rrb_noprint(b); write(1, "rrr\n", 4); }

// ------------------
// Funções auxiliares
// ------------------
void free_stack(t_stack *stack)
{
    if (stack)
    {
        free(stack->numbers);
        free(stack);
    }
}

int is_empty(t_stack *stack) { return (stack->size == 0); }
int is_full(t_stack *stack) { return (stack->size == stack->capacity); }

void push(t_stack *stack, int value)
{
    if (!is_full(stack))
        stack->numbers[stack->size++] = value;
}

int pop(t_stack *stack)
{
    if (is_empty(stack))
        return -1;
    return stack->numbers[--stack->size];
}

int peek(t_stack *stack)
{
    if (is_empty(stack))
        return -1;
    return stack->numbers[stack->size - 1];
}

// DEBUG: imprimir pilha
void print_stack(t_stack *stack, char name)
{
    int i;

    printf("Stack %c (bottom -> top): ", name);
    i = stack->size - 1;
    while (i >= 0)
    {
        printf("%d ", stack->numbers[i]);
        i--;
    }
    if (stack->size > 0)
        printf(" <- top: %d", stack->numbers[stack->size - 1]);
    printf("\n");
}
