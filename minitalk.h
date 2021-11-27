#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

void	mt_error(char *msg);
void	fill_sig(struct sigaction *act, void (*f)(int, siginfo_t *, void *));
void	ft_putnbr(long n);

#endif