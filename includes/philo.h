/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:26:37 by kepouliq          #+#    #+#             */
/*   Updated: 2024/10/31 16:17:39 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define RESET "\e[0m"
# define RED "\e[1;91m"
# define GREEN "\e[1;92m"
# define BLUE "\e[1;94m"
# define YELLOW "\e[1;93m"
# define MAGENTA "\e[1;95m"
# define CYAN "\e[1;96m"
# define WHITE "\e[1;97m"
# define BLACK "\e[1;90m"
# define GRAY "\e[1;37m"
# define ORANGE "\e[38;5;208m"

typedef struct s_philo
{
	int				id;
	int				nb_meal;
	int				fork_id;
	int				neighbor_fork_id;
	long long		time_last_meal;
	long long		time_of_death;
	pthread_t		thread;
	struct s_param	*param;
}					t_philo;

typedef struct s_param
{
	int				nb_philo;
	int				time_eat;
	int				time_die;
	int				time_sleep;
	int				meal_nbr;
	int				id_dead;
	bool			som1_is_dead;
	bool			everybody_ate;
	long long		time_start;
	pthread_mutex_t	fork[200];
	pthread_mutex_t	printf;
	pthread_mutex_t	checks;
	t_philo			philo[200];

}					t_param;

/*                       INIT  :                           */

void				init_param(t_param *param, char **av);
void				init_mutex(t_param *param);
void				init_philo(t_param *param);
void				init_thread(t_param *param);

/*                       UTILS :                           */

void				let_me_printf(t_philo *philo, char *s);
void				ft_bzero(void *s, size_t n);
int    				ft_usleep(size_t milliseconds, t_param *param);
int					ft_atoi(const char *nptr);
int					ft_isdigit(int c);
long long    		timestamp(void);



#endif
