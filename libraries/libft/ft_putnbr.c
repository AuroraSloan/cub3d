#include "libft.h"

size_t	ft_putnbr(long long n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		ft_putchar_fd('-', 1);
	}
	i = ft_numlen(n, 10);
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar_fd(n % 10 + '0', 1);
	return (i);
}
