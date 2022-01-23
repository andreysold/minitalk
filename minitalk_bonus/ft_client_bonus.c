/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galetha <galetha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:50:20 by galetha           #+#    #+#             */
/*   Updated: 2022/01/20 14:52:50 by galetha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	g_kok = 0;

void	ft_mensaje(int signum)
{
	if (signum == SIGUSR1)
		g_kok = 1;
}

int	ft_atoi(const char *s)
{
	int		i;
	char	*p;
	int		res;

	i = 0;
	res = 0;
	p = (char *)s;
	while ((s[i] >= 0x09 && s[i] <= 0x0D) || (s[i] == ' '))
		i++;
	if (p[i] == '-' || p[i] == '+')
		i++;
	while (p[i] >= '0' && p[i] <= '9')
	{
		res = (res * 10) + (p[i] - '0');
		i++;
	}
	return (res);
}

void	ft_dec_bonus(int pid, char *c)
{
	int	g_bts;
	int	i;

	i = 0;
	g_bts = 0b10000000;
	while (1)
	{
		while (g_bts)
		{
			usleep(10);
			if (g_bts & c[i])
				kill (pid, SIGUSR1);
			else
				kill (pid, SIGUSR2);
			g_bts /= 2;
			while (g_kok != 1)
				usleep(1);
			g_kok = 0;
		}
		usleep(20);
		g_bts = 0b10000000;
		if (!c[i])
			break ;
		i++;
	}
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	i = 0;
	signal(SIGUSR1, ft_mensaje);
	if (ac < 3)
	{
		write(1, "ERROR!\n", 7);
		exit(0);
	}
	pid = ft_atoi(av[1]);
	ft_dec_bonus(pid, av[2]);
}
