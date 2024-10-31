/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:26:10 by kepouliq          #+#    #+#             */
/*   Updated: 2024/10/29 18:58:55 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **argv)
{
	t_param	param;

	if (ac != 5 && ac != 6)
		return (printf(RED "Wrong nb of args !\n" RESET), EXIT_FAILURE);
	ft_bzero(&param, sizeof(t_param));
	init_param(&param, argv);
	init_mutex(&param);
	init_philo(&param);
	init_thread(&param);
	return (0);
}
