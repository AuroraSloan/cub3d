//Outputs the characher 'c' to the given file descriptor.

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
