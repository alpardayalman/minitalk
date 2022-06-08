/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ardayalman <ardayalman@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:25:20 by ardayalman        #+#    #+#             */
/*   Updated: 2022/06/08 22:55:46 by ardayalman       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void handleclient(int sig)
{
	ft_putstr_color_fd(ANSI_YELLOW, "Signal sent!\n", 1);
	(void)sig;
}

static int send_bin(int pid, short int chr)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (chr % 2 == 1 && chr)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(WAIT_CRON);
		chr /= 2;
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	int i;
	int pid;
	struct sigaction sig;

	if (ac == 3)
	{
		i = 0;
		pid = ft_atoi(av[1]);
		sig.sa_flags = SA_SIGINFO;
		sig.sa_handler = &handleclient;
		sigaction(SIGUSR2, &sig, NULL);
		ft_putstr_color_fd(ANSI_GREEN, "Sending to : ", 1);
		ft_putstr_color_fd(ANSI_BLUE, ft_itoa(pid), 1);
		ft_putchar_fd('\n', 1);
		while (av[2][i])
			send_bin(pid, av[2][i++]);
	}
	else
		ft_putstr_color_fd(ANSI_GREEN, "Yetersiz bakiye.\n", 1);
	return (0);
}
