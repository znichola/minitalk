/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:32:47 by znichola          #+#    #+#             */
/*   Updated: 2022/11/25 19:34:06 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_confirmation(unsigned int *pid)
{
	write(1, "\n", 1);
	ft_putstr_fd("END acknowledging:", 1);
	ft_quick_itoa(*pid);
	write(1, "\n", 1);
	kill(*pid, SIGUSR1);
	*pid = 0;
}

int	calc_len(int count)
{
	if (count <= 32)
		return (0);
	count -= 31;
	return (count / 8 - 1);
}
