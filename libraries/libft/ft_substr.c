//Allocates and returns a substring from the string 's'. 
//The substring begins with the index 'start' and is of maximum size 'len'.

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char		*sub_s;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (!(sub_s = (char*)malloc(sizeof(*sub_s) * len + 1)))
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
