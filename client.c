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
	int				count;

	count = 32;
	while (count--)
	{
		if (i & (1U << 31))
		{
			// printf("1");
			// printf("sending a 1\n");
			kill(pid, SIGUSR1);
		}
		else
		{
			// printf("0");
			// printf("sending a 2\n");
			kill(pid, SIGUSR2);
		}
		i = i << 1U;
		usleep(BAUD);
	}
	// printf("\n");
}

void	send_message(int pid, char *message)
{
	int client_pid = getpid();
	send_int(client_pid, pid);
	printf("client pid:%d\n", client_pid);
	// printf("<\n");
	// int i = client_pid;
	// for (int j = 0; j < 32; j++) 
	// {
	// 	printf((i & (1U << 31) ? "1" : "0"));
	// 	i = i << 1U;
	// }
	// printf("\n>\n");
	while (*message)
		send_int(*message++, pid);
	send_int(0, pid);
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
