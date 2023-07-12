/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_server.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 20:09:56 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/12 01:06:07 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	bit_handler(int sig, siginfo_t *info, void *context)
{
	static char				c = 0;
	static unsigned char	res = 0;

	(void) context;
	res = (res << 1) + (sig == SIGUSR2);
	if (c++ == 7)
	{
		if (write(1, &res, 1) == -1)
			mt_error("Error writing to stdout");
		c = 0;
		res = 0;
	}
	if (kill(info->si_pid, SIGUSR1))
		mt_error("Error: Failed to send answer\n");
}

int	main(void)
{
	struct sigaction	s;

	s = (struct sigaction){0};
	s.sa_sigaction = bit_handler;
	s.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGUSR1, &s, 0))
		mt_error("Error: Failed to apply sigaction\n");
	if (sigaction(SIGUSR2, &s, 0))
		mt_error("Error: Failed to apply sigaction\n");
	ft_putnbr(getpid());
	if (write(1, "\n", 1) == -1)
		mt_error("Error writing to stdout\n");
	while (1)
		sleep(100);
}
