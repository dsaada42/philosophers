/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:27:57 by dsaada            #+#    #+#             */
/*   Updated: 2021/09/30 17:35:29 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long    get_time_ms(void)
{
        struct timeval  current_time;
        long            time;

        gettimeofday(&current_time, NULL);
        time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
        return (time);
}

int	ft_sleep(int ms, t_var *v, t_philo *philo)
{
	long		time;

	printf("Philo %d sleeping for %d ms\n", philo->id, ms);
	time = get_time_ms();
	while (get_time_ms() - time < ms)
	{
		if (get_time_ms() - philo->last_meal > v->tt_die)
		{
			//philo dies
			printf("Philo %d died at %ld\n", philo->id, get_time_ms());
			return (FAILURE);
		}
		//checking dans le cas ou etat = thinking (dispo des fourchettes)
	}
	printf("Philo %d has slept for %ld ms\n", philo->id, get_time_ms() - time);
	return (SUCCESS);
}

void	*thread_func(void *data)
{
	t_philo	*phi;

	phi = (t_philo *)data; 
	printf("philo alive %d\n", phi->id);
	ft_sleep(190, phi->v, phi);
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
	v->philos = malloc(sizeof(t_philo) * v->nb_philo);
	while (++i < v->nb_philo)
	{
		v->philos[i].id = i + 1;
		v->philos[i].v = v;
		v->philos[i].last_meal = get_time_ms();
		pthread_create(&(v->philos[i].philo), NULL, thread_func, (void *)&(v->philos[i]));
		//init 
	}
	i = -1;
	while (++i < v->nb_philo)
		pthread_join(v->philos[i].philo, NULL);
}

int	main(int argc, char **argv)
{
	t_var	vars;

	(void) argc;
	(void) argv;
	init_vars(&vars);
	free(vars.philos);
	return (0);
}
