#include "minitalk.h"

void	multibyte_handler(unsigned char byte)
{
	static char			nbytes = 0;
	static unsigned int	value = 0;
	char				c;

	c = 7;
	if (!nbytes)
	{
		if (!value)
			while (((byte) >> c--) % 2)
				nbytes++;
	}
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
	{
		if (write(1, "\\", 1) == -1)
			mt_error("Error: Failed to write ending character");
		*sender = 0;
	}
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
	usleep(30);
	if (sender && kill(sender, SIGUSR1))
		mt_error("Error: Failed to send answer");
}

int	main(int argc, char **argv)
{
	struct sigaction	s;

	fill_sig(&s, &bit_handler);
	if (sigaction(SIGUSR1, &s, 0))
		mt_error("Error: Failed to apply sigaction");
	if (sigaction(SIGUSR2, &s, 0))
		mt_error("Error: Failed to apply sigaction");
	write(1, "PID: ", 5);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
}
