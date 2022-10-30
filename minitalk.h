/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroissa <mfroissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:45:53 by mfroissa          #+#    #+#             */
/*   Updated: 2022/10/30 08:58:24 by mfroissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>

/* server.c */
int		get_char(char *str);
void	push_term(char bit);
void	get_signal(int signum, siginfo_t *siginfo, void *context);

/* client.c */
void	send_signal(int serv_pid, int bit);
void	message(int serv_pid, int *bit_index, int *i);
void	answer(int signum, siginfo_t *siginfo, void *context);

/* utils.c */
int		ft_strlen(char *str);
void	ft_putstr(char *str);
void	ft_putchar(char c);
void	ft_putnbr(int n);
int		ft_atoi(char *str);

#endif