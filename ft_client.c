/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayalman <ayalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:25:20 by ardayalman        #+#    #+#             */
/*   Updated: 2022/06/08 15:41:21 by ayalman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	send_bin(int pid, int chr)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (chr % 2 == 1 && chr)
		{
			kill(pid, SIGUSR2);
			usleep(WAIT_CRON);
		}
		else
		{
			kill(pid, SIGUSR1);
			usleep(WAIT_CRON);
		}
		chr /= 2;
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	if (ac == 3)
	{
		i = 0;
		pid = ft_atoi(av[1]);
		while (av[2][i])
			send_bin(pid, av[2][i++]);
	}
	return (0);
}
