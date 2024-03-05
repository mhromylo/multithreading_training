/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:55:22 by mhromylo          #+#    #+#             */
/*   Updated: 2024/03/04 11:14:28 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	report(char *str, t_philo *philo, int num)
{
	size_t	time;

	pthread_mutex_lock(philo->report_lock);
	time = get_current_time() - philo->start_time;
	if (!death(philo))
		printf("%zu %d %s\n", time, num, str);
	pthread_mutex_unlock(philo->report_lock);
}

int	philo_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->eat_lock);
	if (get_current_time() - philo->last_meal >= time_to_die && philo->eat == 0)
		return (pthread_mutex_unlock(philo->eat_lock), 1);
	pthread_mutex_unlock(philo->eat_lock);
	return (0);
}

int	check_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_philos)
	{
		if (philo_dead(&philos[i], philos[i].time_to_die))
		{
			report("died", &philos[i], philos[i].num);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_all_full(t_philo *philos)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (i < philos[0].num_philos)
	{
		pthread_mutex_lock(philos[i].eat_lock);
		if (philos[i].meals >= philos[i].num_times_to_eat)
		{
			full++;
		}
		pthread_mutex_unlock(philos[i].eat_lock);
		i++;
	}
	if (full == philos[0].num_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*god_eye(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
		if (check_dead(philos) == 1 || check_all_full(philos) == 1)
			break ;
	return (arg);
}
