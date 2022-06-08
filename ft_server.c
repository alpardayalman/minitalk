/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ardayalman <ardayalman@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:32:23 by ardayalman        #+#    #+#             */
/*   Updated: 2022/06/08 22:52:28 by ardayalman       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void reset(char *str)
{
	int j;

	j = 0;
	while (j < 8)
		str[j++] = '\0';
}

void write_char(int *res, char *bin)
{
	int two;
	char chr;
	int index;

	two = 1;
	chr = 0;
	index = 0;
	while (index < 8)
	{
		if (bin[index++] == '1')
			chr += two;
		two *= 2;
	}
	write(1, &chr, 1);
	*res = 0;
	reset(bin);
}

static void handle(int sig, siginfo_t *siginfo, void *bos)
{
	static int i;
	static char bin[8];

	(void)bos;
	if (!i)
		i = 1;
	if (sig == SIGUSR1)
	{
		bin[i - 1] = '0';
		i++;
	}
	else if (sig == SIGUSR2)
	{
		bin[i - 1] = '1';
		i++;
	}
	if (i == 9)
	{
		write_char(&i, bin);
		kill(siginfo->si_pid, SIGUSR2);
	}
}

int main(void)
{
	char *a;
	struct sigaction sa;

	sa.sa_sigaction = &handle;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	a = ft_itoa(getpid());
	ft_putstr_color_fd(ANSI_YELLOW, "Pid: ", 1);
	ft_putstr_color_fd(ANSI_BLUE, a, 1);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
