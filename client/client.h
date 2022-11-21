/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:15:02 by znichola          #+#    #+#             */
/*   Updated: 2022/11/21 20:15:02 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CLIENT_H
# define CLIENT_H

#include <stdio.h>

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef SIGUSR1
#  define SIGUSR1 1
# endif
# ifndef SIGUSR2
#  define SIGUSR2 2
# endif


#endif /*client.h*/
