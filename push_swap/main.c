#include "push_swap.h"

static int is_valid(char **str, int nargs);
static void free_split(char **words);
static void fill_stack(t_stack *stack, char **args, int nargs);
int count_numbers(int argc, char **argv);
static int is_sorted(t_stack *list);

int main(int argc, char **argv)
{
    t_stack *a;
    t_stack *b;
    int total;

    total = count_numbers(argc, argv);
    if (argc < 2)
    {
        write(2, "Error\n", 6);
        return (1);
    }
    else
    {
        if (total <= 0)
        {
            write(2, "Error\n", 6);
            return (1);
        }

        if (!is_valid(argv, argc))
        {
            write(2, "Error\n", 6);
            return (1);
        }

        a = create_stack(total);
        b = create_stack(total);
        if (!a || !b)
        {
            write(2, "Error\n", 6);
            return (1);
        }
        
        fill_stack(a, argv, argc);
        print_stack(a, 'a');
        if (a->size > 1 && is_sorted(a) == -1)
            sort_stack(a, b);
        print_stack(a, 'a');
        free_stack(a);
        free_stack(b);
    }
    return (0);
}

int count_numbers(int argc, char **argv)
{
    int i, j, k;
    int error;
    int total = 0;
    char **words;
    int *seen_numbers = malloc(1000 * sizeof(int)); // Array para números vistos

    if (!seen_numbers)
        return (-1);

    error = 0;
    i = 1;
    while (i < argc)
    {
        words = ft_split(argv[i], ' ');
        if (!words)
        {
            i++;
            continue;
        }

        j = 0;
        while (words[j])
        {
            int current_num = ft_atoi(words[j], &error);
            if (error == 1)
            {
                free(seen_numbers);
                free_split(words);
                return (-1);
            }

            // Verifica duplicados
            k = 0;
            while (k < total)
            {
                if (current_num == seen_numbers[k])
                {
                    free(seen_numbers);
                    free_split(words);
                    return (-1);
                }
                k++;
            }

            // Adiciona aos números vistos
            seen_numbers[total] = current_num;
            total++;
            j++;
        }
        free_split(words); // Libera dentro do loop
        i++;
    }
    free(seen_numbers);
    return total;
}

static int is_valid(char **str, int nargs)
{
    int i;
    int c;

    i = 1;
    while (i < nargs)
    {
        c = 0;
        // Verifica se string é vazia
        if (str[i][0] == '\0')
            return (0);
            
        while (str[i][c] != '\0')
        {
            // Verifica múltiplos sinais
            if ((str[i][c] == '-' || str[i][c] == '+') && 
                (str[i][c + 1] == '-' || str[i][c + 1] == '+'))
            {
                return (0);
            }
            // Verifica caracteres inválidos
            if ((str[i][c] != ' ' && str[i][c] != '-' && str[i][c] != '+')
                && !(str[i][c] >= '0' && str[i][c] <= '9'))
            {
                return (0);
            }
            c++;
        }
        i++;
    }
    return (1);
}

static void free_split(char **words)
{
    int i = 0;
    if (!words)
        return;
    while (words[i])
        free(words[i++]);
    free(words);
}

static void fill_stack(t_stack *stack, char **argv, int argc)
{
    int     i, j;
    char    **words;
    int     value;
    int     error;
    int     *temp_values;
    int     count = 0;
    int     total_values = 1000; // Ajuste conforme necessário

    temp_values = malloc(total_values * sizeof(int));
    if (!temp_values)
        exit(1);

    // Primeiro coleta todos os valores
    i = 1;
    while (i < argc)
    {
        words = ft_split(argv[i], ' ');
        if (!words)
        {
            i++;
            continue;
        }
        
        j = 0;
        while (words[j])
        {
            error = 0;
            value = ft_atoi(words[j], &error);
            if (error)
            {
                free(temp_values);
                free_split(words);
                write(2, "Error\n", 6);
                exit(1);
            }
            temp_values[count++] = value;
            j++;
        }
        free_split(words);
        i++;
    }

    // Agora empurra na ordem inversa para corrigir a orientação LIFO
    i = count - 1;
    while (i >= 0)
    {
        push(stack, temp_values[i]);
        i--;
    }
    
    free(temp_values);
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
