/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:27:57 by dsaada            #+#    #+#             */
/*   Updated: 2021/09/27 19:04:20 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_sleep(int ms, t_var *vars)
{
	struct timeval time;

	if (

}
long	check_time_from(long timestamp, long duration)
{
	struct timeval	current_time;
	long		time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	if (time - timestamp > duration)
		return (-1);
	return (time - timestamp);
}

void	*thread_func(void * tid)
{
	long	last_meal;
	struct	timeval current_time;
	pthread_mutex_t	*mutex;

	mutex = (pthread_mutex_t *)tid;
	gettimeofday(&current_time, NULL);
	last_meal = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	pthread_mutex_lock(mutex);
	usleep(10000);
	printf("%ld ms since last meal\n", check_time_from(last_meal, 25));
	pthread_mutex_unlock(mutex);
	return (NULL);
}

void	init_vars(t_var *v)
{
	int	i;

	i = -1;
	v->nb_philo = NBPHILO;
	v->nb_meal = NBMEAL;
	v->tt_eat = TTEAT;
	v->tt_sleep = TTSLEEP;
	v->tt_die = TTDIE;
	pthread_mutex_init(&(v->print), NULL);
	v->philos = malloc(sizeof(pthread_t) * v->nb_philo);
	while (++i < v->nb_philo)
	{
		pthread_create(&(v->philos[i]), NULL, thread_func, (void *)v);
	}
	i = -1;
	while (++i < v->nb_philo)
		pthread_join(v->philo[i], NULL);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	(void) argc;
	(void) argv;
	init_vars(&vars);
	return (0);
}
