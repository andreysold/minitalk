/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galetha <galetha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:31:35 by galetha           #+#    #+#             */
/*   Updated: 2022/01/20 14:32:12 by galetha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

void	ft_sig12_handler(int sig)
{
	static int		i;
	static int		symb;
	static int		count;

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
}

int	main(void)
{
	int	pid;

	ft_putnbr_fd(pid = getpid(), 1);
	write(1, "\n", 1);
	signal(SIGUSR1, &ft_sig12_handler);
	signal(SIGUSR2, &ft_sig12_handler);
	while (1)
		pause();
	return (0);
}
