/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:58:08 by znichola          #+#    #+#             */
/*   Updated: 2022/11/21 13:58:08 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	printf("this is the server pid:%d\n", getpid());
	return (0);
}