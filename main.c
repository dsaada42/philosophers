/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:27:57 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/07 16:22:42 by dsaada           ###   ########.fr       */
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
	return (SUCCESS);
}

int	get_forks(t_philo *phi, t_var *v)
{
	pthread_mutex_lock(&(v->forks[phi->l_fork].forkex));
	v->forks[phi->l_fork].state = phi->id;
	pthread_mutex_lock(&(v->forks[phi->r_fork].forkex));
	v->forks[phi->r_fork].state = phi->id;
	pthread_mutex_lock(&(v->print));
	if (v->flag == 0)
	{
		printf("%ld %d has taken a fork\n", get_time_ms(), phi->id);
		printf("%ld %d has taken a fork\n", get_time_ms(), phi->id);
	}
	pthread_mutex_unlock(&(v->print));
	return (SUCCESS);
}

int	release_forks(t_philo *phi, t_var *v)
{
	v->forks[phi->l_fork].state = 0;
	pthread_mutex_unlock(&(v->forks[phi->l_fork].forkex));
	v->forks[phi->r_fork].state = 0;
	pthread_mutex_unlock(&(v->forks[phi->r_fork].forkex));
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

void	*ft_thread(void *data)
{
	t_philo	*phi;

	phi = (t_philo *)data;
	if (phi->id % 2 == 0)
		usleep(1000);
	while (phi->v->flag == 0)
	{
		if (ft_think(phi->v, phi) == FAILURE)
			return (NULL);
		get_forks(phi, phi->v);
		phi->last_meal = get_time_ms();
		pthread_mutex_lock(&(phi->v->print));
		if (phi->v->flag == 0)
			printf("%ld %d is eating\n", get_time_ms(), phi->id);
		pthread_mutex_unlock(&(phi->v->print));
		if (ft_eat(phi->v->tt_eat, phi->v, phi) == FAILURE)
			return (NULL);
		pthread_mutex_lock(&(phi->v->print));
		release_forks(phi, phi->v);
		if (phi->v->flag == 0)
			printf("%ld %d is sleeping\n", get_time_ms(), phi->id);
		pthread_mutex_unlock(&(phi->v->print));
		if (ft_sleep(phi->v->tt_sleep, phi->v, phi) == FAILURE)
			return (NULL);
		pthread_mutex_lock(&(phi->v->print));
		if (phi->v->flag == 0)
			printf("%ld %d is thinking\n", get_time_ms(), phi->id);
		pthread_mutex_unlock(&(phi->v->print));
	}
	return (NULL);
}

int	init_philos(t_var *v)
{
	int	i;

	i = -1;
	while (++i < v->nb_philo)
	{
		if (i == v->nb_philo - 1)
			v->philos[i].l_fork = 0;
		else
			v->philos[i].l_fork = i + 1;
		v->philos[i].r_fork = i;
		v->philos[i].id = i + 1;
		v->philos[i].v = v;
		v->philos[i].last_meal = get_time_ms();
		v->philos[i].state = 0;
		pthread_create(&(v->philos[i].philo), NULL, ft_thread, (void *)&(v->philos[i]));
	}
	i = -1;
	while (++i < v->nb_philo)
	{
		pthread_join(v->philos[i].philo, NULL);
	}
	return (SUCCESS);
}

int	init_vars(t_var *v)
{
	int	i;

	v->nb_philo = NBPHILO;
	v->nb_meal = NBMEAL;
	v->tt_eat = TTEAT;
	v->tt_sleep = TTSLEEP;
	v->tt_die = TTDIE;
	v->flag = 0;
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
	init_philos(v);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_var	v;

	(void) argc;
	(void) argv;
	if (init_vars(&v) == MALLOC_ERROR)
	{
		if (v.philos)
			free(v.philos);
		if (v.forks)
			free(v.forks);
		return (FAILURE);
	}
	free(v.philos);
	free(v.forks);
	return (0);
}
