/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galetha <galetha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:49:59 by galetha           #+#    #+#             */
/*   Updated: 2022/01/20 14:53:48 by galetha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	i;

	i = 0;
	if (s)
	{
		if (fd >= 0)
		{
			while (s[i] != '\0')
			{
				write(fd, &s[i], 1);
				i++;
			}
		}
	}
}

void	ft_putnbr_fd(int n, int fd)
{	
	int		num;
	char	s[10];

	if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	if (n == 0)
		write(1, "0", 1);
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	num = 0;
	while (n > 0)
	{
		s[num] = n % 10 + '0';
		n = n / 10;
		num++;
	}
	num--;
	while (num >= 0)
	{
		write(1, &s[num], 1);
		num--;
	}
}

void	ft_symb(int *symb, int *count)
{
	if ((*symb) != 0)
	{
		write(1, &(*symb), 1);
	}
	else
	{
		write(1, "\n", 1);
	}
	(*count) = 0b10000000;
	(*symb) = 0;
}

void	ft_sig12_handler(int sig, struct __siginfo *ptr, void *lol)
{
	static int		i;
	static int		symb;
	static int		count;

	(void) lol;
	if (count == 0)
		count = 0b10000000;
	if (sig == SIGUSR1)
	{
		symb += count;
		count /= 2;
		i++;
	}
	if (sig == SIGUSR2)
	{
		count /= 2;
		i++;
	}
	if (i == 8)
	{
		ft_symb(&symb, &count);
		i = 0;
	}
	kill(ptr->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	st;
	int					pid;

	ft_putnbr_fd(pid = getpid(), 1);
	write(1, "\n", 1);
	st.sa_sigaction = ft_sig12_handler;
	st.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &st, NULL);
	sigaction(SIGUSR2, &st, NULL);
	while (1)
		pause();
	return (0);
}
