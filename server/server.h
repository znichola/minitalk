/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:15:26 by znichola          #+#    #+#             */
/*   Updated: 2022/11/21 20:15:26 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SERVER_H
# define SERVER_H

// dev
# include <stdio.h>

// final
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
// #include <string.h>
// #include <stdlib.h>

// so vscode will leave me alone
# ifndef SIGUSR1
#  define SIGUSR1 1
# endif
# ifndef SIGUSR2
#  define SIGUSR2 2
# endif

// ◦ ft_printf and any equivalent YOU coded
// ◦ signal
// ◦ sigemptyset
// ◦ sigaddset
// ◦ sigaction
// ◦ kill
// ◦ getpid
// ◦ malloc
// ◦ free
// ◦ pause
// ◦ sleep
// ◦ usleep
// ◦ exit

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);


#endif /*server.h*/