/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:57:21 by kepouliq          #+#    #+#             */
/*   Updated: 2024/10/31 16:17:14 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	signe;
	int	result;

	result = 0;
	signe = 1;
	while (*nptr == '\t' || *nptr == '\n' || *nptr == '\v'
		|| *nptr == '\f' || *nptr == '\r' || *nptr == ' ')
	{
		nptr++;
	}
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			signe *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result * signe);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	char	*start;

	start = s;
	while (n)
	{
		*start = 0;
		start++;
		n--;
	}
}

void	let_me_printf(t_philo *philo, char *s)
{
	if (philo->param->som1_is_dead)
		return ;
	pthread_mutex_lock(&philo->param->printf);
	printf(YELLOW"%lld "RESET, timestamp() - philo->param->time_start);
	printf(GREEN"%d "RESET, philo->id);
	printf("%s\n", s);
	pthread_mutex_unlock(&philo->param->printf);
}

long long    timestamp(void)
{
    struct    timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

int    ft_usleep(size_t milliseconds, t_param *param)
{
    size_t    start;

    start = timestamp();
    while ((timestamp() - start) < milliseconds)
    {
		if (param->som1_is_dead)
			break;
        usleep(50);
    }
    return (0);
}