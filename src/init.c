/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:05:47 by dsaada            #+#    #+#             */
/*   Updated: 2021/11/08 16:38:14 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_philos_even(t_var *v)
{
	int	i;

	i = -1;
	while (++i < v->nb_philo)
	{
		if (v->philos[i].id % 2 == 0)
			pthread_create(&(v->philos[i].philo), NULL, ft_thread,
				(void *)&(v->philos[i]));
	}
	return (SUCCESS);
}

static int	init_philos(t_var *v)
{
	int	i;

	i = -1;
	while (++i < v->nb_philo)
	{
		if (i == v->nb_philo - 1)
			v->philos[i].l_fork = 0;
		else
			v->philos[i].l_fork = i + 1;
		v->philos[i].nb_meal = 0;
		v->philos[i].r_fork = i;
		v->philos[i].id = i + 1;
		v->philos[i].v = v;
		v->philos[i].last_meal = get_time_ms();
		v->philos[i].state = 0;
		if (v->philos[i].id % 2)
			pthread_create(&(v->philos[i].philo), NULL, ft_thread,
				(void *)&(v->philos[i]));
	}
	init_philos_even(v);
	i = -1;
	while (++i < v->nb_philo)
		pthread_join(v->philos[i].philo, NULL);
	return (SUCCESS);
}

int	init_vars(t_var *v)
{
	int	i;

	v->flag = 0;
	v->nb_done = 0;
	pthread_mutex_init(&(v->print), NULL);
	v->philos = malloc(sizeof(t_philo) * v->nb_philo);
	if (v->philos == NULL)
		return (MALLOC_ERROR);
	v->forks = malloc(sizeof(t_fork) * v->nb_philo);
	if (v->forks == NULL)
		return (MALLOC_ERROR);
	i = -1;
	while (++i < v->nb_philo)
	{
		v->forks[i].state = 0;
		pthread_mutex_init(&(v->forks[i].forkex), NULL);
	}
	v->s_time = get_time_ms();
	init_philos(v);
	return (SUCCESS);
}
