/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 19:45:53 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/11 14:44:38 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
#include <stdio.h>


void	mt_error(char *msg);
void	fill_sig(struct sigaction *act, void (*f)(int, siginfo_t *, void *));
void	ft_putnbr(long n);

#endif