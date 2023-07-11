/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_client.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 20:09:44 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/11 18:51:08 by lmuzio        ########   odam.nl         */
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

void	getans(int sig, siginfo_t *info, void *context)
{
	g_answer = 1;
	(void) sig;
	(void) info;
	(void) context;
}

int	byte_handler(unsigned char value, pid_t pid)
{
	char		bytesize;
	int			bit;
	static int	sig[2] = {
		SIGUSR1,
		SIGUSR2
	};

	bytesize = 8;
	while (bytesize--)
	{
		g_answer = 0;
		bit = ((value) >> bytesize) & 1;
		if (kill(pid, sig[bit]))
			return (1);
		while (!g_answer)
			pause();
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	s;

	if (argc < 3)
		mt_error("Error: Argument count too low\n");
	ft_putnbr(getpid());
	fill_sig(&s, &getans);
	if (sigaction(SIGUSR1, &s, 0))
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
	if (byte_handler(0, pid))
		mt_error("Error: Failed to send End of communication\n");
}
