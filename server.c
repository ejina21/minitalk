#include "header.h"

t_serv	g_byte;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
}

void	convert_to_string(int a)
{
	char	sum;
	char	sum_full;
	int		k;

	(void)a;
	sum_full = 0;
	while (++g_byte.i < 8)
	{
		if (g_byte.b_char[g_byte.i] == 1)
		{
			k = g_byte.i;
			sum = 1;
			while (k)
			{
				sum *= 2;
				k--;
			}
			sum_full += sum;
		}
	}
	ft_putchar(sum_full);
	g_byte.i--;
}

void	handler(int sig_id)
{
	if (sig_id == SIGUSR2)
	{
		g_byte.b_char[g_byte.i] = 1;
		g_byte.i--;
	}
	else
	{
		g_byte.b_char[g_byte.i] = 0;
		g_byte.i--;
	}
	if (g_byte.i == -1)
		convert_to_string(1);
}

int	main(void)
{
	g_byte.i = 7;
	write(1, "My PID: ", 8);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
}
