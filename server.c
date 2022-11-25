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

void	print_bits(unsigned char octet)
{
	for (int i = 7; i >= 0; i--)
	{
		if (octet & (1U << i))
			write(1, "1", 1);
		else
			write(1, "0", 1);
	}
}

void	send_confirmation(unsigned int *pid)
{
	write(1, "\n", 1);
	ft_putstr_fd("END acknowledging:", 1);
	ft_quick_itoa(*pid);
	write(1, "\n", 1);
	kill(*pid, SIGUSR1);
	*pid = 0;
}

void write_reset(int len, unsigned int *count)
{
	len += 1;
	// write(1, "len:", 5);
	// ft_quick_itoa(len);
	// ft_putstr_fd("-writitng-<", 1);
	write(1, message, len);
	// write(1, ">\n", 2);
	*count = 32;
	message[0] = '\0';
}

int	calc_len(int count)
{
	if (count <= 32)
		return (0);
	count -= 31;
	return (count / 8 - 1);
}

int	get_octet(int sig, unsigned int count, unsigned int *ret)
{
	static unsigned int	octet = 0;

	octet = octet << 1U;
	if (sig == 1)
		octet = octet | 1U;
	if (count % 8 == 0)
	{
		// ft_quick_itoa(count);
		// write(1, " : ", 3);
		// print_bits(octet);
		// write(1, &octet, 1);
		// write(1, " : ", 3);
		// ft_quick_itoa(calc_len(count));
		// write(1, "\n", 1);
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
		message[calc_len(*count)] = octet;
		// message[calc_len(*count) + 1] = '\0';
		if (octet == 0)
		{
			write_reset(calc_len(*count), count);
			send_confirmation(pid);
			* count = 0;
		}
		else if (calc_len(*count) == BUFFER)
			write_reset(calc_len(*count), count);
	}
}

void handeler(int sig)
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
	ft_putstr_fd("Server pid: ", 1);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}

// 01245689acdeghilklnop
// 01245689acdeghilklnop
// 0124
//     5689
//         acde
//             f
//             ghil
//                 j
//                   m
//                 klno
//                     p