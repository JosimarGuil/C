#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

// Estrutura da pilha
typedef struct s_stack
{
    int *numbers;   // array de inteiros (dinâmico)
    int size;       // quantidade de elementos atuais
    int capacity;   // capacidade máxima
}   t_stack;


// Funções básicas
t_stack *create_stack(int capacity);
void    free_stack(t_stack *stack);
int     is_empty(t_stack *stack);
int     is_full(t_stack *stack);
void    push(t_stack *stack, int value);
int     pop(t_stack *stack);
int     peek(t_stack *stack);

// Operações exigidas pelo push_swap
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
int ft_atoi(const char *str, int *error);

// Utilitários
void    print_stack(t_stack *stack, char name);
int ft_strchar(const char *str, char c);
char	**ft_split(char const *s, char c);
int	ft_stsr_equal(const char *s, const char *d);
// Adicione estas declarações
void radix_sort(t_stack *a, t_stack *b);
void sort_stack(t_stack *a, t_stack *b);
#endif
