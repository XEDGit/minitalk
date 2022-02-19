/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:09:56 by lmuzio            #+#    #+#             */
/*   Updated: 2022/02/11 18:52:34 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	multibyte_handler(unsigned char byte)
{
	static char			nbytes = 0;
	static unsigned int	value = 0;
	char				c;

	c = 7;
	if (!nbytes && !value)
		while (((byte) >> c--) % 2)
			nbytes++;
	value += (byte) << ((4 - nbytes--) * 8);
	if (!nbytes && value)
	{
		if (write(1, &value, 4) == -1)
			mt_error("Error: failed to write multibyte character");
		value = 0;
		nbytes = 0;
	}
}

void	output_handler(unsigned char res, pid_t *sender)
{
	if (!res)
		*sender = 0;
	else if (res < 128)
	{
		if (write(1, &res, 1) == -1)
			mt_error("Error: Failed to write character");
	}
	else
		multibyte_handler(res);
}

void	bit_handler(int sig, siginfo_t *info, void *context)
{
	static char				c = 0;
	static unsigned char	res = 0;
	static pid_t			sender = 0;
	char					bit;

	(void) context;
	if (!sender)
		sender = info->si_pid;
	if (sig == 30)
		bit = 0;
	else
		bit = 1;
	res = res << 1;
	res += bit;
	if (c++ == 7)
	{
		output_handler(res, &sender);
		c = 0;
		res = 0;
	}
	usleep(35);
	if (sender && kill(sender, SIGUSR1))
		mt_error("Error: Failed to send answer");
}

int	main(void)
{
	struct sigaction	s;

	fill_sig(&s, &bit_handler);
	if (sigaction(SIGUSR1, &s, 0))
		mt_error("Error: Failed to apply sigaction");
	if (sigaction(SIGUSR2, &s, 0))
		mt_error("Error: Failed to apply sigaction");
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
}
