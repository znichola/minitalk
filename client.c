/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:15:08 by znichola          #+#    #+#             */
/*   Updated: 2022/11/21 20:15:08 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_int(unsigned int i, int pid)
{
	int	count;

	count = 32;
	while (count--)
	{
		if (i & (1U << 31))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i = i << 1U;
		usleep(BAUD);
	}
}

void	send_char(unsigned int i, int pid)
{
	int	count;

	count = 8;
	while (count--)
	{
		if (i & (1U << 7))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i = i << 1U;
		usleep(BAUD);
	}
}

void	send_message(int pid, char *message)
{
	int	client_pid;

	client_pid = getpid();
	send_int(client_pid, pid);
	ft_putstr_fd("client pid:", 1);
	ft_quick_itoa(client_pid);
	write(1, "\n", 1);
	while (*message)
		send_char(*message++, pid);
	send_char(0, pid);
}

void	handeler(int sig)
{
	if (sig == SIGUSR1)
		ft_putstr_fd("confirmation received\n", 1);
	exit(0);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	signal(SIGUSR1, handeler);
	send_message(ft_atoi(argv[1]), argv[2]);
	sleep(2);
	ft_putstr_fd("no confirmation :(\n", 1);
	return (1);
}
