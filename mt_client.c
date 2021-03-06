/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:09:44 by lmuzio            #+#    #+#             */
/*   Updated: 2022/02/11 18:58:30 by lmuzio           ###   ########.fr       */
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
	char	bytesize;
	char	bit;

	bytesize = 8;
	while (bytesize--)
	{
		while (!g_answer)
			pause();
		g_answer = 0;
		bit = ((value) >> bytesize) % 2;
		if (!bit)
			if (kill(pid, SIGUSR1))
				return (1);
		if (bit)
			if (kill(pid, SIGUSR2))
				return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	s;

	if (argc < 3)
		mt_error("Error: Argument count too low\n");
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
