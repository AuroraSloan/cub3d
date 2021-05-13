#include "libft.h"

size_t	gnl_strlen(char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	gnl_strchr_len(char *s, int c)
{
	size_t	i;

	if (s[0] == (char)c)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (0);
}

char	*gnl_strdup(char *s1)
{
	char	*dst;
	int		i;
	int		j;

	j = 0;
	i = gnl_strlen(s1);
	dst = (char *)malloc(sizeof(*dst) * gnl_strlen(s1) + 1);
	if (!(dst))
		return (NULL);
	while (j < i)
	{
		dst[j] = s1[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*join;

	if (!s1 || !s2)
		return (s1);
	len = gnl_strlen(s1) + gnl_strlen(s2);
	join = (char *)malloc(sizeof(*join) * len + 1);
	if (!(join))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

char	*gnl_substr(char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub_s;

	if (!s)
		return (NULL);
	if (start >= gnl_strlen(s))
		return (gnl_strdup(""));
	sub_s = (char *)malloc(sizeof(*sub_s) * len + 1);
	if (!(sub_s))
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub_s[i] = s[start + i];
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}
