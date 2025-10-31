#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

/* node da lista duplamente ligada */
typedef struct s_node
{
    int             value;
    struct s_node   *prev;
    struct s_node   *next;
}               t_node;

/* estrutura da pilha como lista ligada */
typedef struct s_stack
{
    t_node  *top;      /* topo da pilha (o elemento "top") */
    t_node  *bottom;   /* bottom */
    int     size;
    int     capacity;  /* opcional, mantido para compatibilidade */
}               t_stack;

/* Funções básicas */
t_stack *create_stack(int capacity);
void    free_stack(t_stack *stack);
int     is_empty(t_stack *stack);
int     is_full(t_stack *stack);
void    push(t_stack *stack, int value);         /* push para o topo */
void    push_bottom(t_stack *stack, int value);  /* push para o fundo (só usado no fill) */
int     pop(t_stack *stack);
int     peek(t_stack *stack);

/* Operações do subject */
void    sa(t_stack *a);
void    sb(t_stack *b);
void    ss(t_stack *a, t_stack *b);
void    pa(t_stack *a, t_stack *b);
void    pb(t_stack *a, t_stack *b);
void    ra(t_stack *a);
void    rb(t_stack *b);
void    rr(t_stack *a, t_stack *b);
void    rra(t_stack *a);
void    rrb(t_stack *b);
void    rrr(t_stack *a, t_stack *b);

/* utilitários de parsing / string (mantive teus protótipos) */
int     ft_atoi(const char *str, int *error);
int     ft_strchar(const char *str, char c);
char	**ft_split(char const *s, char c);
int	    ft_stsr_equal(const char *s, const char *d);

/* Funções de ordenação */
void    sort_large(t_stack *a, t_stack *b);
void    sort_stack(t_stack *a, t_stack *b);

/* Helpers usados por sort */
int     get_min(t_stack *stack);
int     get_index(t_stack *stack, int value);
void print_stack(t_stack *stack, char name);
#endif
