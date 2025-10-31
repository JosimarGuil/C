#include "push_swap.h"

static int prev_overflow(long result, int digit, int s)
{
	if (s == 1 && (result > INT_MAX / 10  || (result == INT_MAX / 10 && digit > 7)))
	{
		return (1);
	}
	else if (s == -1 && (result > -(INT_MIN / 10) || (result == -(INT_MIN / 10) && digit > 8)))
	{
		return (1);
	}
	return (0);
}

int ft_atoi(const char *str, int *error)
{
    if (!str)
        return (0);
    long result;
    int s;

    s = 1;
    result = 0;
    while(*str == ' ' || (*str >= '\t' && *str <= '\r'))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
			s = -1;
        str++;
    }

    while(*str >= '0' && *str <= '9')
    {
		if (prev_overflow(result, (*str - '0'), s))
		{
			*error = 1;
			return 0;
		}
        result = ((result * 10) + (*str - '0'));
        str++; 
    }
    return (s * result);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (*(str + i))
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_size;

	if (!dst || !src)
		return (0);
	src_size = ft_strlen(src);
	if (size == 0)
		return (src_size);
	while (size - 1 > 0 && *src)
	{
		*dst++ = *src++;
		size--;
	}
	*dst = '\0';
	return (src_size);
}

size_t	ft_count_words(const char *str, int c)
{
	size_t	count;
	int		i;

	count = 0;
	i = 0;
	while (*str)
	{
		if (*str != c && i == 0)
		{
			count++;
			i = 1;
		}
		if (*str == c)
			i = 0;
		str++;
	}
	return (count);
}

int	ft_alloc_copy(char **arr, char const *s, char c, size_t number_words)
{
	size_t	i;
	size_t	count_chars;

	i = 0;
	while (i < number_words)
	{
		while (*s == c)
			s++;
		count_chars = 0;
		while (s[count_chars] && s[count_chars] != c)
			count_chars++;
		arr[i] = (char *)malloc((count_chars + 1) * sizeof (char));
		if (!arr[i])
		{	
			while (i > 0)
				free(arr[--i]);
			return (0);
		}
		ft_strlcpy(arr[i], s, count_chars + 1);
		s += count_chars;
		i++;
	}
	arr[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	number_words;

	if (!s || !c)
		return (NULL);
	number_words = ft_count_words(s, c);
	arr = (char **)malloc((number_words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (!ft_alloc_copy(arr, s, c, number_words))
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}

int ft_stsr_equal(const char *s, const char *d)
{
    if (!s || !d)
        return -1;

    while (*s && *d)
    {
        if (*s != *d)
            return 0;
        s++;
        d++;
    }
    return (*s == '\0' && *d == '\0');
}

