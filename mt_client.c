/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_client.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 20:09:44 by lmuzio        #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2023/07/11 22:19:30 by lmuzio        ########   odam.nl         */
=======
/*   Updated: 2023/07/12 00:49:57 by lmuzio        ########   odam.nl         */
>>>>>>> fa41d32 (Simplified)
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	g_answer;

int	ft_atoi(const char *str)
{
	long		res;
	int			min;

	res = 0;
	min = 0;
	if (!*str)
		return (res);
	while (*str == ' ' || *str == '	' || *str == '\t'\
	|| *str == '\n' || *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		min = 1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += *str++ - '0';
	}
	if (min)
		res *= -min;
	return (res);
}

void	getans(int sig)
{
	(void) sig;
	g_answer = 1;
}

int	byte_handler(unsigned char value, pid_t pid)
{
	char		bytesize;
	static int	sig[2] = {
		SIGUSR1,
		SIGUSR2
	};

	bytesize = 8;
	while (bytesize--)
	{
		g_answer = 0;
		if (kill(pid, sig[((value) >> bytesize) & 1]))
			return (1);
		while (1)
		{
			if (g_answer)
				break ;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t				pid;

	if (argc < 3)
		mt_error("Error: Argument count too low\n");
	if (signal(SIGUSR1, getans) == SIG_ERR)
		mt_error("Error: Failed to apply sigaction");
	pid = ft_atoi(argv[1]);
	if (!pid || pid <= 0)
		mt_error("Error: Failed reading PID\n");
	g_answer = 1;
	while (*argv[2])
	{
		if (byte_handler(argv[2][0], pid))
			mt_error("Error: Failed to send signals\n");
		argv[2]++;
	}
}
