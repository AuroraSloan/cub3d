/*Applies the function 'f' to each character of the string 's' to create a
new string resulting from successive applications of 'f'.*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	char	*ptr;
	int	i;

	i = 0;
	if (!s)
		return ((char*)s);
	if (!(ptr = (char*)malloc(sizeof(*ptr) * ft_strlen(s) + 1)))
		return (NULL);
	while (s[i])
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
