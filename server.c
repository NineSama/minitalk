/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroissa <mfroissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:09:08 by mfroissa          #+#    #+#             */
/*   Updated: 2022/11/07 11:57:47 by mfroissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct s_binary
{
	char	tab[9];
	int		bit_index;
}				t_binary;
t_binary	g_bin;

int	get_char(char *str)
{
	int	i;
	int	val;

	i = 0;
	val = 0;
	while (str[i])
	{
		if (str[i] == '0')
			val = val * 2;
		if (str[i] == '1')
			val = val * 2 + 1;
		i++;
	}
	return (val);
}

void	push_term(char bit, int pid)
{
	g_bin.tab[g_bin.bit_index] = bit;
	g_bin.bit_index++;
	if (g_bin.bit_index > 7)
	{
		g_bin.tab[8] = '\0';
		ft_putchar(get_char(g_bin.tab));
		g_bin.bit_index = 0;
		if (get_char(g_bin.tab) == '\0')
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
	}
	else
		kill(pid, SIGUSR2);
}

void	get_signal(int signum, siginfo_t *siginfo, void *context)
{
	(void)context;
	if (signum == 10)
		push_term('0', siginfo->si_pid);
	if (signum == 12)
		push_term('1', siginfo->si_pid);
}

int	main(int ac, char **av)
{
	int					serv_pid;
	struct sigaction	act;

	if (ac != 1)
		write(2, "This doesnt take parameters\n", 28);
	(void)av;
	serv_pid = getpid();
	ft_putstr("PID : ");
	ft_putnbr(serv_pid);
	ft_putstr("\n");
	act.sa_sigaction = &get_signal;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		sleep(-1);
}
