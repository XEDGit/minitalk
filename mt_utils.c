/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/06 20:22:55 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/11 19:16:24 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	mt_error(char *msg)
{
	int	c;

	c = 0;
	if (msg)
	{
		while (msg[c])
			c++;
		if (write(2, msg, c) == -1)
			mt_error("Error writing to stdout\n");
	}
	exit(1);
}

void	fill_sig(struct sigaction *act, void (*f)(int, siginfo_t *, void *))
{
	if (!act || !f)
		mt_error("Error: Failed to create sigaction");
	act->sa_sigaction = f;
	act->sa_mask = (__sigset_t){0};
	act->sa_flags = SA_SIGINFO | SA_RESTART;
}

void	ft_putnbr(long n)
{
	char	c;

	if (n == 0)
	{
		if (write(1, "0", 1) == -1)
			mt_error("Error writing to stdout\n");
	}
	else if (n < 0)
		n *= -write(1, "-", 1);
	if (n > 0)
	{
		if (n / 10 != 0)
			ft_putnbr(n / 10);
		c = n % 10 + '0';
		if (write(1, &c, 1) == -1)
			mt_error("Error writing to stdout\n");
	}
}
