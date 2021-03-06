/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:27:57 by dsaada            #+#    #+#             */
/*   Updated: 2021/11/09 15:00:21 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	handle_meals(t_philo *phi)
{
	if (phi->v->nb_meal == phi->nb_meal)
		phi->v->nb_done++;
	if (phi->v->nb_done == phi->v->nb_philo)
	{
		pthread_mutex_lock(&(phi->v->print));
		if (phi->v->flag == 0)
			printf("End of program %ld ms\n",
				get_time_ms() - phi->v->s_time);
		phi->v->flag = 1;
		pthread_mutex_unlock(&(phi->v->print));
		release_forks(phi, phi->v);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	eat_routine(t_philo *phi)
{
	get_forks(phi, phi->v);
	phi->last_meal = get_time_ms();
	if (phi->v->flag == 0)
		printf("%ld %d is eating\n",
			get_time_ms() - phi->v->s_time, phi->id);
	pthread_mutex_unlock(&(phi->v->print));
	if (ft_eat(phi->v->tt_eat, phi->v, phi) == FAILURE)
	{
		release_forks(phi, phi->v);
		return (FAILURE);
	}
	if (handle_meals(phi) == FAILURE)
		return (FAILURE);
	pthread_mutex_lock(&(phi->v->print));
	release_forks(phi, phi->v);
	return (SUCCESS);
}

void	*solo_routine(t_philo *phi, t_var *v)
{
	pthread_mutex_lock(&(v->forks[phi->l_fork].forkex));
	v->forks[phi->l_fork].state = phi->id;
	printf("%ld %d has taken a fork\n",
		get_time_ms() - v->s_time, phi->id);
	while (get_time_ms() - phi->last_meal < v->tt_die)
	{
	}
	printf("%ld %d is dead\n",
		get_time_ms() - v->s_time, phi->id);
	pthread_mutex_unlock(&(v->forks[phi->l_fork].forkex));
	return (NULL);
}

void	*ft_thread(void *data)
{
	t_philo	*phi;

	phi = (t_philo *)data;
	if (phi->id == 1 && phi->v->nb_philo == 1)
		return (solo_routine(phi, phi->v));
	while (phi->v->flag == 0)
	{
		if (ft_think(phi->v, phi) == FAILURE)
			return (NULL);
		if (eat_routine(phi) == FAILURE)
			return (NULL);
		if (phi->v->flag == 0)
			printf("%ld %d is sleeping\n",
				get_time_ms() - phi->v->s_time, phi->id);
		pthread_mutex_unlock(&(phi->v->print));
		if (ft_sleep(phi->v->tt_sleep, phi->v, phi) == FAILURE)
			return (NULL);
		pthread_mutex_lock(&(phi->v->print));
		if (phi->v->flag == 0)
			printf("%ld %d is thinking\n",
				get_time_ms() - phi->v->s_time, phi->id);
		pthread_mutex_unlock(&(phi->v->print));
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_var	v;

	if (parser(&v, argc, argv) == FAILURE)
		return (FAILURE);
	if (init_vars(&v) == FAILURE)
	{
		if (v.philos)
			free(v.philos);
		if (v.forks)
			free(v.forks);
		mutex_destroyer(&v);
		return (FAILURE);
	}
	mutex_destroyer(&v);
	free(v.philos);
	free(v.forks);
	return (0);
}
