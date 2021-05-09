/*Allocates and reutrns a copy of 's1' with the characters specified in 'set' 
removed from the beginning and the end of the string.*/

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;
	char	*new_str;

	if (!s1 || !set)
		return ((char*)s1);
	start = 0;
	while (ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[end]) && start < end)
		end--;
	if (!(new_str = ft_substr(s1, start, end - start + 1)))
		return (NULL);
	return (new_str);
}
