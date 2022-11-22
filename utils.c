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
	if (!*s || fd < 0)
		return ;
	while (*s)
		write(fd, s++, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else
	{
		if (n > 9)
			ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
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

char	*ft_strcpy(char *dest, char *src)
{
	char	*t;
	
	t = dest;
	if (!dest || !src)
		return (NULL);
	while (*src)
		*t++ = *src++;
	return (dest);
}

	// printf("byte:%u count:%d", byte, count);
	// printf("<");
	// int i = byte;
	// for (int j = 0; j < 32; j++) 
	// {
	// 	printf((i & (1U << 31) ? "1" : "0"));
	// 	i = i << 1U;
	// }
	// printf(">\n");

	// printf("%c\n", (sig ? '1' : '0'));
	