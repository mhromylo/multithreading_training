/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:55:00 by mhromylo          #+#    #+#             */
/*   Updated: 2024/03/01 15:44:46 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	report("is thinking", philo, philo->num);
}

void	dream(t_philo *philo)
{
	report("is sleeping", philo, philo->num);
	ft_usleep(philo->time_to_sleap);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	report("has taken a fork", philo, philo->num);
	if (philo->num_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	report("has taken a fork", philo, philo->num);
	philo->eat = 1;
	report("is eating", philo, philo->num);
	pthread_mutex_lock(philo->eat_lock);
	philo->last_meal = get_current_time();
	philo->meals++;
	pthread_mutex_unlock(philo->eat_lock);
	ft_usleep(philo->time_to_eat);
	philo->eat = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
