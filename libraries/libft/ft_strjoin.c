//Allocates and returns a new string, which is the result of the concatenation of 's1' and 's2'.

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int	i;
	int	j;
	int	len;
	char	*join;

	if (!s1 || !s2)
		return ((char*)s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(join = (char *)malloc(sizeof(*join) * len + 1)))
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
