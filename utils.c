/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:15:19 by znichola          #+#    #+#             */
/*   Updated: 2022/11/21 20:15:19 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!*s || fd < 0)
		return ;
	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}

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

int	message_exit(int sig, int fd, char *msg)
{
	while (*msg)
		write(fd, msg++, 1);
	write(fd, &"\n", 1);
	return (sig);
}

void	ft_quick_itoa(unsigned int n)
{
	unsigned char	c;

	if (n > 9)
		ft_quick_itoa(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}
