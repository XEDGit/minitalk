/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/06 20:22:55 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/12 00:27:29 by lmuzio        ########   odam.nl         */
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
