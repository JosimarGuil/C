#include "../includes/pipex.h"

static int count_word(const char *str, char sep)
{
	int total = 0;
	int in_word = 0;

	while (*str)
	{
		if (*str != sep && in_word == 0)
		{
			in_word = 1;
			total++;
		}
		else if (*str == sep)
			in_word = 0;
		str++;
	}
	return (total);
}

static void fill_word(char *dest, char **src, int l)
{
	int c = 0;
	while (**src && c < l)
	{
		dest[c++] = **src;
		(*src)++;
	}
	dest[c] = '\0';
}

static char **fill_words(char *str, char sep, int total_words, char **words)
{
	int i;
	int l;

	i = 0;
	while (i < total_words)
	{
		l = 0;
		while (*str == sep)
			str++;
		while (str[l] && str[l] != sep)
			l++;
		words[i] = malloc(sizeof(char) * (l + 1));
		if (!words[i])
		{
			while (i--)
				free(words[i]);
			free(words);
			return (NULL);
		}
		fill_word(words[i], &str, l);
		i++;
	}
	words[i] = NULL;
	return (words);
}

char **ft_split(char *str, char sep)
{
	int total_words;
	char **words;

	if (!str)
		return (NULL);
	total_words = count_word(str, sep);
	if (total_words == 0)
	{
		words = malloc(sizeof(char *));
		if (!words)
			return (NULL);
		words[0] = NULL;
		return (words);
	}
	words = malloc(sizeof(char *) * (total_words + 1));
	if (!words)
		return (NULL);
	words = fill_words(str, sep, total_words, words);
	if (!words)
		return (NULL);
	return (words);
}

void	ft_free_split(char **arr)
{
	int	i = 0;
	if (!arr)
		return;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
