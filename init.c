/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:54:35 by mhromylo          #+#    #+#             */
/*   Updated: 2024/03/01 16:25:09 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_philo *philo, char **argv)
{
	philo->num_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleap = ft_atoi(argv[4]);
	if (argv[5])
		philo->num_times_to_eat = ft_atoi(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

void	init_philos(t_philo *philos, t_task *task, pthread_mutex_t *forks,
			char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos[i].num = i + 1;
		philos[i].eat = 0;
		philos[i].meals = 0;
		init_args(&philos[i], argv);
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].report_lock = &task->report_lock;
		philos[i].dead_lock = &task->dead_lock;
		philos[i].eat_lock = &task->eat_lock;
		philos[i].dead = &task->death_flag;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].num_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_task(t_task *task, t_philo *philos)
{
	task->death_flag = 0;
	task->philos = philos;
	pthread_mutex_init(&task->report_lock, NULL);
	pthread_mutex_init(&task->dead_lock, NULL);
	pthread_mutex_init(&task->eat_lock, NULL);
}

void	destroy_theads(char *str, t_task *task, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&task->report_lock);
	pthread_mutex_destroy(&task->eat_lock);
	pthread_mutex_destroy(&task->dead_lock);
	while (i < task->philos[0].num_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
