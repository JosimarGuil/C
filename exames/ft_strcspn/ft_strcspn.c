size_t	ft_strcspn(const char *s, const char *reject)
{
    int i;
    int x =0;
    while (s[x])
    {
        i = 0;
        while(reject[i])
        {
            if (s[x] == reject[i])
                return (x);
            i++;
        }
        x++;
    }
    return (x);
}
OBS: RETORNA O INDICE DO PRIMEIRO CARACTER DE S QUE NAO ESTA EM REJECT E strspn faz o contrario.


char *strpbrk(const char *s1, const char *s2);

char	*ft_strpbrk(const char *s, const char *accept)
{
	size_t i;

	while (*s)
	{
		i = 0;
		while (accept[i])
		{
			if (*s == accept[i])
				return ((char *)s);
			i++;
		}
		s++;
	}
	return (NULL);
}


Funcionamento passo a passo

A função percorre a string s1 caractere por caractere.

Para cada caractere de s1, ela verifica se existe em s2.

Assim que encontra o primeiro caractere comum,
retorna um ponteiro para esse caractere dentro de s1.

Se nenhum caractere coincidir, retorna NULL.