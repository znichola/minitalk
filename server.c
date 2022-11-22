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

char	*message;

int	add_message(int index, int c)
{
	char *tmp;

	if (index != MSGSIZE && index % MSGSIZE == 0)
	{
		tmp = message;
		message = (char *)malloc((index + MSGSIZE + 1) * sizeof(char));
		if (!tmp)
			return (1);
		ft_strcpy(message, tmp);
		printf("\nrealloc-ed, new size:%d\n", (index + MSGSIZE + 1) * sizeof(char));
		free(tmp);
	}
	message[index] = c;
}

void	send_confirmation(int pid)
{
	printf("\nsending confirmation to:%d\n", pid);
	kill(pid, SIGUSR1);
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
		add_message(count / 32 - 2, byte);
	if (byte == 0)
	{
		ft_putstr_fd(message, 1);
		// write(1, "\n", 1);
		send_confirmation(pid);
		count = 0;
	}
	byte = 0;
}

void handeler(int sig)
{
	if (sig == SIGUSR1)
		get_byte(1);
	if (sig == SIGUSR2)
		get_byte(2);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int	count;

	count = 0;
	message = (char *)malloc((MSGSIZE + 1) * sizeof(char));
	if (!message)
		return (1);
	signal(SIGUSR1, handeler);
	signal(SIGUSR2, handeler);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
		sleep(1);
	return (0);
}
