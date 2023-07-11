/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_server.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 20:09:56 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/11 21:23:25 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	bit_handler(int sig, siginfo_t *info, void *context)
{
	static char				c = 0;
	static unsigned char	res = 0;
	static pid_t			sender = 0;
	char					bit;

	(void) context;
	if (!sender)
		sender = info->si_pid;
	bit = sig == SIGUSR2;
	res = (res << 1) + bit;
	if (c++ == 7)
	{
		if (write(1, &res, 1) == -1)
			mt_error("Error writing to stdout\n");
		c = 0;
		res = 0;
	}
	if (sender && kill(sender, SIGUSR1))
		mt_error("Error: Failed to send answer\n");
	if (!res)
		sender = 0;
}

int	main(void)
{
	struct sigaction	s;

	fill_sig(&s, &bit_handler);
	if (sigaction(SIGUSR1, &s, 0))
		mt_error("Error: Failed to apply sigaction\n");
	if (sigaction(SIGUSR2, &s, 0))
		mt_error("Error: Failed to apply sigaction\n");
	ft_putnbr(getpid());
	if (write(1, "\n", 1) == -1)
		mt_error("Error writing to stdout\n");
	while (1)
		pause();
}
