/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:55:43 by mhromylo          #+#    #+#             */
/*   Updated: 2024/02/29 17:15:58 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int					num;
	int					eat;
	int					meals;
	int					num_philos;
	int					num_times_to_eat;
	int					*dead;
	size_t				last_meal;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleap;
	size_t				start_time;
	pthread_t			thread;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*report_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*eat_lock;
}				t_philo;
typedef struct s_task
{
	int				death_flag;
	pthread_mutex_t	report_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	eat_lock;
	t_philo			*philos;
}				t_task;

int		input_num(char *num);
int		ft_strlen(char *str);
int		ft_atoi(char *str);
size_t	get_current_time(void);
void	init_args(t_philo *philo, char **argv);
void	init_philos(t_philo *philos, t_task *task,
			pthread_mutex_t *forks, char **argv);
void	init_forks(pthread_mutex_t *forks, int num_philos);
void	init_task(t_task *task, t_philo *philos);
int		death(t_philo *philo);
int		ft_usleep(size_t time);
void	report(char *str, t_philo *philo, int num);
void	think(t_philo *philo);
void	dream(t_philo *philo);
void	eat(t_philo *philo);
void	*philo_routine(void *arg);
void	destroy_theads(char *str, t_task *task, pthread_mutex_t *forks);
int		philo_dead(t_philo *philo, size_t time_to_die);
int		check_dead(t_philo *philos);
int		check_all_full(t_philo *philos);
void	*god_eye(void *arg);
int		thread_create(t_task *task, pthread_mutex_t *forks);

#endif