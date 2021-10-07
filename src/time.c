/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:06:42 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/07 18:43:11 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_ms(void)
{
	struct timeval	current_time;
	long			time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time);
}

int	ft_sleep(int ms, t_var *v, t_philo *philo)
{
	long	time;

	time = get_time_ms();
	while (get_time_ms() - time < ms)
	{
		if (get_time_ms() - philo->last_meal >= v->tt_die)
		{
			pthread_mutex_lock(&(v->print));
			if (v->flag == 0)
			{
				v->flag = 1;
				printf("%ld %d is dead\n", get_time_ms(), philo->id);
			}
			pthread_mutex_unlock(&(v->print));
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	ft_eat(int ms, t_var *v, t_philo *philo)
{
	long	time;

	time = get_time_ms();
	while (get_time_ms() - time < ms)
	{
		if (get_time_ms() - philo->last_meal >= v->tt_die)
		{
			pthread_mutex_lock(&(v->print));
			if (v->flag == 0)
			{
				printf("%ld %d is dead\n", get_time_ms(), philo->id);
				v->flag = 1;
			}
			else
				release_forks(philo, v);
			pthread_mutex_unlock(&(v->print));
			return (FAILURE);
		}
	}
	philo->nb_meal++;
	return (SUCCESS);
}

int	ft_think(t_var *v, t_philo *philo)
{
	while (philo->v->forks[philo->l_fork].state != 0
		&& philo->v->forks[philo->r_fork].state != 0)
	{
		if (get_time_ms() - philo->last_meal >= v->tt_die)
		{
			pthread_mutex_lock(&(v->print));
			if (v->flag == 0)
			{
				v->flag = 1;
				printf("%ld %d is dead\n", get_time_ms(), philo->id);
			}
			pthread_mutex_unlock(&(v->print));
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
