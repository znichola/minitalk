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


#include "client.h"

int	ft_atoi(const char *str)
{
	int	s;
	int	n;

	n = 0;
	s = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			s = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		n = n * 10 + *str++ - '0';
	return ((int)n * s);
}
void	send_int(unsigned int i, int pid)
{
	int				count;

	// char *str = "000000000000000000101111111101110";
	// char *str = "00000000000000000011000001001111";
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
		usleep(50);
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
	write(1, "confirmation rescived", 22);
	exit(0);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (0);
	signal(SIGUSR1, handeler);
	send_message(ft_atoi(argv[1]), argv[2]);
	sleep(2);
	write(1, "no confirmation :(", 19);
	return (0);
}
