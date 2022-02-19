/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 20:22:55 by lmuzio            #+#    #+#             */
/*   Updated: 2022/02/11 17:25:53 by lmuzio           ###   ########.fr       */
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
		write(2, msg, c);
	}
	exit(1);
}

void	fill_sig(struct sigaction *act, void (*f)(int, siginfo_t *, void *))
{
	if (!act || !f)
		mt_error("Error: Failed to create sigaction");
	act->__sigaction_u.__sa_sigaction = f;
	act->sa_mask = 0;
	act->sa_flags = SA_SIGINFO;
}

void	ft_putnbr(long n)
{
	char	c;

	if (n == 0)
		write(1, "0", 1);
	else if (n < 0)
		n *= -write(1, "-", 1);
	if (n > 0)
	{
		if (n / 10 != 0)
			ft_putnbr(n / 10);
		c = n % 10 + '0';
		write(1, &c, 1);
	}
}
