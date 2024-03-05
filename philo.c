/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:55:34 by mhromylo          #+#    #+#             */
/*   Updated: 2024/03/05 12:24:58 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input_num(char *num)
{
	int	i;

	i = 0;
	while (num[i] != '\0')
	{
		if (num[i] < '0' || num[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	valid_input(char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || input_num(argv[1]) == 1)
		return (write(2, "Number of philosophers should be >0\n", 38), 1);
	if (ft_atoi(argv[2]) <= 0 || input_num(argv[2]) == 1)
		return (write(2, "Time to die should be >0\n", 27), 1);
	if (ft_atoi(argv[3]) <= 0 || input_num(argv[3]) == 1)
		return (write(2, "Time to eat should be >0\n", 27), 1);
	if (ft_atoi(argv[4]) <= 0 || input_num(argv[4]) == 1)
		return (write(2, "Time to sleep should be >0\n", 29), 1);
	if (argv[5] && (ft_atoi(argv[5]) <= 0 || input_num(argv[5]) == 1))
		return (write(2, "Number of times to eat should be >0\n", 36), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_task			task;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];

	if (argc != 5 && argc != 6)
		return (write(2, "wrong number of args\n", 21), 1);
	if (valid_input(argv) == 1)
		return (1);
	init_task(&task, philos);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(philos, &task, forks, argv);
	thread_create(&task, forks);
	destroy_theads(NULL, &task, forks);
	return (0);
}
