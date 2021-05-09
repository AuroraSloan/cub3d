//Allocates and reutrns a string representing the integer received as an arguments.

#include "libft.h"

char	*ft_itoa(int n)
{
	char		*str;
	int		len;
	unsigned int	tmp;

	tmp = n < 0 ? -n : n;
	len = n < 0 ? (ft_numlen(tmp, 10) + 1) : ft_numlen(tmp, 10);
	if (!(str = (char*)malloc(sizeof(*str) * len + 1)))
		return (NULL);
	str[len--] = '\0';
	if (n <= 0)
		str[0] = (n == 0) ? '0' : '-';
	while (tmp)
	{
		str[len--] = tmp % 10 + '0';
		tmp /= 10;
	}
	return (str);
}
