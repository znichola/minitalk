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

#include "minitalk.h"

char	g_message[BUFFER];

void	write_reset(int len, unsigned int *count)
{
	len += 1;
	write(1, g_message, len);
	*count = 32;
	g_message[0] = '\0';
}

int	get_octet(int sig, unsigned int count, unsigned int *ret)
{
	static unsigned int	octet = 0;

	octet = octet << 1U;
	if (sig == 1)
		octet = octet | 1U;
	if (count % 8 == 0)
	{
		*ret = octet;
		octet = 0;
		return (0);
	}
	return (1);
}

void	decoder(int sig, unsigned int *count, unsigned int *pid)
{
	unsigned int	octet;

	if (get_octet(sig, *count, &octet))
		return ;
	if (*count <= 32)
		*pid = (*pid << 8 | octet);
	else
	{
		g_message[calc_len(*count)] = octet;
		if (octet == 0)
		{
			write_reset(calc_len(*count), count);
			send_confirmation(pid);
			*count = 0;
		}
		else if (calc_len(*count) == BUFFER)
			write_reset(calc_len(*count), count);
	}
}

void	handeler(int sig)
{
	static unsigned int	count = 0;
	static unsigned int	pid = 0;

	count += 1;
	if (sig == SIGUSR1)
		decoder(1, &count, &pid);
	if (sig == SIGUSR2)
		decoder(2, &count, &pid);
	if (sig == SIGTERM || sig == SIGINT)
	{
		ft_putstr_fd("\nTERMINATION\nbuffer_flush{", 1);
		ft_putstr_fd(g_message, 1);
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
	ft_putstr_fd("Server pid: ", 1);
	ft_quick_itoa(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
