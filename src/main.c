/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:27:57 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/07 18:47:05 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		if (phi->v->nb_meal == phi->nb_meal)
            phi->v->nb_done++;
        if (phi->v->nb_done == phi->v->nb_philo)
        {
            phi->v->flag = 1;
            return (NULL);
        }
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

int	main(int argc, char **argv)
{
	t_var	v;

	if (parser(&v, argc, argv) == FAILURE)
		return (FAILURE);
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
