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
	for (int i = 31; i >= 0; i--)
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
	ft_putstr_fd("\n-writitng-\n", 1);
	write(1, message, len);
	write(1, "", 1);
	if (*count > 32)
		*count = 32;
	message[0] = '\0';
}

int	calc_len(int count)
{
	if (count <= 32)
		return (0);
	count -= 32;
	return (count / 8 - 1);
}

int	get_pid(int sig, unsigned int *count, unsigned int *pid)
{
	static unsigned int	i = 0;

	if (*count > 32)
		return(0);
	*count = *count + 1;
	i = i << 1U;
	if (sig == 1)
		i = i | 1U;
	ft_quick_itoa(*count);
	write(1, " : ", 3);
	ft_quick_itoa(calc_len(*count));
	write(1, " : ", 3);
	print_bits(i);
	write(1, "\n", 1);
	if (*count == 31)
		return (0);
	return (1);
}

int	get_char(int sig, unsigned int *count, unsigned int *octet)
{
	// printf("\nget char");
	*count = *count + 1;
	*octet = *octet << 1U;
	if (sig == 1)
		*octet = *octet | 1U;
	// ft_quick_itoa(*count);
	// write(1, " : ", 3);
	// ft_quick_itoa(calc_len(*count));
	// write(1, " : ", 3);
	// print_bits(*octet);
	// write(1, "\n", 1);
	if (calc_len(*count) != 8)
		return (1);
	return (0);
}


void	get_byte(int sig)
{
	static unsigned int	byte = 0;
	static unsigned int	count = 0;
	static unsigned int	pid = 0;
	
	if (get_pid(sig, &count, &pid))
		return ;
	if (get_char(sig, &count, &byte))
		return ;
	message[(count / 2 - 2)] = byte;
	if ((count / 2 - 2) % BUFFER == 0 || byte == 0)
		write_reset((count / 2 - 2), &count);
	if (byte == 0)
		send_confirmation(&pid);
	// byte = 0;
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
	while (1)
	{
		pause();
		// usleep(100000);
	}
	return (0);
}

// 00000000000000000011000010111100
// 00000000000000000000000001011110
// 00000000000000000000000010111100