/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:15:41 by znichola          #+#    #+#             */
/*   Updated: 2022/11/21 20:15:41 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "minitalk.h"

char	message[MSGBUFF];

void	send_confirmation(int pid)
{
	write(1, "\nSTOP. sending confirmation:%d\n", 32);
	ft_quick_itoa(pid);
	printf("\npid:%d\n", pid);
	kill(pid, SIGUSR1);
}

void write_reset(int len, unsigned int *count)
{
	write(1, message, len);
	count = 0;
}

void	get_byte(int sig)
{
	static unsigned int	byte = 0;
	static unsigned int	count = 0;
	static unsigned int	pid = 0;
	
	count++;
	byte = byte << 1;
	if (sig == 1)
		byte = byte | 1U;
	if (count % 32)
		return ;
	if (count == 32)
		pid = byte;
	else
		message[(count / 32 - 2)] = byte;
	if ((count / 32 - 2) >= MSGBUFF || byte == 0)
		write_reset((count / 32 - 2), &count);
	if (byte == 0)
		send_confirmation(pid);
	byte = 0;
}

void handeler(int sig)
{
	if (sig == SIGUSR1)
		get_byte(1);
	if (sig == SIGUSR2)
		get_byte(2);
	if (sig == SIGTERM)
	{
		ft_putstr_fd("TERMINATING - buffer flush[\n", 1);
		ft_putstr_fd(message, 1);
		ft_putstr_fd("] - flush complete, goodbye\n", 1);
	}
}

int	main(void)
{
	int	i;
	char *loading;
	char *whitesp;

	// message = (char *)malloc((MSGBUFF + 1) * sizeof(char));
	// if (!message)
	// 	return (message_exit(1, 2, "malloc error, get more ram"));
	signal(SIGUSR1, handeler);
	signal(SIGUSR2, handeler);
	signal(SIGTERM, handeler);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	loading = "-\\|/" ;
	i = 0;
	while (1)
	{
		// if (i > 5)
		// 	i = 0;
		// write(1, loading + i, 1);
		// write(1, "\r", 2);
		usleep(100000);
		// i++;
	}
	return (0);
}
