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

char	message[BUFFER];

void	send_confirmation(int pid)
{
	write(1, "\n", 1);
	ft_putstr_fd("END acknowledging:", 1);
	ft_quick_itoa(pid);
	write(1, "\n", 1);
	kill(pid, SIGUSR1);
}

void write_reset(int len, unsigned int *count)
{
	ft_putstr_fd("\n-writitng-\n", 1);
	write(1, message, len);
	write(1, "", 1);
	if (*count > 32)
		*count = 32;
	message[0] = '\0';
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
	// printf("found byte:%c pid:%d count:%d len:%d\n", byte, pid, count, (count / 32 - 2));
	if ((count != 32 && (count / 32 - 2) >= BUFFER) || byte == 0)
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
	if (sig == SIGTERM || sig == SIGINT)
	{
		ft_putstr_fd("\nTERMINATION\nbuffer_flush{", 1);
		ft_putstr_fd(message, 1);
		ft_putstr_fd("}flush_complete .. goodbye\n", 1);
		exit(0);
	}
}

int	main(void)
{
	signal(SIGUSR1, handeler);
	signal(SIGUSR2, handeler);
	signal(SIGTERM, handeler);
	signal(SIGINT, handeler);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	if (BUFFER == 1024)
	{
		ft_putstr_fd("unchanged buffer<", 1);
		ft_quick_itoa(BUFFER);
		ft_putstr_fd(">unchanged buffer\n", 1);
	}
	else
		ft_putstr_fd("unchanged buffer", 1);
	while (1)
	{
		pause();
		// usleep(100000);
	}
	return (0);
}
