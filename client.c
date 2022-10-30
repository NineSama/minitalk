/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroissa <mfroissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:26:16 by mfroissa          #+#    #+#             */
/*   Updated: 2022/10/30 13:19:25 by mfroissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

const char	*g_str;

void	send_signal(int serv_pid, int bit)
{
	if (bit / 128 == 0)
		kill(serv_pid, SIGUSR1);
	else
		kill(serv_pid, SIGUSR2);
}

void	message(int serv_pid, int *bit_index, int *i)
{
	unsigned char	bit;

	if ((*i) > ft_strlen((char *)g_str))
		exit(0);
	bit = g_str[*i];
	bit = bit << (*bit_index);
	send_signal(serv_pid, bit);
	if ((*bit_index) > 6)
	{
		(*i)++;
		(*bit_index) = 0;
	}
	else
		(*bit_index)++;
}

void	answer(int signum, siginfo_t *siginfo, void *context)
{
	static int	bit_index;
	static int	i;

	(void)context;
	if (signum == SIGUSR2)
	{
		printf("yo");
		if (signum == 10)
			write(1, "Message sent", 12);
		if (signum == 12)
			write(1, "Fail", 4);
		exit(0);
	}
	if (bit_index == 0 && i == 0)
		bit_index = 1;
	message(siginfo->si_pid, &bit_index, &i);
}

int	main(int ac, char **av)
{
	int					serv_pid;
	int					i;
	struct sigaction	act;

	i = 0;
	if (ac != 3)
	{
		write(2, "This only takes 2 parameters\n", 29);
		return (1);
	}
	serv_pid = ft_atoi(av[1]);
	g_str = av[2];
	act.sa_sigaction = &answer;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	message(serv_pid, &i, &i);
	while (1)
		sleep(-1);
	return (0);
}
