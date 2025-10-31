#include "push_swap.h"

/* Criar pilha */
t_stack *create_stack(int capacity)
{
    t_stack *s = malloc(sizeof(t_stack));
    if (!s) return NULL;
    s->top = NULL;
    s->bottom = NULL;
    s->size = 0;
    s->capacity = capacity;
    return s;
}

/* Helper: criar nó */
static t_node *node_new(int value)
{
    t_node *n = malloc(sizeof(t_node));
    if (!n) return NULL;
    n->value = value;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

/* push para o topo (usado por pa/pb e por algoritmo) */
void push(t_stack *stack, int value)
{
    if (!stack) return;
    if (stack->capacity > 0 && stack->size >= stack->capacity) return;
    t_node *n = node_new(value);
    if (!n) return;
    if (stack->size == 0)
    {
        stack->top = n;
        stack->bottom = n;
    }
    else
    {
        n->next = stack->top;
        stack->top->prev = n;
        stack->top = n;
    }
    stack->size++;
}

/* push para o fundo - usado no fill para preservar a ordem de entrada */
void push_bottom(t_stack *stack, int value)
{
    if (!stack) return;
    if (stack->capacity > 0 && stack->size >= stack->capacity) return;
    t_node *n = node_new(value);
    if (!n) return;
    if (stack->size == 0)
    {
        stack->top = n;
        stack->bottom = n;
    }
    else
    {
        n->prev = stack->bottom;
        stack->bottom->next = n;
        stack->bottom = n;
    }
    stack->size++;
}

/* pop do topo (retorna valor) */
int pop(t_stack *stack)
{
    if (!stack || stack->size == 0) return INT_MIN; /* sinal de vazio */
    t_node *n = stack->top;
    int val = n->value;
    stack->top = n->next;
    if (stack->top)
        stack->top->prev = NULL;
    else
        stack->bottom = NULL;
    free(n);
    stack->size--;
    return val;
}

/* peek topo */
int peek(t_stack *stack)
{
    if (!stack || stack->size == 0) return INT_MIN;
    return stack->top->value;
}

/* is_empty / is_full */
int is_empty(t_stack *stack) { return (stack->size == 0); }
int is_full(t_stack *stack) { return (stack->capacity > 0 && stack->size >= stack->capacity); }

/* free stack (libera todos os nós) */
void free_stack(t_stack *stack)
{
    if (!stack) return;
    t_node *cur = stack->top;
    while (cur)
    {
        t_node *next = cur->next;
        free(cur);
        cur = next;
    }
    free(stack);
}

/* DEBUG: imprime pilha bottom -> top igual ao teu antigo print */
void print_stack(t_stack *stack, char name)
{
    if (!stack)
    {
        printf("Stack %c: (null)\n", name);
        return;
    }
    printf("Stack %c (bottom -> top): ", name);
    /* iterar do bottom para top */
    t_node *cur = stack->bottom;
    while (cur)
    {
        printf("%d ", cur->value);
        cur = cur->prev;
    }
    if (stack->size > 0)
        printf(" <- top: %d", stack->top->value);
    printf("\n");
}

/* ---------------------- Operações públicas (imprimem) ---------------------- */

/* swap top two of a */
void sa(t_stack *a)
{
    if (!a || a->size < 2) return;
    t_node *first = a->top;
    t_node *second = first->next;
    int tmp = first->value;
    first->value = second->value;
    second->value = tmp;
    write(1, "sa\n", 3);
}

void sb(t_stack *b)
{
    if (!b || b->size < 2) return;
    t_node *first = b->top;
    t_node *second = first->next;
    int tmp = first->value;
    first->value = second->value;
    second->value = tmp;
    write(1, "sb\n", 3);
}

void ss(t_stack *a, t_stack *b)
{
    sa(a);
    sb(b);
    /* sa and sb already printed; subject allows "ss" but double printing is OK.
       If you want exactly "ss\n" only, implement without calling sa/sb. */
}

/* pa: pop b -> push a */
void pa(t_stack *a, t_stack *b)
{
    if (!a || !b || is_empty(b)) return;
    int v = pop(b);   /* pop from b */
    push(a, v);       /* push to a */
    write(1, "pa\n", 3);
}

/* pb: pop a -> push b */
void pb(t_stack *a, t_stack *b)
{
    if (!a || !b || is_empty(a)) return;
    int v = pop(a);
    push(b, v);
    write(1, "pb\n", 3);
}

/* rotate: move top -> bottom (ra) */
void ra(t_stack *a)
{
    if (!a || a->size < 2) return;
    /* detach top node and append to bottom */
    t_node *first = a->top;
    a->top = first->next;
    a->top->prev = NULL;
    first->next = NULL;
    first->prev = a->bottom;
    a->bottom->next = first;
    a->bottom = first;
    write(1, "ra\n", 3);
}

/* rotate b */
void rb(t_stack *b)
{
    if (!b || b->size < 2) return;
    t_node *first = b->top;
    b->top = first->next;
    b->top->prev = NULL;
    first->next = NULL;
    first->prev = b->bottom;
    b->bottom->next = first;
    b->bottom = first;
    write(1, "rb\n", 3);
}

/* rr: both */
void rr(t_stack *a, t_stack *b)
{
    if (a && a->size >= 2) { /* inline ra_noprint-like but keep print at end? */
        t_node *first = a->top;
        a->top = first->next;
        a->top->prev = NULL;
        first->next = NULL;
        first->prev = a->bottom;
        a->bottom->next = first;
        a->bottom = first;
    }
    if (b && b->size >= 2) {
        t_node *firstb = b->top;
        b->top = firstb->next;
        b->top->prev = NULL;
        firstb->next = NULL;
        firstb->prev = b->bottom;
        b->bottom->next = firstb;
        b->bottom = firstb;
    }
    write(1, "rr\n", 3);
}

/* reverse rotate: move bottom -> top (rra) */
void rra(t_stack *a)
{
    if (!a || a->size < 2) return;
    t_node *last = a->bottom;
    a->bottom = last->prev;
    a->bottom->next = NULL;
    last->prev = NULL;
    last->next = a->top;
    a->top->prev = last;
    a->top = last;
    write(1, "rra\n", 4);
}

/* rrb */
void rrb(t_stack *b)
{
    if (!b || b->size < 2) return;
    t_node *last = b->bottom;
    b->bottom = last->prev;
    b->bottom->next = NULL;
    last->prev = NULL;
    last->next = b->top;
    b->top->prev = last;
    b->top = last;
    write(1, "rrb\n", 4);
}

/* rrr */
void rrr(t_stack *a, t_stack *b)
{
    if (a && a->size >= 2) {
        t_node *last = a->bottom;
        a->bottom = last->prev;
        a->bottom->next = NULL;
        last->prev = NULL;
        last->next = a->top;
        a->top->prev = last;
        a->top = last;
    }
    if (b && b->size >= 2) {
        t_node *lastb = b->bottom;
        b->bottom = lastb->prev;
        b->bottom->next = NULL;
        lastb->prev = NULL;
        lastb->next = b->top;
        b->top->prev = lastb;
        b->top = lastb;
    }
    write(1, "rrr\n", 4);
}
