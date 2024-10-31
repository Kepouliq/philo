/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:46:31 by kepouliq          #+#    #+#             */
/*   Updated: 2024/10/31 15:17:26 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
			j++;
		}
		i++; 
	}
	return (0);
}

void	init_param(t_param *param, char **av)
{
	if (check_args(av))
	{
		printf(RED "ONE ARG IS NOT A NUMBER\n" RESET);
		exit(EXIT_FAILURE);
	}
	param->nb_philo = ft_atoi(av[1]);
	param->time_die = ft_atoi(av[2]);
	param->time_eat = ft_atoi(av[3]);
	param->time_sleep = ft_atoi(av[4]);
	if (param->nb_philo < 1 || param->time_die < 60 || param->time_eat < 60
		|| param->time_sleep < 60 || param->nb_philo > 200)
	{
		printf(RED "PROBLEM WITH ARGS VALUES\n" RESET);
		exit(EXIT_FAILURE);
	}
	if (av[5])
	{
		param->meal_nbr = ft_atoi(av[5]);
		if (param->meal_nbr <= 0)
		{
			printf(RED "NBR OF MEAL CANT BE 0\n" RESET);
			exit(EXIT_FAILURE);
		}
	}
	else
		param->meal_nbr = -1;
}

void	init_mutex(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->nb_philo)
	{
		pthread_mutex_init(&(param->fork[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(param->printf), NULL);
	pthread_mutex_init(&(param->checks), NULL);
}

void	init_philo(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->nb_philo)
	{
		ft_bzero(&param->philo[i], sizeof(t_philo));
		param->philo[i].id = i + 1;
		param->philo[i].nb_meal = 0;
		param->philo[i].fork_id = i;
		param->philo[i].neighbor_fork_id = (i + 1) % (param->nb_philo);
		param->philo[i].time_last_meal = 0;
		param->philo[i].param = param;
		// printf("philo [%d] take fork [%d] & [%d]\n", param->philo[i].id,
		// 	param->philo[i].fork_id, param->philo[i].neighbor_fork_id);
		i++;
	}
}
