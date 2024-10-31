/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:00:47 by kepouliq          #+#    #+#             */
/*   Updated: 2024/10/31 16:37:27 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_a_fork(t_philo *philo, int id)
{
	t_param	*param;

	param = philo->param;
	pthread_mutex_lock(&(param->fork[id]));
	let_me_printf(philo, CYAN "has taken a fork" RESET);
}

void	only_one_philo (t_philo *philo)
{
	t_param	*param;

	param = philo->param;
	take_a_fork(philo, philo->fork_id);
	pthread_mutex_lock(&param->checks);
	param->philo[0].time_of_death = timestamp() - param->time_start;
	param->id_dead = param->philo[0].id;
	philo->param->som1_is_dead = true;
	pthread_mutex_unlock(&param->checks);
	pthread_mutex_unlock(&(param->fork[philo->fork_id]));
}

void	eating(t_philo *philo)
{
	t_param	*param;

	param = philo->param;
	if (philo->param->nb_philo == 1)
	{
		only_one_philo(philo);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		usleep(500);
		take_a_fork(philo, philo->fork_id);
		take_a_fork(philo, philo->neighbor_fork_id);
	}
	else
	{
		take_a_fork(philo, philo->neighbor_fork_id);
		take_a_fork(philo, philo->fork_id);
	}
	let_me_printf(philo, MAGENTA "is eating" RESET);
	pthread_mutex_lock(&param->checks);
	philo->time_last_meal = timestamp() - param->time_start;
	philo->nb_meal++;
	pthread_mutex_unlock(&param->checks);
	if (!philo->param->som1_is_dead)
		ft_usleep(param->time_eat, philo->param);
	pthread_mutex_unlock(&(param->fork[philo->fork_id]));
	pthread_mutex_unlock(&(param->fork[philo->neighbor_fork_id]));
}

void	sleeping(t_philo *philo)
{
	let_me_printf(philo, BLUE"is sleeping"RESET);
	if (philo->param->som1_is_dead == false)
		ft_usleep(philo->param->time_sleep, philo->param);
}

void	thinking(t_philo *philo)
{
	let_me_printf(philo, ORANGE"is thinking"RESET);
}

void	*routine(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	while (!philo->param->everybody_ate)
	{
		if (philo->param->som1_is_dead)
			break;
		eating(philo);
		if (philo->param->som1_is_dead)
			break;
		sleeping(philo);
		if (philo->param->som1_is_dead)
			break;
		thinking(philo);
		if (philo->param->som1_is_dead)
			break;
	}
	return (NULL);
}

void check_if_som1_died_bro(t_param *param)
{
	int i;

	while (!param->everybody_ate)
	{
		i = 0;
		while(i < param->nb_philo && !param->som1_is_dead)
		{
			pthread_mutex_lock(&param->checks);
			if (param->philo[i].time_last_meal > param->time_die * param->philo[i].nb_meal)
			{
				param->philo[i].time_of_death = timestamp() - param->time_start;
				param->som1_is_dead = true;
				param->id_dead = param->philo[i].id;
			}
			pthread_mutex_unlock(&param->checks);
			i++;
			// usleep(100);
		}
		if (param->som1_is_dead)
			break;
		pthread_mutex_lock(&param->checks);
		i = 0;
		while (param->meal_nbr != -1 && i < param->nb_philo && param->philo[i].nb_meal >= param->meal_nbr)
			i++;
		if (i == param->nb_philo)
			param->everybody_ate = true;
		pthread_mutex_unlock(&param->checks);
	}
}

void	destroy_mutex(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->nb_philo)
	{
		pthread_mutex_destroy(&(param->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&(param->printf));
	pthread_mutex_destroy(&(param->checks));
}

void	init_thread(t_param *param)
{
	int	i;

	i = 0;
	param->time_start = timestamp();
	while (i < param->nb_philo)
	{
		if (pthread_create(&(param->philo[i].thread), NULL, &routine,
				&(param->philo[i])))
		{
			printf(RED "PROBLEM WITH THREAD INIT\n" RESET);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (param->nb_philo != 1)
		check_if_som1_died_bro(param);
	i = 0;
	while (i < param->nb_philo)
	{
		pthread_join(param->philo[i].thread, NULL);
		i++;
	}
	if (param->som1_is_dead == true)
		printf(RED "%lld %d is dead\n" RESET, param->philo[param->id_dead - 1].time_of_death, param->id_dead);
	destroy_mutex(param);
}
