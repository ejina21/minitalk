#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void	ft_exit(int a)
{
	if (a == 5)
		write(1, "Error: Wrong PID\n", 17);
	else if (a == 4)
		write(1, "Error: System PID\n", 18);
	else if (a == 3)
		write(1, "Error: write ONLY PID_Server and String_to_pass\n", 48);
	else if (a == 2)
		write(1, "Error: malloc not allocated\n", 28);
	exit(a);
}

int	ft_atoi(const char *str)
{
	int			flag;
	long int	sum;

	flag = 0;
	sum = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			flag = !flag;
	while (*str >= '0' && *str <= '9')
	{
		if (sum >= 922337203685477580 && *str - '0' > 7)
			return (- !flag);
		sum = sum * 10 + *str - '0';
		str++;
	}
	if (flag)
		return (-sum);
	else
		return (sum);
}

int	*convert_bite(char c)
{
	int	*b_arr;
	int	i;

	b_arr = malloc(sizeof(int) * 8);
	if (!b_arr)
		return (0);
	i = 7;
	while (i >= 0)
	{
		b_arr[i] = (int)c % 2;
		c /= 2;
		i--;
	}
	return (b_arr);
}

void	send_char(int *b_arr, int pid)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (b_arr[i] == 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_exit(5);
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_exit(5);
		}
		usleep(120);
	}
	free(b_arr);
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;
	int	*b_arr;

	if (argc != 3)
		ft_exit(3);
	pid = ft_atoi(argv[1]);
	if (pid == 0)
		ft_exit(4);
	i = 0;
	while (argv[2][i])
	{
		b_arr = convert_bite(argv[2][i++]);
		if (!b_arr)
			ft_exit(2);
		send_char(b_arr, pid);
	}
}
