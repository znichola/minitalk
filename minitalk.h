/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:15:26 by znichola          #+#    #+#             */
/*   Updated: 2022/11/21 23:55:36 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

// dev
# include <stdio.h>

// final
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

// so vscode will leave me alone
# ifndef SIGUSR1
#  define SIGUSR1 1
# endif
# ifndef SIGUSR2
#  define SIGUSR2 2
# endif

# ifndef BUFFER
#  define BUFFER 10
# endif
# ifndef BAUD
#  define BAUD 50
# endif

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *str);
char	*ft_strcpy(char *dest, char *src);

// server utils
void	send_confirmation(unsigned int *pid);
int		calc_len(int count);

// utils
int		message_exit(int sig, int fd, char *msg);
void	ft_quick_itoa(unsigned int n);

#endif /*server.h*/