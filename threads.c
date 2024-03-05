/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:55:52 by mhromylo          #+#    #+#             */
/*   Updated: 2024/03/05 16:03:49 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num % 2 == 0)
		ft_usleep(1);
	while (!death(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (arg);
}

int	thread_create(t_task *task, pthread_mutex_t *forks)
{
	pthread_t	god;
	int			i;

	if (pthread_create(&god, NULL, &god_eye, task->philos) != 0)
		destroy_theads("Thread creation error", task, forks);
	i = 0;
	while (i < task->philos[0].num_philos)
	{
		if (pthread_create(&task->philos[i].thread, NULL, &philo_routine,
				&task->philos[i]) != 0)
			destroy_theads("Thread creation error", task, forks);
		i++;
	}
	i = 0;
	if (pthread_join(god, NULL) != 0)
		destroy_theads("Thread join error", task, forks);
	while (i < task->philos[0].num_philos)
	{
		if (pthread_join(task->philos[i].thread, NULL) != 0)
			destroy_theads("Thread join error", task, forks);
		i++;
	}
	return (0);
}
